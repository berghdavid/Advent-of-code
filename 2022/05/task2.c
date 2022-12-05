#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"

const int STACKS = 9;

typedef struct Crate Crate;
typedef struct Stack Stack;
typedef struct Hangar Hangar;

struct Crate {
	char	id;
	Crate*	next;
};

struct Stack {
	Crate*	first;
	Crate*	last;
};

struct Hangar {
	int	size;
	Stack*	row;
	char*	ans;
};

void append(Hangar* h, Crate* c, int i)
{
	Stack*	s;

	s = &h->row[i];
	
	if (s->last != NULL) {
		s->last->next = c;
	} else {
		s->first = c;
	}
	s->last = c;
}

Crate* get(Hangar* h, int row, int nbr)
{
	int	i;
	Crate*	c;
	Stack*	s;

	s = &h->row[row];

	c = s->first;
	for (i = 0; i < nbr; i++) {
		if (c->next == NULL) {
			return c;
		}
		c = c->next;
	}

	return c;
}

Stack* pop(Hangar* h, int row, int nbr)
{
	int	i;
	Crate*	c;
	Crate*	first;
	Stack*	s;
	Stack*	new;

	s = &h->row[row];
	c = s->first;

	new = malloc(sizeof(Stack));
	new->first = c;

	for (i = 0; i < nbr - 1; i++) {
		c = c->next;
	}
	new->last = c;
	s->first = c->next;
	c->next = NULL;
	
	if (s->first == NULL) {
		s->last = NULL;
	}
	
	return new;
}

void merge(Hangar* h, Stack* new, int i)
{
	Stack*	s;

	s = &h->row[i];
	new->last->next = s->first;
	s->first = new->first;

	free(new);
}

Hangar*	init_hangar()
{
	char	c;
	int	i;
	int	count;
	Crate*	crate;
	Hangar*	h;

	count = 0;

	h = malloc(sizeof(Hangar));
	h->size = STACKS;
	h->row = malloc(h->size * sizeof(Stack));
	h->ans = malloc((h->size + 1) * sizeof(char));
	h->ans[h->size] = '\0';

	for (i = 0; i < h->size; i++) {
		h->row[i].first = NULL;
		h->row[i].last = NULL;
	}

	while (1) {
		c = getchar();
		if (c == '[') {
			c = getchar();
			crate = malloc(sizeof(Crate));
			crate->next = NULL;
			crate->id = c;
			append(h, crate, count % h->size);
			getchar();		/* Skip ']'	*/
		} else if (c == ' '){
			c = getchar();
			if (c == ' ') {
				getchar();	/* Skip ' '	*/
			} else {
				break;
			}
		}

		getchar();			/* Skip blanks	*/
		count++;
	}

	while (c != 'm') {
		c = getchar();
	}

	return h;
}

void free_hangar(Hangar* h)
{
	int	i;
	Crate*	c;
	Stack*	s;

	for (i = 0; i < h->size; i++) {
		s = &h->row[i];
		c = s->first;
		while (c != NULL) {
			s->first = c->next;
			free(c);
			c = s->first;
		}
	}
	free(h->row);
	free(h->ans);
	free(h);
}

void make_moves(Hangar* h)
{
	int	counter;
	int	nbr;
	int	from;
	int	i;
	Crate*	crate;

	counter = 0;
	while ((i = next_int()) != -1) {
		if (i == 0) {
			continue;
		}
		if (counter == 0) {
			nbr = i;
			counter++;
		} else if (counter == 1) {
			from = i - 1;
			counter++;
		} else {
			merge(h, pop(h, from, nbr), i - 1);
			counter = 0;
		}
	}
}

void calc_ans(Hangar* h)
{
	int	i;
	char*	c;

	for (i = 0; i < h->size; i++) {
		c = &get(h, i, 0)->id;
		h->ans[i] = *c;
	}
}

Hangar* solve()
{
	Hangar*	h;

	h = init_hangar();

	make_moves(h);
	calc_ans(h);

	return h;
}

int main(int argc, char *argv[])
{
	Hangar*	h;
	h = solve();

	printf("Task 2 ans: %s\n", h->ans);

	free_hangar(h);

	return 0;
}

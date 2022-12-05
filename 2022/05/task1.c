#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../common/utils.h"

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

void prepend(Hangar* h, Crate* c, int i)
{
	Stack*	s;

	s = &h->row[i];

	c->next = s->first;
	s->first = c;
	if (s->last == NULL) {
		s->last = c;
	}

}

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

Crate* pop(Hangar* h, int row)
{
	Crate*	c;
	Stack*	s;

	s = &h->row[row];
	
	c = s->first;
	s->first = c->next;
	c->next = NULL;

	if (s->first == NULL) {
		s->last = NULL;
	}
	
	return c;
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
			getchar();	/* getchar() == ']'	*/
		} else if (c == ' '){
			c = getchar();
			if (c == ' ') {
				getchar(); /* getchar() == ' '	*/
			} else {
				break;
			}
		}

		getchar();		/* getchar()==' '||'\n'	*/
		count++;
	}

	while (c != 'm') {
		c = getchar();
	}

	return h;
}

void print_hangar(Hangar* h)
{
	int	i;
	Crate*	c;
	Stack*	s;

	printf(" --- Hangar ---\n");
	for (i = 0; i < h->size; i++) {
		s = &h->row[i];
		printf("Stack %d:", i + 1);
		c = s->first;
		while (c != NULL) {
			printf(" %c", c->id);
			c = c->next;
		}
		printf("\n");
	}
}

void free_hangar(Hangar* h)
{
	int	i;
	Stack*	s;

	for (i = 0; i < h->size; i++) {
		s = &h->row[i];
		while (s->first != NULL) {
			free(pop(h, i));
		}
	}
	free(h->row);
	free(h->ans);
	free(h);
}

void move(Hangar* h, int nbr, int from, int to)
{
	int	i;

	for (i = 0; i < nbr; i++) {
		prepend(h, pop(h, from), to);
	}
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
			move(h, nbr, from, i - 1);
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

	printf("Task 1 ans: %s\n", h->ans);

	free_hangar(h);

	return 0;
}

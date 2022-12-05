#include <stdio.h>
#include <stdlib.h>
#include "../common/utils.h"

typedef struct Letter Letter;
typedef struct Sack Sack;

struct Letter {
	char	item;
	Letter*	next;
};

struct Sack {
	Letter*	comp1;
	Letter*	comp2;
	int	size;
};

Sack* build_sack()
{
	int	size;
	char	c;
	Letter*	first;
	Letter*	mid;
	Letter*	s;
	Sack*	l;

	/* Init first element */
	c = getchar();
	if (c == EOF || c == '\n') {
		return NULL;
	}
	first = malloc(sizeof(Letter));
	first->item = c;
	first->next = NULL;
	size = 1;

	s = first;
	mid = first;
	
	while((c = getchar()) != EOF && c != '\n') {
		s->next = malloc(sizeof(Letter));
		s = s->next;
		s->item = c;
		s->next = NULL;
		if (++size % 2 == 0) {
			mid = mid->next;
		}
	}

	l = malloc(sizeof(Sack));
	l->comp1 = first;
	l->comp2 = mid;
	l->size = size;

	return l;
}

void free_sack(Sack* l)
{
	Letter*	i;
	Letter*	temp;

	i = l->comp1;

	while (i != NULL) {
		temp = i->next;
		free(i);
		i = temp;
	}

	free(l);
}

int in_comp1(char c, Sack* l)
{
	int	i;
	Letter*	s;

	i = 0;
	s = l->comp1;

	for (i = 0; i < l->size / 2; i++) {
		if (s->item == c) {
			return 1;
		}
		s = s->next;
	}

	return 0;
}

int pts(char c)
{
	int	ans;

	ans = (int) c - 96;
	if (ans <= 0) {
		ans += 58;
	}
	return ans;
}

int main(void)
{
	int	ans;
	int	i;
	Letter*	s;
	Sack*	l;

	ans = 0;

	while ((l = build_sack()) != NULL) {
		s = l->comp2;
		for (i = 0; i < (l->size / 2); i++) {
			if (in_comp1(s->item, l)) {
				ans += pts(s->item);
				break;
			}
			s = s->next;
		}
		free_sack(l);
	}

	printf("Task 1 ans: %d\n", ans);

	return 0;
}

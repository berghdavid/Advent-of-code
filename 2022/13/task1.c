#include <stdio.h>
#include <stdlib.h>

typedef struct List List;
typedef struct Pair Pair;

struct List {
	int	val;
	int	parens;
	List*	next;
};

struct Pair {
	List*	l1;
	List*	l2;
	Pair*	next;
};

Pair* init_pair()
{
	Pair*	p;

	p = malloc(sizeof(Pair));
	p->next = NULL;
	p->l1 = malloc(sizeof(List));
	p->l1->next = NULL;
	p->l1->parens = 0;
	p->l1->val = 0;
	p->l2 = malloc(sizeof(List));
	p->l2->next = NULL;
	p->l2->parens = 0;
	p->l2->val = 0;
	return p;
}

int read_to_pair(Pair* p)
{
	char	c;

	while ((c = getchar()) != EOF && c != '\n') {
		/* TODO: Read to l1 */
	}
	if (c == '\n') {
		return 1;
	}
	while ((c = getchar()) != EOF) {
		/* TODO: Read to l2 */
	}
	return 0;
}

Pair* init_pairs()
{
	Pair*	first;
	Pair*	prev;
	Pair*	p;

	first = read_to_pair();
	prev = first;
	while (read_to_pair(p) == 0) {
		p = init_pair();
		prev->next = p;
	}

	return first;
}

void free_pairs(Pair* first)
{
	Pair*	p;
	Pair*	next_p;
	List*	l;
	List*	next_l;

	p = first;
	while (p != NULL) {
		l = p->l1;
		while (l != NULL) {
			next_l = l->next;
			free(l);
			l = next_l;
		}
		next_p = p->next;
		free(p);
		p = p->next;
	}
}

int get_score(Pair* first)
{
	/* TODO: Calculate score */
	return 0;
}

void solve(char* ans)
{
	Pair*	first;
	int	score;

	first = init_pairs();
	score = get_score();
	free_pairs(first);

	sprintf(ans, "%d", score);
}

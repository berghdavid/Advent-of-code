#include <stdio.h>
#include <stdlib.h>

typedef struct Letter Letter;
typedef struct Sack Sack;
typedef struct Group Group;

struct Letter {
	char	item;
	Letter*	next;
};

struct Sack {
	Letter*	comp1;
	int	size;
};

struct Group {
	Sack* elf_1;
	Sack* elf_2;
	Sack* elf_3;
};

Sack* build_sack()
{
	int	size;
	char	c;
	Letter*	first;
	Letter*	s;
	Sack*	l;

	/* Init first element */
	c = getchar();
	if (c == EOF || c == '\n') {
		return NULL;
	}
	first = malloc(sizeof(Sack));
	first->item = c;
	first->next = NULL;
	size = 1;

	s = first;
	
	while((c = getchar()) != EOF && c != '\n') {
		s->next = malloc(sizeof(Sack));
		s = s->next;
		s->item = c;
		s->next = NULL;
	}

	l = malloc(sizeof(Sack));
	l->comp1 = first;
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

Group* build_group()
{
	Group*	g;
	Sack*	l;

	l = build_sack();
	if (l == NULL) {
		return NULL;
	}

	g = malloc(sizeof(Group));

	g->elf_1 = l;
	g->elf_2 = build_sack();
	g->elf_3 = build_sack();

	return g;
}

void free_group(Group* g)
{
	free_sack(g->elf_1);
	free_sack(g->elf_2);
	free_sack(g->elf_3);

	free(g);
}

int is_in(char c, Sack* s)
{
	Letter*	l;

	l = s->comp1;

	while (l != NULL) {
		if (l->item == c) {
			return 1;
		}
		l = l->next;
	}
	return 0;
}

char get_badge(Group* g)
{
	Letter*	l;

	l = g->elf_1->comp1;

	while (l != NULL) {
		if (is_in(l->item, g->elf_2) && is_in(l->item, g->elf_3)) {
			return l->item;
		}
		l = l->next;
	}
	printf("ERROR\n");
	return 'a';
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

void solve(char* ans)
{
	int	tot_pts;
	Group*	g;

	tot_pts = 0;

	while ((g = build_group()) != NULL) {
		tot_pts += pts(get_badge(g));
		free_group(g);
	}

	sprintf(ans, "%d", tot_pts);
}

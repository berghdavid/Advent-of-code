#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct Game Game;

struct Game {
	char	elf;
	char	me;
	Game*	next;
};

Game* build_games()
{
	Game*	first;
	Game*	g;
	char	c;

	/* Init first element */
	first = malloc(sizeof(Game));
	first->elf = getchar();
	getchar();
	first->me = getchar();
	getchar();
	first->next = NULL;

	g = first;
	
	while((c = getchar()) != EOF) {
		g->next = malloc(sizeof(Game));
		g = g->next;
		g->elf = c;
		g->next = NULL;
		getchar();
		g->me = getchar();
		getchar();
	}

	return first;
}

void free_games(Game* first)
{
	Game*	i;
	Game*	temp;

	i = first;

	while (i != NULL) {
		temp = i->next;
		free(i);
		i = temp;
	}
}

int pts2(char elf, char me)
{
	int	score;
	int	pos;

	score = 0;

        if (me == 'Y') {
		score += 3;
	} else if (me == 'Z') {
		score += 6;
	}
	pos = score / 3;

	if (elf == 'C') {
		pos += 1;
	} else if (elf == 'A') {
		pos += 2;
	}
	pos = (pos % 3) + 1;

	return score + pos;
}

int sum_points(Game* g)
{
	Game*	i;
	int	sum;

	sum = 0;
	i = g;

	while (i != NULL) {
		sum += pts2(i->elf, i->me);
		i = i->next;
	}

	return sum;
}

int main(int argc, char *argv[])
{
	int     ans;
	Game*	g;

	g = build_games();

	ans = sum_points(g);

	printf("Task 2 ans: %d\n", ans);

	free_games(g);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "../common/utils.h"

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

int pts(char elf, char me)
{
	int	score;
	int	pos;

	score = 0;

	if (me == 'X') {
		score += 1;
	} else if (me == 'Y') {
		score += 2;
	} else {
		score += 3;
	}
	pos = score;

	if (elf == 'B') {
		pos += 2;
	} else if (elf == 'C') {
		pos += 1;
	}
	pos = pos % 3;

	return score + (pos * 3);
}

int sum_points(Game* g)
{
	Game*	i;
	int	sum;

	sum = 0;
	i = g;

	while (i != NULL) {
		sum += pts(i->elf, i->me);
		i = i->next;
	}

	return sum;
}

int main(void)
{
	int     ans;
	Game*	g;

	g = build_games();

	ans = sum_points(g);

	printf("Task 1 ans: %d\n", ans);

	free_games(g);
	return 0;
}

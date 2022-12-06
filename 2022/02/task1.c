#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
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

void solve(char* ans)
{
	int     pts;
	Game*	g;

	g = build_games();
	pts = sum_points(g);
	free_games(g);

	sprintf(ans, "%d", pts);
}

int main(int argc, char* argv[])
{
	char		ans[100];
	struct timeval	begin, end;
	long		seconds;
	long		microseconds;
	double		elapsed_ms;

	if (argc == 0) {
		return 0;
	}

	if (argc > 1 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&begin, 0);
		solve(ans);
		gettimeofday(&end, 0);

		seconds = end.tv_sec - begin.tv_sec;
		microseconds = end.tv_usec - begin.tv_usec;
		elapsed_ms = seconds*1e3 + microseconds*1e-3;
		printf("%s execution time: %.3f (ms)\n", argv[0], elapsed_ms);
	} else {
		solve(ans);
	}

	printf("%s ans: %s\n", argv[0], ans);

	return 0;
}

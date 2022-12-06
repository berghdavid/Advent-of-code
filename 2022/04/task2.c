#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "../common/utils.h"

typedef struct Team Team;

struct Team {
	int	min_1;
	int	max_1;
	int	min_2;
	int	max_2;
};

Team* build_team()
{
	Team*	t;

	t = malloc(sizeof(Team));
	
	if ((t->min_1 = next_int()) == -1) {
		free(t);
		return NULL;
	}

	t->max_1 = next_int();
	t->min_2 = next_int();
	t->max_2 = next_int();

	return t;
}

void free_team(Team* t)
{
	free(t);
}

int overlaps_range(Team* t)
{
	return (t->max_1 >= t->min_2 && t->min_1 <= t->max_2) ||
		(t->max_2 >= t->min_1 && t->min_2 <= t->max_1);
}

void solve(char* ans)
{
	int	overlaps;
	Team*	t;

	overlaps = 0;
	while ((t = build_team()) != NULL) {
		if (overlaps_range(t)) {
			overlaps++;
		}
		free_team(t);
	}
	sprintf(ans, "%d", overlaps);
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

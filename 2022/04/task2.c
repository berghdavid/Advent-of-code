#include <stdio.h>
#include <stdlib.h>
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

int solve()
{
	int	ans;
	Team*	t;

	ans = 0;
	while ((t = build_team()) != NULL) {
		if (overlaps_range(t)) {
			ans++;
		}
		free_team(t);
	}

	return ans;
}

int main(int argc, char *argv[])
{
	int	ans;

	ans = solve();

	printf("Task 2 ans: %d\n", ans);

	return 0;
}

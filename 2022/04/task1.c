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

int contains_range(Team* t)
{
	return (t->min_1 <= t->min_2 && t->max_1 >= t->max_2) ||
		(t->min_2 <= t->min_1 && t->max_2 >= t->max_1);
}

void solve(char* ans)
{
	int	in_range;
	Team*	t;

	in_range = 0;
	while ((t = build_team()) != NULL) {
		if (contains_range(t)) {
			in_range++;
		}
		free_team(t);
	}
	
	sprintf(ans, "%d", in_range);
}

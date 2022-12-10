#include <stdio.h>
#include <stdlib.h>
#include "../common/utils.h"

const int LEN = 1001;

typedef struct Knot Knot;

struct Knot {
	int	x;
	int	y;
};

Knot* init_knot()
{
	Knot*	k;

	k = malloc(sizeof(Knot));
	k->y = LEN/2;
	k->x = LEN/2;

	return k;
}

int norm(int n)
{
	if (n < 0) {
		return -1;
	} else if (n > 0) {
		return 1;
	}
	return 0;
}

void move_knot(Knot* k, int dy, int dx)
{
	k->y += dy;
	k->x += dx;
}

void follow_knot(Knot* head, Knot* tail)
{
	int	dy;
	int	dx;
	
	dy = head->y - tail->y;
	dx = head->x - tail->x;

	if (abs(dy) > 1 || abs(dx) > 1) {
		move_knot(tail, norm(dy), norm(dx));
	}
}

int make_moves(Knot* head, Knot* tail)
{
	int	i;
	int	j;
	int	n;
	int	visited;
	char	c;
	int**	grid;

	visited = 0;
	grid = malloc(LEN * sizeof(int*));

	for (i = 0; i < LEN; i++) {
		grid[i] = malloc(LEN * sizeof(int));
		for (j = 0; j < LEN; j++) {
			grid[i][j] = 0;
		}
	}

	grid[tail->y][tail->x] = 1;

	while ((c = getchar()) != EOF) {
		if (c == 'U') {
			i = 1;
			j = 0;
		} else if (c == 'D') {
			i = -1;
			j = 0;
		} else if (c == 'R') {
			i = 0;
			j = 1;
		} else if (c == 'L') {
			i = 0;
			j = -1;
		}

		getchar();
		n = next_int();
		for (; n > 0; n--) {
			move_knot(head, i, j);
			follow_knot(head, tail);
			grid[tail->y][tail->x] = 1;
		}
	}

	for (i = 0; i < LEN; i++) {
		for (j = 0; j < LEN; j++) {
			visited += grid[i][j];
		}
		free(grid[i]);
	}
	free(grid);

	return visited;
}

void solve(char* ans)
{
	int	sol;
	Knot*	head;
	Knot*	tail;

	head = init_knot();
	tail = init_knot();

	sol = make_moves(head, tail);

	free(head);
	free(tail);

	sprintf(ans, "%d", sol);
}

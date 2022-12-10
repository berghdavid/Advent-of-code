#include <stdio.h>
#include <stdlib.h>
#include "../common/utils.h"

const int LEN = 501;

typedef struct Knot Knot;

struct Knot {
	int	x;
	int	y;
};

Knot* init_knot()
{
	Knot*	k;

	k = malloc(sizeof(Knot));
	k->x = LEN/2;
	k->y = LEN/2;
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

void move_knot(Knot* k, int dx, int dy)
{
	k->x += dx;
	k->y += dy;
}

void follow_knot(Knot* head, Knot* tail)
{
	int	dx;
	int	dy;
	
	dx = head->x - tail->x;
	dy = head->y - tail->y;

	if (abs(dx) > 1 || abs(dy) > 1) {
		move_knot(tail, norm(dx), norm(dy));
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
		move_knot(head, i * n, j * n);
		getchar();

		follow_knot(head, tail);
		printf("Head: [%d, %d]\n", head->y, head->x);
		printf("Tail: [%d, %d]\n", tail->y, tail->x);
		grid[tail->y][tail->x] = 1;
	}

	for (i = 0; i < LEN; i++) {
		for (j = 0; j < LEN; j++) {
			visited += grid[i][j];
		}
	}

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

#include <stdio.h>
#include <stdlib.h>
#include "../common/utils.h"

const int LEN = 1001;

typedef struct Knot Knot;

struct Knot {
	int	x;
	int	y;
	Knot*	next;
};

Knot* init_knots(int nbr)
{
	int	i;
	Knot*	head;
	Knot*	k;

	head = malloc(sizeof(Knot));
	head->y = LEN/2;
	head->x = LEN/2;

	k = head;
	for (i = 0; i < nbr - 1; i++) {
		k->next = malloc(sizeof(Knot));
		k = k->next;
		k->y = LEN/2;
		k->x = LEN/2;
		k->next = NULL;
	}

	return head;
}

void clean_knots(Knot* head)
{
	Knot*	k;
	Knot*	temp;

	k = head;
	while (k != NULL) {
		temp = k->next;
		free(k);
		k = temp;
	}
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

int make_moves(Knot* head)
{
	int	i;
	int	j;
	int	n;
	int	visited;
	Knot*	k;
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

	grid[head->y][head->x] = 1;

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
			k = head;
			while (k->next != NULL) {
				follow_knot(k, k->next);
				k = k->next;
			}
			grid[k->y][k->x] = 1;
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

	head = init_knots(10);

	sol = make_moves(head);

	clean_knots(head);

	sprintf(ans, "%d", sol);
}

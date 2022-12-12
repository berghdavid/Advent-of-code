#include <stdio.h>
#include <stdlib.h>

const int rows = 41;
const int cols = 143;

typedef struct Hill Hill;
typedef struct Pos Pos;

struct Pos {
	int	x;
	int	y;
	int	h;
	int	d_start;
	Pos*	next;
};

struct Hill {
	Pos**	grid;
	Pos*	goal;
	Pos*	start;
	Pos*	first;
	Pos*	last;
};

Pos** init_grid()
{
	int	i;
	int	j;
	Pos**	grid;

	grid = malloc(rows * sizeof(Pos*));
	for (i = 0; i < rows; i++) {
		grid[i] = malloc(cols * sizeof(Pos));
		for (j = 0; j < cols; j++) {
			grid[i][j].x = j;
			grid[i][j].y = i;
			grid[i][j].d_start = -1;
			grid[i][j].next = NULL;
		}
	}

	return grid;
}

void free_grid(Pos** grid)
{
	int	i;

	for (i = 0; i < rows; i++) {
		free(grid[i]);
	}
	free(grid);
}

Hill* init_hill()
{
	int	i;
	int	j;
	Pos*	start;
	Pos*	goal;
	Pos**	grid;
	Hill*	hill;

	hill = malloc(sizeof(Hill));

	grid = init_grid();
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			grid[i][j].h = getchar() - 'a';
			if (grid[i][j].h == -14) {
				start = &grid[i][j];
				start->d_start = 0;
				start->h = 0;
				start->x = j;
				start->y = i;
			} else if (grid[i][j].h == -28) {
				goal = &grid[i][j];
				goal->h = 25;
				goal->x = j;
				goal->y = i;
			}
		}
		getchar();
	}

	hill->grid = grid;
	hill->start = start;
	hill->goal = goal;
	hill->first = NULL;
	hill->last = NULL;

	return hill;
}

void print_hill_height(Hill* hill)
{
	Pos**	grid;
	int	i;
	int	j;

	grid = hill->grid;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf(" %3d", grid[i][j].h);
		}
		printf("\n");
	}
}

void print_hill_dist(Hill* hill)
{
	Pos**	grid;
	int	i;
	int	j;

	grid = hill->grid;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf(" %3d", grid[i][j].d_start);
		}
		printf("\n");
	}
}

void free_hill(Hill* hill)
{
	free_grid(hill->grid);
	free(hill);
}

void push_work(Hill* hill, Pos* p)
{
	p->next = NULL;
	if (hill->first == NULL) {
		hill->first = p;
	} else {
		hill->last->next = p;
	}
	hill->last = p;
}

Pos* pop_work(Hill* hill)
{
	Pos*	p;

	p = hill->first;
	if (p != NULL) {
		hill->first = p->next;
		p->next = NULL;
	}
	if (p == hill->last) {
		hill->last = NULL;
	}

	return p;
}

void set_pos_len(Hill* hill, Pos* p1, Pos* p2)
{
	int	new_len;
	
	new_len = p1->d_start + 1;
	if ((p2->d_start == -1 || p2->d_start > new_len) && p2->h - p1->h <= 1) {
		p2->d_start = new_len;
		push_work(hill, p2);
	}
}

void set_neighbours(Hill* hill, Pos* p)
{
	if (0 < p->y) {
		set_pos_len(hill, p, &hill->grid[p->y - 1][p->x]);
	}
	if (p->y < rows - 1) {
		set_pos_len(hill, p, &hill->grid[p->y + 1][p->x]);
	}
	if (0 < p->x) {
		set_pos_len(hill, p, &hill->grid[p->y][p->x - 1]);
	}
	if (p->x < cols - 1) {
		set_pos_len(hill, p, &hill->grid[p->y][p->x + 1]);
	}
}

void set_lengths(Hill* hill)
{
	push_work(hill, hill->start);

	Pos*	p;
	while ((p = pop_work(hill)) != NULL) {
		set_neighbours(hill, p);
	}
}

void solve(char* ans)
{
	Hill*	hill;
	int	max;

	hill = init_hill();
	set_lengths(hill);

	max = hill->goal->d_start;

	free_hill(hill);

	sprintf(ans, "%d", max);
}

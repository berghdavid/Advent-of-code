#include <stdio.h>
#include <stdlib.h>

const int rows = 41;
const int cols = 143;

typedef struct Hill Hill;
typedef struct Pos Pos;

struct Pos {
	int	x;
	int	y;
};

struct Hill {
	int**	grid;
	Pos*	goal;
	Pos*	start;
};

Hill* init_hill()
{
	int	i;
	int	j;
	Pos*	start;
	Pos*	goal;
	int**	grid;
	Hill*	hill;

	hill = malloc(sizeof(Hill));
	start = malloc(sizeof(Pos));
	goal = malloc(sizeof(Pos));

	grid = malloc(rows * sizeof(int*));
	for (i = 0; i < rows; i++) {
		grid[i] = malloc(cols * sizeof(int));
		for (j = 0; j < cols; j++) {
			grid[i][j] = getchar() - 'a';
			if (grid[i][j] == -14) {
				grid[i][j] = 0;
				start->x = j;
				start->y = i;
			} else if (grid[i][j] == -28) {
				grid[i][j] = 25;
				goal->x = j;
				goal->y = i;
			}
		}
		getchar();
	}

	hill->grid = grid;
	hill->start = start;
	hill->goal = goal;

	return hill;
}

void print_hill(Hill* hill)
{
	int**	grid;
	int	i;
	int	j;

	grid = hill->grid;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf(" %2d", grid[i][j]);
		}
		printf("\n");
	}
}

void free_hill(Hill* hill)
{
	int**	grid;
	int	i;

	grid = hill->grid;
	for (i = 0; i < rows; i++) {
		free(grid[i]);
	}

	free(grid);
	free(hill->start);
	free(hill->goal);
	free(hill);
}

int can_move_to(Hill* hill, int x1, int y1, int x2, int y2)
{
	return (abs(x2 - x1) + abs(y2 - y1) == 1 &&
		abs(hill->grid[y2][x2] - hill->grid[y1][x1]) < 2);
}

void solve(char* ans)
{
	Hill*	hill;
	int	max;

	hill = init_hill();
	print_hill(hill);

	max = 0;

	free_hill(hill);

	sprintf(ans, "%d", max);
}

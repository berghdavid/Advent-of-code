#include <stdio.h>
#include <stdlib.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))

const int LEN = 99;

int** init_grid()
{
	int	i;
	int**	grid;

	grid = malloc(LEN * sizeof(int*));

	for (i = 0; i < LEN; i++) {
		grid[i] = malloc(LEN * sizeof(int));
	}

	return grid;
}

void read_to_grid(int** grid)
{
	int	i;
	int	j;

	for (i = 0; i < LEN; i++) {
		for (j = 0; j < LEN; j++) {
			grid[i][j] = getchar() - '0';
		}
		getchar();
	}
}

void print_grid(int** grid)
{
	int	i;
	int	j;

	for (i = 0; i < LEN; i++) {
		for (j = 0; j < LEN; j++) {
			printf("%d", grid[i][j]);
		}
		printf("\n");
	}
}

void clean_grid(int** grid)
{
	int	i;

	for (i = 0; i < LEN; i++) {
		free(grid[i]);
	}
	free(grid);
}

int tree_score(int** grid, int row, int col)
{
	int	i;
	int	n;
	int	h;
	int	score;

	score = 1;

	n = 0;
	for (i = col + 1; i < LEN; i++) {
		h = grid[row][i];
		n++;
		if (h >= grid[row][col]) {
			break;
		}
	}
	score *= n;
	
	n = 0;
	for (i = row + 1; i < LEN; i++) {
		h = grid[i][col];
		n++;
		if (h >= grid[row][col]) {
			break;
		}
	}
	score *= n;

	n = 0;
	for (i = col - 1; i >= 0; i--) {
		h = grid[row][i];
		n++;
		if (h >= grid[row][col]) {
			break;
		}
	}
	score *= n;

	n = 0;
	for (i = row - 1; i >= 0; i--) {
		h = grid[i][col];
		n++;
		if (h >= grid[row][col]) {
			break;
		}
	}
	score *= n;

	return score;
}

int max_score(int** grid)
{
	int	i;
	int	j;
	int	score;

	score = 1;
	for (i = 1; i < LEN - 1; i++) {
		for (j = 1; j < LEN - 1; j++) {
			score = max(score, tree_score(grid, i, j));
		}
	}
	return score;
}

void solve(char* ans)
{
	int	sol;
	int**	grid;

	grid = init_grid();
	read_to_grid(grid);

	sol = max_score(grid);

	sprintf(ans, "%d", sol);

	clean_grid(grid);
}

#include <stdio.h>
#include <stdlib.h>

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

int** get_hidden(int** grid)
{
	int	i;
	int	j;
	int	n;
	int	max;
	int**	hidden;

	hidden = init_grid();

	for (i = 0; i < LEN; i++) {
		for (j = 0; j < LEN; j++) {
			hidden[i][j] = 1;
		}
	}

	for (i = 0; i < LEN; i++) {
		hidden[i][0] = 0;
		hidden[i][LEN - 1] = 0;
		hidden[0][i] = 0;
		hidden[LEN - 1][i] = 0;
	}

	for (i = 1; i < LEN - 1; i++) {
		/* Check viewable from left */
		max = grid[i][0];
		for (j = 1; j < LEN - 1; j++) {
			n = grid[i][j];
			if (n > max) {
				max = n;
				hidden[i][j] = 0;
				if (max == 9) {
					break;
				}
			}
		}

		/* Check viewable from right */
		max = grid[i][LEN - 1];
		for (j = LEN - 1; j > 0; j--) {
			n = grid[i][j];
			if (n > max) {
				max = n;
				hidden[i][j] = 0;
				if (max == 9) {
					break;
				}
			}
		}

		/* Check viewable from up */
		max = grid[0][i];
		for (j = 1; j < LEN - 1; j++) {
			n = grid[j][i];
			if (n > max) {
				max = n;
				hidden[j][i] = 0;
				if (max == 9) {
					break;
				}
			}
		}

		/* Check viewable from down */
		max = grid[LEN - 1][i];
		for (j = LEN - 1; j > 0; j--) {
			n = grid[j][i];
			if (n > max) {
				max = n;
				hidden[j][i] = 0;
				if (max == 9) {
					break;
				}
			}
		}
	}

	return hidden;
}

int visible(int** hidden)
{
	int	i;
	int	j;
	int	n;

	n = LEN*LEN;
	for (i = 0; i < LEN; i++) {
		for (j = 0; j < LEN; j++) {
			n -= hidden[i][j];
		}
	}
	return n;
}

void solve(char* ans)
{
	int	sol;
	int**	grid;
	int**	hidden;

	grid = init_grid();
	read_to_grid(grid);
	hidden = get_hidden(grid);

	sol = visible(hidden);

	sprintf(ans, "%d", sol);

	clean_grid(grid);
	clean_grid(hidden);
}

#include <stdio.h>
#include <stdlib.h>
#include "../../../utils/submit.c"
#include "../../../utils/utils.c"


int valid(int dir, int prev_val, int new_val)
{
	int	min;
	int	max;
	
	if (dir == 1) {
		min = prev_val + dir;
		max = prev_val + 3 * dir;
	} else {
		max = prev_val + dir;
		min = prev_val + 3 * dir;
	}
	return (min <= new_val && new_val <= max);
}

Pack* parse_row()
{
	Pack*	curr;
	int	prev;
	int	dir;

	curr = NULL;
	prev = 0;
	dir = 0;
	while (1) {
		curr = next_positive_int3();

		if (prev == 0) {
			// First iteration has no prev, if bad row just skip
			prev = curr->val;
			free(curr);
			continue;
		}

		if (dir == 0) {
			if (curr->val < prev) {
				dir = -1;
			} else if (curr->val > prev) {
				dir = 1;
			} else {
				curr->val = 0;
				curr->end = read_to_end();
				break;
			}
		}
		if (!valid(dir, prev, curr->val)) {
			curr->val = 0;
			curr->end = read_to_end();
			break;
		}

		if (curr->end == EOF || curr->end == '\n') {
			curr->val = 1;
			break;
		}

		prev = curr->val;
		free(curr);
	}
	return curr;
}

int main(int argc, char* argv[])
{
	char	ans[2048];
	Pack*	res;
	int	sum;

	sum = 0;
	while ((res = parse_row()) && res->end != EOF) {
		sum += res->val;
		free(res);
	}
	free(res);

	printf("Ans: %d\n", sum);
	sprintf(ans, "%d", sum);

	if (argc == 3) {
		// Post answer to AoC
		submit(ans, argv[1], argv[2]);
	}
}

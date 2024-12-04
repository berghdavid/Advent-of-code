#include <stdio.h>
#include "../../../utils/utils.c"
#include "tree.h"

int matches(Entry* left, Tree* right)
{
	Entry*	e;
	int	sum;

	sum = 0;
	e = bst_get(right, left->key);
	if (e) {
		sum += left->key * e->val;
	}
	if (left->left) {
		sum += matches(left->left, right);
	}
	if (left->right) {
		sum += matches(left->right, right);
	}
	return sum;
}

int main(int argc, char* argv[])
{
	char	ans[2048];
	int	curr;
	int	counter;
	int	sum;
	Tree*	left;
	Tree*	right;
	Entry*	e;

	left = bst_init();
	right = bst_init();

	counter = 0;
	while((curr = next_positive_int()) >= 0) {
		if (counter % 2 == 0) {
			e = bst_get(left, curr);
			if (!e) {
				e = init_entry(curr);
				bst_insert(left, curr);
			} else {
				e->val++;
			}
		} else {
			e = bst_get(right, curr);
			if (!e) {
				e = init_entry(curr);
				bst_insert(right, curr);
			} else {
				e->val++;
			}
		}
		counter++;
	}

	sum = matches(left->root, right);

	bst_destroy(left);
	bst_destroy(right);

	printf("Ans: %d\n", sum);
	sprintf(ans, "%d", sum);

	if (argc == 3) {
		submit(ans, argv[1], argv[2]);
	}
}

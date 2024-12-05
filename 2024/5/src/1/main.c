#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../../utils/submit.c"
#include "../../../utils/utils.c"
#include "tree.h"

static void list_insert_existing(List* l, Tree* t, int x)
{
	Node*	n;

	n = bst_get(t, x);
	if (n) {
		list_append(l, n);
	}
}

static List* read_line(Tree* t)
{
	int	x;
	int	c;
	List*	l;

	l = list_init();
	while (1) {
		c = getchar();
		while (!isdigit(c)) {
			if (c == '\n') {
				return l;
			} else if (c == EOF) {
				list_destroy(l);
				return NULL;
			}
			c = getchar();
		}

		x = 0;
		while (isdigit(c)) {
			x = 10 * x + c - '0';
			c = getchar();
		}
		list_insert_existing(l, t, x);
		if (c == '\n') {
			return l;
		} else if (c == EOF) {
			list_destroy(l);
			return NULL;
		}
	}

	return l;
}

static int is_valid(Node* n, Tree* t)
{
	Node*	curr;

	curr = n->next;
	while (curr) {
		if (curr->index < n->index) {
			return 0;
		}
		curr = curr->next;
	}
	return 1;
}

static int middle_val(List* row, Tree* t)
{
	Node*	middle;
	Node*	curr;
	int	sum;
	int	counter;

	counter = 0;
	curr = row->first;
	middle = row->first;
	while (curr) {
		if (!is_valid(curr, t)) {
			return 0;
		}

		if (counter % 2 == 1) {
			middle = middle->prev;
		}
		curr = curr->next;
		counter++;
	}
	return middle->key;
}

static int check_updates(Tree* t)
{
	int	curr;
	List*	l;
	Node*	n;
	int	sum;
	int	counter;

	sum = 0;
	while (1) {
		l = read_line(t);
		if (!l) {
			break;
		}

		if (l->size == 0) {
			list_destroy(l);
			continue;
		}

		sum += middle_val(l, t);

		list_destroy(l);
	}
	return sum;
}

static void compute_indices_rec(Node* n)
{
	Node*	tmp;
	int	i;

	if (n->flag) {
		return;
	}

	n->index = 99999;
	n->flag = 1;
	for (i = 0; i < n->afters->size; i++) {
		tmp = n->afters->node[i];
		if (!tmp->flag) {
			compute_indices_rec(tmp);
		}
		if (tmp->index < n->index) {
			n->index = tmp->index;
		}
	}
	n->index--;
}

static void compute_node_rec(Node* n)
{
	if (!n) {
		return;
	}
	printf("Computing %d\n", n->key);

	compute_indices_rec(n);

	compute_node_rec(n->left);
	compute_node_rec(n->right);
}

static void prep_tree(Node* n)
{
	if (!n) {
		return;
	}
	n->flag = 0;
	stack_sort(n->afters);
	prep_tree(n->left);
	prep_tree(n->right);
}

int main(int argc, char* argv[])
{
	char	ans[2048];
	Tree*	t;
	int	curr;
	int	prev;
	int	counter;
	int	sum;

	t = bst_init();
	sum = 0;
	counter = 0;
	prev = -1;
	while((curr = next_positive_int2()) != -1) {
		if (curr == -2) {
			break;
		}

		if (counter % 2 == 0) {
			prev = curr;
		} else {
			bst_insert(t, prev, curr);
			prev = -1;
		}

		counter++;
	}

	prep_tree(t->root);
	compute_indices_rec(t->root);

	sum = check_updates(t);

	bst_destroy(t);

	printf("Ans: %d\n", sum);
	sprintf(ans, "%d", sum);

	if (argc == 3) {
		// Post answer to AoC
		submit(ans, argv[1], argv[2]);
	}
}

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

Entry* init_entry(int key)
{
	Entry*	e;

	e = malloc(sizeof(Entry));
	e->height = 0;
	e->key = key;
	e->left = NULL;
	e->right = NULL;
	e->parent = NULL;
	e->val = 1;
	return e;
}

/**
 * @brief Get the maximum of 2 integers.
 */
static int max(int a, int b) {
	return (a > b) ? a : b;
}

/**
 * @brief Get height of entry in BST.
 * @param e Entry (or node) that has been admitted to the BST.
 * @return 0 if entry is NULL, otherwise get the height field.
 */
static int bst_height(Entry* e)
{
	if (e) {
		return e->height;
	}
	return 0;
}

/**
 * @brief Compute and set the correct height for the provided entry.
 * @param e Entry (or node) that has been admitted to the BST.
 */
static void bst_update_height(Entry* e)
{
	if (e) {
		e->height = 1 + max(bst_height(e->left), bst_height(e->right));
	}
}

static int bst_get_balance(Entry* node) {
	if (node) {
		return bst_height(node->left) - bst_height(node->right);
	}
	return 0;
}

/**
 * @brief Get the leftmost entry.
 * @param e Entry (or node) that has been admitted to the BST.
 * @return Entry that has no left child.
 */
static Entry* bst_get_leftmost(Entry* e)
{
	while (e->left) {
		e = e->left;
	}
	return e;
}

/**
 * @brief Rotate nodes in BST left. Used during balancing.
 */
static Entry* bst_rotate_left(Entry* p)
{
	Entry*	e1;
	Entry*	e2;

	e1 = p->right;
	e2 = e1->left;

	/* Rotate */
	e1->left = p;
	p->right = e2;

	/* Update pointers */
	if (e2) {
		e2->parent = p;
	}
	e1->parent = p->parent;
	p->parent = e1;

	bst_update_height(p);
	bst_update_height(e1);
	return e1;
}

/**
 * @brief Rotate nodes in BST right. Used during balancing.
 */
static Entry* bst_rotate_right(Entry* p)
{
	Entry*	e1;
	Entry*	e2;

	e1 = p->left;
	e2 = e1->right;

	/* Rotate */
	e1->right = p;
	p->left = e2;

	/* Update pointers */
	if (e2) {
		e2->parent = p;
	}
	e1->parent = p->parent;
	p->parent = e1;

	bst_update_height(p);
	bst_update_height(e1);
	return e1;
}

/**
 * @brief Balance the BST. Perform after insertion or deletion.
 */
static Entry* bst_balance(Entry* e)
{
	int	balance;

	bst_update_height(e);
	balance = bst_get_balance(e);

	if (balance > 1) {
		if (bst_get_balance(e->left) < 0) {
			/* Left Right Case */
			e->left = bst_rotate_left(e->left);
		}
		return bst_rotate_right(e);
	}

	if (balance < -1) {
		if (bst_get_balance(e->right) > 0) {
			/* Right Left Case */
			e->right = bst_rotate_right(e->right);
		}
		return bst_rotate_left(e);
	}

	return e;
}

/**
 * @brief Remove entry from BST, returns the replacing entry
 */ 
static Entry* bst_remove(const Entry* e) {
	Entry*	b;	// Entry to start balancing from
	Entry*	rep;	// Entry to replace e's position

	b = e->parent;

	if (!e->left && !e->right) {
		// e has no children
		rep = NULL;
	} else if (!e->left) {
		// e has 1 child (right)
		rep = e->right;
	} else if (!e->right) {
		// e has 1 child (left)
		rep = e->left;
	} else {
		// e has two children
		// Note: tmp is guaranteed to not have a left node
		rep = bst_get_leftmost(e->right);
		b = rep->parent;

		if (rep != e->right) {
			if (rep->right) {
				// tmp has right subtree
				rep->parent->left = rep->right;
				rep->right->parent = rep->parent;
			} else {
				// tmp is leaf node
				rep->parent->left = NULL;
			}

			rep->right = e->right;
			e->right->parent = rep;
		}

		rep->left = e->left;
		e->left->parent = rep;
	}

	// Set parent-child relations with replacement
	if (rep) {
		rep->parent = e->parent;
	}
	if (e->parent) {
		if (e->parent->left == e) {
			e->parent->left = rep;
		} else {
			e->parent->right = rep;
		}
	}

	// Update heights and balance the tree
	while (b) {
		b = bst_balance(b);
		b = b->parent;
	}

	return rep;
}

Tree* bst_init()
{
	Tree*	t;

	t = calloc(1, sizeof(Tree));
	return t;
}

void free_entry(Entry* e)
{
	if (e->left) {
		free_entry(e->left);
	}
	if (e->right) {
		free_entry(e->right);
	}
	free(e);
}

void bst_destroy(Tree* t)
{
	free_entry(t->root);
	free(t);
}

/**
 * @brief Insert a new entry into BST using recursion.
 * @param curr Current position in BST.
 * @param e Entry to be inserted.
 * @return Entry that should be in the place of the @p curr entry, or the
 * @p curr entry itself if it is correctly positioned.
 */
static Entry* bst_insert_rec(Entry* curr, int key)
{
	if (!curr) {
		return init_entry(key);
	}
	if (key == curr->key) {
		curr->val++;
		return curr;
	}

	if (key < curr->key) {
		curr->left = bst_insert_rec(curr->left, key);
		// TODO: Only set parent after insertion of new entry
		curr->left->parent = curr;
	} else {
		curr->right = bst_insert_rec(curr->right, key);
		// TODO: Only set parent after insertion of new entry
		curr->right->parent = curr;
	}

	return bst_balance(curr);
}

void bst_insert(Tree* t, int key)
{
	t->root = bst_insert_rec(t->root, key);
}

Entry* bst_get(Tree* t, int key)
{
	Entry*	e;

	e = t->root;
	while (e && e->key != key) {
		if (key < e->key) {
			e = e->left;
		} else {
			e = e->right;
		}
	}
	return e;
}

/**
 * @brief Print 2 spaces per indentation step.
 */
static void bst_print_indented(int indentation)
{
	for (int i = 0; i < indentation; i++) {
		printf("  ");
	}
}

/**
 * @brief Print an entry and its children recursively.
 */
static void bst_print_rec(int max_height, Entry* e)
{
	int	indentation;

	if (!e) {
		return;
	}
	indentation = max_height - e->height;

	bst_print_indented(indentation);
	printf("+-----------------------\n");
	bst_print_indented(indentation);
	printf("| Key:         %d\n", e->key);
	bst_print_indented(indentation);
	if (e->parent) {
		printf("| Parent:      %d\n", e->parent->key);
	} else {
		printf("| Parent:      NULL\n");
	}
	bst_print_indented(indentation);
	if (e->left) {
		printf("| Left child:  %d\n", e->left->key);
	} else {
		printf("| Left child:  NULL\n");
	}
	bst_print_indented(indentation);
	if (e->right) {
		printf("| Right child: %d\n", e->right->key);
	} else {
		printf("| Right child: NULL\n");
	}
	bst_print_indented(indentation);
	printf("| Height:      %d\n", e->height);
	bst_print_indented(indentation);

	bst_print_rec(max_height, e->left);
	bst_print_rec(max_height, e->right);
}

void bst_print(Tree* tree)
{
	printf("----------------- BST --------------\n");
	if (tree && tree->root) {
		bst_print_rec(tree->root->height, tree->root);
	}
	printf("------------------------------------\n");
}

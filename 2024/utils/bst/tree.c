#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;
typedef struct Tree Tree;

/* Key-value pair, referenced in the BST and the LFU list */
struct Node {
	Node*	left;	/* Left node in BST		*/
	Node*	right;	/* Right node in BST		*/
	Node*	parent;	/* Parent node in BST		*/
	int	key;	/* Key in binary search tree	*/
	int	val;	/* Held object			*/
	int	height;	/* Height of this node in BST	*/
};

/* Used as BST */
struct Tree {
	Node*	root;
};

Node* init_node(int key, int val)
{
	Node*	e;

	e = malloc(sizeof(Node));
	e->height = 0;
	e->key = key;
	e->left = NULL;
	e->right = NULL;
	e->parent = NULL;
	e->val = val;
	return e;
}

/**
 * @brief Get the maximum of 2 integers.
 */
static int max(int a, int b) {
	return (a > b) ? a : b;
}

/**
 * @brief Get height of node in BST.
 * @param e Node (or node) that has been admitted to the BST.
 * @return 0 if node is NULL, otherwise get the height field.
 */
static int bst_height(Node* e)
{
	if (e) {
		return e->height;
	}
	return 0;
}

/**
 * @brief Compute and set the correct height for the provided node.
 * @param e Node (or node) that has been admitted to the BST.
 */
static void bst_update_height(Node* e)
{
	if (e) {
		e->height = 1 + max(bst_height(e->left), bst_height(e->right));
	}
}

static int bst_get_balance(Node* node) {
	if (node) {
		return bst_height(node->left) - bst_height(node->right);
	}
	return 0;
}

/**
 * @brief Get the leftmost node.
 * @param e Node (or node) that has been admitted to the BST.
 * @return Node that has no left child.
 */
static Node* bst_get_leftmost(Node* e)
{
	while (e->left) {
		e = e->left;
	}
	return e;
}

/**
 * @brief Rotate nodes in BST left. Used during balancing.
 */
static Node* bst_rotate_left(Node* p)
{
	Node*	e1;
	Node*	e2;

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
static Node* bst_rotate_right(Node* p)
{
	Node*	e1;
	Node*	e2;

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
static Node* bst_balance(Node* e)
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
 * @brief Remove node from BST, returns the replacing node
 */ 
static Node* bst_remove(const Node* e) {
	Node*	b;	// Node to start balancing from
	Node*	rep;	// Node to replace e's position

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

void free_node(Node* e)
{
	if (e->left) {
		free_node(e->left);
	}
	if (e->right) {
		free_node(e->right);
	}
	free(e);
}

void bst_destroy(Tree* t)
{
	free_node(t->root);
	free(t);
}

/**
 * @brief Insert a new node into BST using recursion.
 * @param curr Current position in BST.
 * @return Node that should be in the place of the @p curr node, or the
 * @p curr node itself if it is correctly positioned.
 */
static Node* bst_insert_rec(Node* curr, int key, int val)
{
	if (!curr) {
		return init_node(key, val);
	}
	if (key == curr->key) {
		return curr;
		// Do something if node exists?
	}

	if (key < curr->key) {
		curr->left = bst_insert_rec(curr->left, key, val);
		// TODO: Only set parent after insertion of new node
		curr->left->parent = curr;
	} else {
		curr->right = bst_insert_rec(curr->right, key, val);
		// TODO: Only set parent after insertion of new node
		curr->right->parent = curr;
	}

	return bst_balance(curr);
}

void bst_insert(Tree* t, int key, int val)
{
	t->root = bst_insert_rec(t->root, key, val);
}

/**
 * @brief Find the node in the BST with the provided key. This function
 * is NOT thread safe, and requires the BST to be locked.
 * @param t BST.
 * @param key Key to look for, of type unsigned long long.
 * @return Node with the same key, or NULL if none exists.
 */
Node* bst_get(Tree* t, int key)
{
	Node*	e;

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

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

Node*	FETCHED = NULL;

Stack* stack_init()
{
	Stack*	s;

	s = malloc(sizeof(Stack));
	s->size = 0;
	s->node = NULL;
	return s;
}

static int compare_ptrs(const void* a, const void* b)
{
	Node* obj1 = *(Node**)a;
	Node* obj2 = *(Node**)b;

	if (obj1 < obj2) {
		return -1;
	} else if (obj1 > obj2) {
		return 1;
	}
	return 0;
}

int stack_contains(Stack* s, Node* n)
{
	int	left;
	int	right;
	int	mid;
	
	if (!n) {
		return 0;
	}

	left = 0;
	right = s->size - 1;
	while (left <= right) {
		mid = left + (right - left) / 2;

		if (s->node[mid] < n) {
			left = mid + 1;
		} else if (s->node[mid] > n) {
			right = mid - 1;
		} else {
			return s->node[mid] == n;
		}
	}
}

void stack_sort(Stack* s)
{
	qsort(s->node, s->size, sizeof(Node*), compare_ptrs);
}

void stack_append(Stack* s, Node* n)
{
	if (!n) {
		return;
	}
	s->size++;
	s->node = realloc(s->node, s->size * sizeof(Node*));
	s->node[s->size - 1] = n;
}

Stack* stack_destroy(Stack* s)
{
	free(s->node);
	free(s);
}

Node* node_init(int key, Node* n)
{
	Node*	e;

	e = malloc(sizeof(Node));
	e->height = 0;
	e->key = key;
	e->left = NULL;
	e->right = NULL;
	e->parent = NULL;
	e->prev = NULL;
	e->next = NULL;
	e->afters = stack_init();
	e->flag = 0;
	e->index = 10000;
	stack_append(e->afters, n);
	return e;
}

List* list_init()
{
	List*	l;

	l = calloc(1, sizeof(List));
	return l;
}

void list_destroy(List* l)
{
	Node*	n;
	Node*	tmp;

	n = l->first;
	while (n) {
		tmp = n->next;
		n->next = NULL;
		n->prev = NULL;
		n = tmp;
	}
	free(l);
}

void list_append(List* l, Node* n)
{
	n->next = NULL;
	if (l->last) {
		l->last->next = n;
	} else {
		l->first = n;
	}
	n->prev = l->last;
	l->last = n;
	l->size++;
}

Node* list_pop(List* l)
{
	Node*	n;

	if (!l->first) {
		return NULL;
	}
	n = l->first;
	if (n->next) {
		n->next->prev = NULL;
	} else {
		l->last = NULL;
	}
	l->first = n->next;
	l->size--;
	return n;
}

/**
 * @brief Remove an entry from the LFU list. Is NOT thread safe.
 * @param l List to remove entry from.
 * @param e Elem to be removed from list, assumed to be within @p l.
 */
static void list_remove(List* l, Node* n)
{
	if (n->prev) {
		n->prev->next = n->next;
	} else {
		l->first = n->next;
	}
	if (n->next) {
		n->next->prev = n->prev;
	} else {
		l->last = n->prev;
	}
	l->size--;
}

void list_move_to_back(List* l, Node* n)
{
	if (l->last == n) {
		return;
	}
	n->next->prev = n->prev;

	if (l->first == n) {
		l->first = n->next;
	} else {
		n->prev->next = n->next;
	}

	n->prev = l->last;
	n->next = NULL;

	l->last->next = n;
	l->last = n;
}

void list_print(List* l)
{
	Node*	n;
	int	i;

	printf("-------------- LFU list ------------\n");
	printf("%-6s  %-19s\n", "Index", "Key");
	printf("------------------------------------\n");
	n = l->first;
	i = 0;
	while (n) {
		printf("%-6d: %-19d\n", i, n->key);
		n = n->next;
		i++;
	}
	printf("------------------------------------\n");
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

void node_destroy(Node* n)
{
	stack_destroy(n->afters);
	free(n);
}

void node_destroy_rec(Node* n)
{
	if (n->left) {
		node_destroy_rec(n->left);
	}
	if (n->right) {
		node_destroy_rec(n->right);
	}
	node_destroy(n);
}

void bst_destroy(Tree* t)
{
	node_destroy_rec(t->root);
	free(t);
}

/**
 * @brief Insert a new node into BST using recursion.
 * @param curr Current position in BST.
 * @param e Node to be inserted.
 * @return Node that should be in the place of the @p curr node, or the
 * @p curr node itself if it is correctly positioned.
 */
static Node* bst_insert_fetch_rec(Node* curr, int key, Node* after)
{
	Node*	ptr;

	if (!curr) {
		FETCHED = node_init(key, after);
		return FETCHED;
	}
	if (key == curr->key) {
		stack_append(curr->afters, after);
		FETCHED = curr;
		return curr;
	}

	if (key < curr->key) {
		curr->left = bst_insert_fetch_rec(curr->left, key, after);
		curr->left->parent = curr;
	} else {
		curr->right = bst_insert_fetch_rec(curr->right, key, after);
		curr->right->parent = curr;
	}

	return bst_balance(curr);
}

void bst_insert(Tree* t, int key, int val)
{
	Node*	val_node;

	t->root = bst_insert_fetch_rec(t->root, val, NULL);
	t->root = bst_insert_fetch_rec(t->root, key, FETCHED);
}

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
 * @brief Print an node and its children recursively.
 */
static void bst_print_rec(int max_height, Node* e)
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
	printf("| Index:       %d\n", e->index);
	bst_print_indented(indentation);
	printf("| Flag:        %d\n", e->flag);

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

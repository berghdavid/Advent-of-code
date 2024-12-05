#ifndef TREE_H
#define TREE_H

typedef struct Stack Stack;
typedef struct Node Node;
typedef struct List List;
typedef struct Tree Tree;

struct Stack {
	size_t	size;
	Node**	node;	/* Stack of node references	*/
};

/* Key-value pair, referenced in the BST and the LFU list */
struct Node {
	int	key;	/* Key in binary search tree	*/
	Node*	left;	/* Left node in BST		*/
	Node*	right;	/* Right node in BST		*/
	Node*	prev;	/* First item in list		*/
	Node*	next;	/* Last item in list		*/
	Node*	parent;	/* Parent node in BST		*/
	Stack*	afters;	/* Stack of after nodes		*/
	int	height;	/* Height of this node in BST	*/
	int	flag;	/* Whether the node is new	*/
	int	index;	/* List index			*/
};

struct List {
	Node*	first;	/* First item in list		*/
	Node*	last;	/* Last item in list		*/
	int	size;	/* List size			*/
};

/* Used as BST */
struct Tree {
	Node*	root;
};

Stack* stack_init();

void stack_sort(Stack* s);

int stack_contains(Stack* s, Node* n);

void stack_append(Stack* s, Node* n);

Stack* stack_destroy(Stack* s);

/* Initialize empty LFU list object. */
List* list_init();

/* Release the memory held by the list, but not its contained elements. */
void list_destroy(List* l);

/* Append entry to list. Assumes that entry is not already in the list. */
void list_append(List* l, Node* n);

/* Pop and return the first entry from the list. Is NOT thread-safe. */
Node* list_pop(List* l);

/* Append entry to list. Assumes that entry already is in list. */
void list_move_to_back(List* l, Node* n);

/* Print the objects held by the LFU list. */
void list_print(List* l);

Node* node_init(int key, Node* n);

void node_destroy(Node* n);

void node_destroy_rec(Node* n);

/* Initialize empty BST object. */
Tree* bst_init();

/* Release the memory held by the tree, but not its contained elements. */
void bst_destroy(Tree* t);

/* Insert a new node into the BST. Replaces existing node with same key. */
void bst_insert(Tree* t, int key, int val);

/**
 * @brief Find the node in the BST with the provided key. This function
 * is NOT thread safe, and requires the BST to be locked.
 * @param t BST.
 * @param key Key to look for, of type unsigned long long.
 * @return Node with the same key, or NULL if none exists.
 */
Node* bst_get(Tree* t, int key);

/* Print the objects held by the BST. */
void bst_print(Tree* tree);

#endif

#ifndef TREE_H
#define TREE_H

typedef struct Entry Entry;
typedef struct Tree Tree;

/* Key-value pair, referenced in the BST and the LFU list */
struct Entry {
	int	key;	/* Key in binary search tree	*/
	Entry*	left;	/* Left node in BST		*/
	Entry*	right;	/* Right node in BST		*/
	Entry*	parent;	/* Parent node in BST		*/
	int	val;	/* Held object			*/
	int	height;	/* Height of this node in BST	*/
};

/* Used as BST */
struct Tree {
	Entry*	root;
};

Entry* init_entry(int key);

void free_entry(Entry* e);

/* Initialize empty BST object. */
Tree* bst_init();

/* Release the memory held by the tree, but not its contained elements. */
void bst_destroy(Tree* t);

/* Insert a new entry into the BST. Replaces existing entry with same key. */
void bst_insert(Tree* t, int e);

/**
 * @brief Find the entry in the BST with the provided key. This function
 * is NOT thread safe, and requires the BST to be locked.
 * @param t BST.
 * @param key Key to look for, of type unsigned long long.
 * @return Entry with the same key, or NULL if none exists.
 */
Entry* bst_get(Tree* t, int key);

/* Print the objects held by the BST. */
void bst_print(Tree* tree);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

const int MARKER_LENGTH = 14;
const char EMPTY = '-';

typedef struct Node Node;
typedef struct List List;

struct Node {
	char	c;
	Node*	prev;
	Node*	next;
};

struct List {
	Node*	first;
	Node*	last;
};

List* build_nodes(int size)
{
	int	i;
	Node*	n;
	List*	l;

	l = malloc(sizeof(List));
	l->first = malloc(sizeof(Node));

	n = l->first;
	n->c = EMPTY;
	n->prev = NULL;
	n->next = NULL;

	for (i = 0; i < size - 1; i++) {
		n->next = malloc(sizeof(Node));
		n->next->prev = n;
		n->next->next = NULL;
		n->next->c = EMPTY;
		n = n->next;
	}

	l->last = n;

	return l;
}

void free_nodes(List* l)
{
	Node*	n;
	Node*	next;

	n = l->first;
	while (n != NULL) {
		next = n->next;
		free(n);
		n = next;
	}
	free(l);
}

/**
 * @brief Resets the nodes between nodes res and max counted backwards from the 
 * last node in the list.
 */
void reset_nodes(List* l, int res, int max)
{
	int	i;
	Node*	n;

	n = l->last->prev;

	for (i = 1; i < res; i++) {
		n = n->prev;
	}
	for (i = res; i <= max; i++) {
		n->c = EMPTY;
		n = n->prev;
	}
}

/**
 * @brief Inserts the char c last in the list l.
 */
void insert_char(List* l, char c)
{
	Node*	n;

	n = l->first;
	n->c = c;

	l->last->next = n;
	n->prev = l->last;
	l->last = n;

	l->first = n->next;
	l->first->prev = NULL;
	n->next = NULL;
}

/**
 * @brief Find the node distance to the first matching node, starting from the 
 * last node.
 * 
 * @return The distance to the closest match, or 0 if some nodes are still
 * empty, or the size of the list if the list is unique.
 */
int find_match(List* l, char c)
{
	int	i;
	Node*	n;

	i = 1;
	n = l->last->prev;

	while (n != NULL) {
		if (c == n->c) {
			return i;
		} else if (n->c == EMPTY) {
			return 0;
		}
		n = n->prev;
		i++;
	}

	return i;
}

void solve(char* ans)
{
	int	curr_size;
	int	length;
	int	resets;
	char	c;
	List*	l;

	l = build_nodes(MARKER_LENGTH);
	length = 0;
	curr_size = 0;
	
	while ((c = getchar()) != EOF) {
		insert_char(l, c);
		resets = find_match(l, c);
		length++;
		if (resets == 0) {
			curr_size++;
		} else if (resets != MARKER_LENGTH) {
			reset_nodes(l, resets, curr_size);
			curr_size = resets;
		} else {
			break;
		}
	}

	sprintf(ans, "%d", length);
	free_nodes(l);
}

int main(int argc, char* argv[])
{
	char		ans[100];
	struct timeval	begin, end;
	long		seconds;
	long		microseconds;
	double		elapsed_ms;

	if (argc == 0) {
		return 0;
	}

	if (argc > 1 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&begin, 0);
		solve(ans);
		gettimeofday(&end, 0);

		seconds = end.tv_sec - begin.tv_sec;
		microseconds = end.tv_usec - begin.tv_usec;
		elapsed_ms = seconds*1e3 + microseconds*1e-3;
		printf("%s execution time: %.3f (ms)\n", argv[0], elapsed_ms);
	} else {
		solve(ans);
	}

	printf("%s ans: %s\n", argv[0], ans);

	return 0;
}

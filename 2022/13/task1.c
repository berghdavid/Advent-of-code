#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct List List;
typedef struct Pair Pair;

struct List {
	int	val;	/* The val of this item or -1 for empty	*/
	List*	parent;	/* The parent list of this list		*/
	List*	first;	/* The first element in this list	*/
	List*	next;	/* The next item in the list this is in	*/
};

struct Pair {
	List*	l1;
	List*	l2;
	Pair*	next;
};

List* init_list()
{
	List*	l;
	l = malloc(sizeof(List));
	l->parent = NULL;
	l->first = NULL;
	l->next = NULL;
	l->val = -1;
	return l;
}

Pair* init_pair()
{
	Pair*	p;

	p = malloc(sizeof(Pair));
	p->next = NULL;
	p->l1 = init_list();
	p->l2 = init_list();
	return p;
}

void print_list(List* l)
{
	if (l->val == -1) {
		printf("[");
		if (l->first != NULL) {
			print_list(l->first);
		}
		printf("]");
	} else {
		printf("%d", l->val);
	}

	if (l->next != NULL) {
		printf(",");
		print_list(l->next);
	}
}

void print_pair(Pair* p)
{
	printf("\n");
	print_list(p->l1);
	printf("\n");
	print_list(p->l2);
	printf("\n");
}

int read_to_list(List*	first)
{
	int	x;
	int	is_nbr;
	char	c;
	List*	l;
	
	if ((c = getchar()) == EOF) {
		return 1;
	}

	l = first;
	l->val = -1;
	x = 0;
	is_nbr = 0;

	while (c != '\n') {
		//printf("Read %c\n", c);
		if (c == '[') {
			l->first = init_list();
			l->first->parent = l;
			l = l->first;
		} else if (c == ']') {
			if (is_nbr == 1) {
				//printf("Inserting nbr %d\n", x);
				l->val = x;
				is_nbr = 0;
				x = 0;
			}
			l = l->parent;
		} else if (c == ',') {
			if (is_nbr == 1) {
				//printf("Inserting nbr %d\n", x);
				l->val = x;
				is_nbr = 0;
				x = 0;
			}
			l->next = init_list();
			l->next->parent = l->parent;
			l = l->next;
		} else if (isdigit(c)) {
			is_nbr = 1;
			x = 10 * x + c - '0';
		}
		c = getchar();
	}

	return 0;
}

int read_to_pair(Pair* p)
{
	if (read_to_list(p->l1) == 1) {
		return 1;
	}
	if (read_to_list(p->l2) == 1) {
		return 1;
	}
	getchar();
	return 0;
}

Pair* init_pairs()
{
	Pair*	first;
	Pair*	prev;
	Pair*	p;

	first = init_pair();
	if (read_to_pair(first) != 0) {
		return first;
	}
	
	prev = first;
	while (1) {
		p = init_pair();
		prev->next = p;
		if (read_to_pair(p) == 1) {
			break;
		}
		print_pair(p);
		prev->next = p;
	}

	return first;
}

void print_all_pairs(Pair* first)
{
	Pair*	p;

	p = first;
	while (p != NULL) {
		print_pair(p);
		p = p->next;
	}
}

void free_list(List* l)
{
	if (l->first != NULL) {
		free_list(l->first);
	}

	if (l->next != NULL) {
		free_list(l->next);
	}
	free(l);
}

void free_pairs(Pair* first)
{
	Pair*	p;
	Pair*	next_p;

	p = first;
	while (p != NULL) {
		free_list(p->l1);
		free_list(p->l2);
		next_p = p->next;
		free(p);
		p = next_p;
	}
}

int get_score(Pair* first)
{
	/* TODO: Calculate score */
	return 0;
}

void solve(char* ans)
{
	Pair*	first;
	int	score;

	first = init_pairs();

	//print_all_pairs(first);

	score = get_score(first);
	free_pairs(first);

	sprintf(ans, "%d", score);
}

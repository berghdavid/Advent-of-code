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

void print_all_pairs(Pair* first)
{
	Pair*	p;

	p = first;
	while (p != NULL) {
		print_pair(p);
		p = p->next;
	}
}

int read_to_list(List*	first)
{
	int	x;
	int	is_nbr;
	int	depth;
	int	prev_c;
	char	c;
	List*	l;
	
	if ((c = getchar()) == EOF) {
		return 1;
	}

	l = first;
	l->val = -1;
	x = 0;
	is_nbr = 0;
	depth = 0;
	prev_c = '*';

	while (c != '\n') {
		//printf("Read %c\n", c);
		if (c == '[') {
			//printf("d=%d: Inserting list\n", depth);
			l->first = init_list();
			l->first->parent = l;
			depth++;
			l = l->first;
		} else if (c == ']') {
			if (is_nbr == 1) {
				//printf("d=%d: Inserting nbr %d\n", depth, x);
				l->val = x;
				is_nbr = 0;
				x = 0;
			}
			depth--;
			l = l->parent;
			if (prev_c == '[') {
				free(l->first);
				l->first = NULL;
			}
		} else if (c == ',') {
			if (is_nbr == 1) {
				//printf("d=%d: Inserting nbr %d\n", depth, x);
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
		prev_c = c;
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
		if (read_to_pair(p) == 1) {
			free_pairs(p);
			break;
		} else {
			prev->next = p;
		}
		prev = p;
	}

	return first;
}

int norm_pts(int a)
{
	if (a > 0) {
		return 1;
	} else if (a < 0) {
		return -1;
	}
	return 0;
}

int cmp_list(List* l1, List* l2)
{
	int	tmp;

	if (l1 == NULL) {
		if (l2 == NULL) {
			return 0;
		} else {
			return 1;
		}
	} else if (l2 == NULL) {
		return -1;
	}

	if (l1->val != l2->val) {
		if (l1->val != -1 && l2->val != -1) {
			tmp = norm_pts(l2->val - l1->val);
			if (tmp != 0) {
				return tmp;
			}
			return cmp_list(l1->next, l2->next);
		}

		/* Different types, make one into a list */
		if (l1->val == -1) {
			tmp = l2->val;
			l2->val = -1;
			l2->first = init_list();
			l2->first->parent = l2;
			l2->first->val = tmp;
		} else {
			tmp = l1->val;
			l1->val = -1;
			l1->first = init_list();
			l1->first->parent = l1;
			l1->first->val = tmp;
		}

		tmp = cmp_list(l1->first, l2->first);
		if (tmp != 0) {
			return tmp;
		}
	} else if (l1->val == -1 || l2->val == -1) {
		tmp = cmp_list(l1->first, l2->first);
		if (tmp != 0) {
			return tmp;
		}
	}

	return cmp_list(l1->next, l2->next);
}


int get_score(Pair* first)
{
	int	score;
	int	res;
	int	i;
	Pair*	p;

	score = 0;
	i = 1;
	p = first;
	while (p != NULL) {
		res = cmp_list(p->l1, p->l2);
		if (res == 1) {
			score += res * i;
		}
		i++;
		p = p->next;
	}

	return score;
}

void solve(char* ans)
{
	Pair*	first;
	int	score;

	first = init_pairs();

	score = get_score(first);
	free_pairs(first);

	sprintf(ans, "%d", score);
}

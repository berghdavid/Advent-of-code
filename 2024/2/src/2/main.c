#include <stdio.h>
#include <stdlib.h>
#include "../../../utils/submit.c"
#include "../../../utils/utils.c"

typedef struct Elem Elem;
typedef struct Row Row;

struct Elem {
	int	val;
	int	bad;
	Elem*	next;
	Elem*	prev;
};

struct Row {
	Elem*	first;
	Elem*	last;
};

void row_free(Row* r)
{
	Elem*	e;
	Elem*	e2;

	e = r->first;
	while (e) {
		e2 = e->next;
		free(e);
		e = e2;
	}
	free(r);
}

void row_print(Row* r)
{
	Elem*	e;

	if (!r->first) {
		printf("[ ]\n");
		return;
	}

	printf("[ %d", r->first->val);
	e = r->first->next;
	while (e) {
		printf(", %d", e->val);
		e = e->next;
	}
	printf(" ]\n");
}

Row* row_init()
{
	Row*	r;

	r = malloc(sizeof(Row));
	r->first = NULL;
	r->last = NULL;
	return r;
}

void row_append(Row* r, int val)
{
	Elem*	e;

	e = malloc(sizeof(Elem));
	e->val = val;
	e->bad = 0;
	e->next = NULL;
	e->prev = r->last;
	if (r->last) {
		r->last->next = e;
	} else {
		r->first = e;
	}
	r->last = e;
}

int valid(int dir, int prev_val, int new_val)
{
	int	min;
	int	max;
	
	if (dir == 1) {
		min = prev_val + dir;
		max = prev_val + 3 * dir;
	} else {
		max = prev_val + dir;
		min = prev_val + 3 * dir;
	}
	return (min <= new_val && new_val <= max);
}

int valid_dir_row(int dir, Row* r)
{
	Elem*	curr;
	Elem*	prev;
	int	bad;

	bad = 0;
	prev = r->first;
	curr = prev->next;
	while (curr && bad < 2) {
		if (valid(dir, prev->val, curr->val)) {
			prev = curr;
			curr = prev->next;
			continue;
		}
		bad++;

		if (!curr->next) {
			prev = curr;
		} else if (curr->next && valid(dir, prev->val, curr->next->val)) {
			prev = curr->next;
		} else if (prev->prev && valid(dir, prev->prev->val, curr->val)) {
			prev = curr;
		} else if (!prev->prev) {
			prev = curr;
		} else {
			prev = curr;
			bad++;
		}
		curr = prev->next;
	}
	return bad < 2;
}

Pack* parse_row()
{
	Pack*	curr;
	Row*	r;

	r = row_init();
	curr = NULL;
	while (1) {
		curr = next_positive_int3();
		if (curr->val > 0) {
			row_append(r, curr->val);
		}
		if (curr->end == EOF || curr->end == '\n') {
			break;
		}
		free(curr);
	}

	curr->val = 0;
	if (r->first && r->first->next) {
		curr->val = valid_dir_row(1, r) || valid_dir_row(-1, r);
	}

	row_free(r);

	return curr;
}

int main(int argc, char* argv[])
{
	char	ans[2048];
	Pack*	res;
	int	sum;

	sum = 0;
	while ((res = parse_row()) && res->end != EOF) {
		sum += res->val;
		free(res);
	}
	free(res);

	printf("Ans: %d\n", sum);
	sprintf(ans, "%d", sum);

	if (argc == 3) {
		// Post answer to AoC
		submit(ans, argv[1], argv[2]);
	}
}

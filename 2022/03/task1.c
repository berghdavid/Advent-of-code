#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "../common/utils.h"

typedef struct Letter Letter;
typedef struct Sack Sack;

struct Letter {
	char	item;
	Letter*	next;
};

struct Sack {
	Letter*	comp1;
	Letter*	comp2;
	int	size;
};

Sack* build_sack()
{
	int	size;
	char	c;
	Letter*	first;
	Letter*	mid;
	Letter*	s;
	Sack*	l;

	/* Init first element */
	c = getchar();
	if (c == EOF || c == '\n') {
		return NULL;
	}
	first = malloc(sizeof(Letter));
	first->item = c;
	first->next = NULL;
	size = 1;

	s = first;
	mid = first;
	
	while((c = getchar()) != EOF && c != '\n') {
		s->next = malloc(sizeof(Letter));
		s = s->next;
		s->item = c;
		s->next = NULL;
		if (++size % 2 == 0) {
			mid = mid->next;
		}
	}

	l = malloc(sizeof(Sack));
	l->comp1 = first;
	l->comp2 = mid;
	l->size = size;

	return l;
}

void free_sack(Sack* l)
{
	Letter*	i;
	Letter*	temp;

	i = l->comp1;

	while (i != NULL) {
		temp = i->next;
		free(i);
		i = temp;
	}

	free(l);
}

int in_comp1(char c, Sack* l)
{
	int	i;
	Letter*	s;

	i = 0;
	s = l->comp1;

	for (i = 0; i < l->size / 2; i++) {
		if (s->item == c) {
			return 1;
		}
		s = s->next;
	}

	return 0;
}

int pts(char c)
{
	int	ans;

	ans = (int) c - 96;
	if (ans <= 0) {
		ans += 58;
	}
	return ans;
}

void solve(char* ans)
{
	int	tot_pts;
	int	i;
	Letter*	s;
	Sack*	l;

	tot_pts = 0;

	while ((l = build_sack()) != NULL) {
		s = l->comp2;
		for (i = 0; i < (l->size / 2); i++) {
			if (in_comp1(s->item, l)) {
				tot_pts += pts(s->item);
				break;
			}
			s = s->next;
		}
		free_sack(l);
	}

	sprintf(ans, "%d", tot_pts);
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

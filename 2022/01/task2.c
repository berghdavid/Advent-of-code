#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "../common/utils.h"

typedef struct Node_t Node_t;

struct Node_t {
        int     val;
        Node_t* next;
};

Node_t* build_nodes(int size)
{
        int     i;
        Node_t* first;
        Node_t* n;

        first = malloc(sizeof(Node_t));
        first->val = 0;
        first->next = NULL;

        n = first;

        for (i = 0; i < size - 1; i++) {
                n->next = malloc(sizeof(Node_t));
                n = n->next;
                n->val = 0;
                n->next = NULL;
        }

        return first;
}

void free_nodes(Node_t* n)
{
        Node_t* temp;
        Node_t* next;

        temp = n;

        while (temp != NULL) {
                next = temp->next;
                free(temp);
                temp = next;
        }
}

int get_sum(Node_t* n)
{
        int     sum;
        Node_t* temp;

        sum = 0;
        temp = n;

        while (temp != NULL) {
                sum += temp->val;
                temp = temp->next;
        }

        return sum;
}

void check_max(Node_t* n, int d)
{
        Node_t* min;
        Node_t* temp;

        temp = n;
        min = n;

        while (temp != NULL) {
                if (temp->val < min->val) {
                        min = temp;
                }
                temp = temp->next;
        }
        if (d > min->val) {
                min->val = d;
        }
}

void solve(char* ans)
{
        int     max;
        int     sum;
        int     temp;
        Node_t* n;

        n = build_nodes(3);
        sum = 0;

        while (1) {
                temp = next_int();
                if (temp == 0) {
                        check_max(n, sum);
                        sum = 0;
                } else if (temp == -1) {
                        check_max(n, sum);
                        break;
                } else {
                        sum += temp;
                }
        }
        max = get_sum(n);
        free_nodes(n);

	sprintf(ans, "%d", max);
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

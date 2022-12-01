#include <ctype.h>
#include <stdio.h>
#include "utils.h"

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

int main(int argc, char *argv[])
{
        Node_t* n;
        int     max;
        int     sum;
        int     temp;

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
        printf("Task 2 ans: %d\n", max);
        free_nodes(n);

        return 0;
}

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "utils.h"

int next_int()
{
        int     x;
        int     c;

	x = 0;

        if((c = getchar()) == EOF) {
                return -1;
        }
        while (isdigit(c)) {
                x = 10 * x + c - '0';
                c = getchar();
        }

        return x;
}

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

Node_t* free_nodes(Node_t* n)
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

void print_nodes(Node_t* n)
{
        int     i;
        Node_t* temp;

        temp = n;
        i = 0;

        while (temp != NULL) {
                printf("Node %d: %d\n", i++, temp->val);
                temp = temp->next;
        }
}

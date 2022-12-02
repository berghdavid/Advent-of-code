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

Node* build_nodes(int size)
{
        int     i;
        Node* first;
        Node* n;

        first = malloc(sizeof(Node));
        first->val = 0;
        first->next = NULL;

        n = first;

        for (i = 0; i < size - 1; i++) {
                n->next = malloc(sizeof(Node));
                n = n->next;
                n->val = 0;
                n->next = NULL;
        }

        return first;
}

Node* free_nodes(Node* n)
{
        Node* temp;
        Node* next;

        temp = n;

        while (temp != NULL) {
                next = temp->next;
                free(temp);
                temp = next;
        }
}

void print_nodes(Node* n)
{
        int     i;
        Node* temp;

        temp = n;
        i = 0;

        while (temp != NULL) {
                printf("Node %d: %d\n", i++, temp->val);
                temp = temp->next;
        }
}

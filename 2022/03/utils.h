#ifndef UTILS_H_
#define UTILS_H_

typedef struct Node Node;

struct Node {
        int     val;
        Node* next;
};

int next_int();

Node* build_nodes(int size);

int get_sum(Node* n);

void print_nodes(Node* n);

Node* free_nodes(Node* n);

void check_max(Node* n, int d);

#endif

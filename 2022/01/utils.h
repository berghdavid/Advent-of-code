#ifndef UTILS_H_
#define UTILS_H_

typedef struct Node_t Node_t;

struct Node_t {
        int     val;
        Node_t* next;
};

int next_int();

Node_t* build_nodes(int size);

int get_sum(Node_t* n);

void print_nodes(Node_t* n);

Node_t* free_nodes(Node_t* n);

void check_max(Node_t* n, int d);

#endif

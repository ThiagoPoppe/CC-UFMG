#ifndef LIST_H
#define LIST_H

typedef struct node {
    int id;
    int weight;
    struct node* next;
} Node;

typedef struct list {
    Node* head;
    Node* tail;
    int size;
} List;

List* create_list();
Node* create_node(int id, int weight);

void insert_end(List* l, int id, int weight);
void remove_begin(List* l);

void print_list(List* l);

void destroy_list(List* l);

#endif
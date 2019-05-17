#ifndef LIST_H
#define LIST_H

typedef struct edge {
    int id;
    int weight;
    struct edge* next;
} Edge;

typedef struct list {
    Edge* head;
    Edge* tail;
    int size;
} List;

List* create_list();
Edge* create_edge(int id, int weight);

int in_list(List* l, int id);

void insert_end(List* l, int id, int weight);
void remove_begin(List* l);

void print_list(List* l);

void destroy_list(List* l);

#endif
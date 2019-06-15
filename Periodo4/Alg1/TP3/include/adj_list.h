#ifndef ADJ_LIST_H
#define ADJ_LIST_H

typedef struct vertex {
    int id;
    int degree;
    struct vertex* next;
} Vertex;

typedef struct adj_list {
    Vertex* head;
    Vertex* tail;
} Adj_List;

Adj_List* create_adj_list();
Vertex* create_vertex(int id, int degree);

void insert_end(Adj_List* l, int id, int degree);

void print_adj_list(Adj_List* l);
void destroy_adj_list(Adj_List* l);

#endif
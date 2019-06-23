#ifndef LIST_H
#define LIST_H

typedef struct node {
    int id;
    struct node* next;
} Node;

typedef struct list {
    Node* head;
    Node* tail;
    int size;
} List;

// Função que cria uma Lista
List* create_list();

// Função que cria um Node
Node* create_node(int id);

// Função que insere um elemento no final
void insert_end(List* l, int id);

// Função que remove um elemento dado seu id
void remove_id(List* l, int id);

// Função que imprime uma Lista
void print_list(List* l);

// Função que desaloca uma Lista
void destroy_list(List* l);

#endif
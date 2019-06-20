#ifndef ADJ_LIST_H
#define ADJ_LIST_H

// Estrutura para representar nossos vértices
typedef struct vertex {
    int id;
    struct vertex* next;
} Vertex;

// Estrutura para representar uma lista de adjacência
typedef struct adj_list {
    Vertex* head;
    Vertex* tail;
    int degree;
    int lost_edge;
} Adj_List;

// Função que cria uma lista de adjacência
Adj_List* create_adj_list();

// Função que cria um vértice
Vertex* create_vertex(int id);

// Função que insere no final da lista de adjacência
void insert_end(Adj_List* l, int id);

// Função que remove uma conexão entre dois vértices
void remove_connection(Adj_List* l, int id);

// Função que imprime uma lista de adjacência
void print_adj_list(Adj_List* l);

// Função que desaloca uma lista de adjacência
void destroy_adj_list(Adj_List* l);

#endif
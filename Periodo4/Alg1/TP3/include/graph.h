#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"

typedef struct graph {
    int num_vertices;
    int num_edges;

    List** vertices;
} Graph;

// Função que cria um grafo
Graph* create_graph(int num_vertices, int num_edges);

// Função que insere uma aresta em um grafo genérico
void insert_edge(Graph* g, int u, int v);

// Função que insere uma aresta direcionada do menor vértice para o maior em um grafo árvore
void insert_edge_tree(Graph* g, int u, int v);

// Função que remove uma aresta do grafo
<<<<<<< HEAD
void remove_edge(Graph* g, int u, int v);

// Função que remove todas as arestas de um vértice
void remove_incident_edges(Graph* g, int v);
=======
void remove_edge(Graph* g, int v, int u);

// Função que retorna o id do vértice de maior grau no grafo
int max_degree_id(Graph* g);

/*
   Função que aproxima uma instância válida mínima do vertex cover,
   imprimindo os vértices que participam dessa instância
*/
void aprox_min_vertex_cover(Graph* g);

/* 
   Função que calcula o número de vértices que participam de uma
   instância válida mínima de um vertex cover do nosso grafo
*/
int min_vertex_cover(Graph* g, Vertex* prev, Vertex* current, int isPart);
>>>>>>> c89f06c320ce897255a002e10a5af0824294261a

// Função que imprime um grafo
void print_graph(Graph* g);

// Função que desaloca um grafo
void destroy_graph(Graph* g);

#endif
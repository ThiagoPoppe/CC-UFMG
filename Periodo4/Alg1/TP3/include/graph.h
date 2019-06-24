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

// Função que remove uma aresta do grafo
void remove_edge(Graph* g, int u, int v);

// Função que remove todas as arestas de um vértice
void remove_incident_edges(Graph* g, int v);

// Função que imprime um grafo
void print_graph(Graph* g);

// Função que desaloca um grafo
void destroy_graph(Graph* g);

#endif
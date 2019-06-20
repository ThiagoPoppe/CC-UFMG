#ifndef GRAPH_H
#define GRAPH_H

#include "adj_list.h"

typedef struct graph {
    int num_vertices;
    int num_edges;

    Adj_List** vertices;
} Graph;

// Função que cria um grafo dado seu número de vértices
Graph* create_graph(int num_vertices, int num_edges);

// Função que insere uma aresta no grafo
void insert_edge(Graph* g, int v, int u);

// Função que remove uma aresta do grafo
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

// Função que imprime um grafo
void print_graph(Graph* g);

// Função que desaloca um grafo
void destroy_graph(Graph* g);

#endif
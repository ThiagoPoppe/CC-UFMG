#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"

typedef struct graph {
    int V;
    int E;

    List** adj_list;
} Graph;

Graph* create_graph(int V, int E);

void insert_edge(Graph* g, int v, int u, int weight);
void insert_edge_K(Graph* g, int v, int u, int weight);

void print_graph(Graph* g);
void destroy_graph(Graph* g);

#endif
#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"

typedef struct connectedComponents {
    int* vertices;
    int num_components;
} ConnectedComponents;

typedef struct edge {
    int v;
    int u;
    int weight;
} Edge;

typedef struct graph {
    int num_vertices;
    int num_edges;
    Edge* edges;
    List** adj_list;
} Graph;

Graph* create_graph(int V);
Graph* create_induced_graph_less(Graph* g, int pivot);

void get_edges(Graph* g, Edge* edges);

ConnectedComponents* return_connected_components(Graph* g);

int is_connected(Graph* g);

void insert_undirected_edge(Graph* g, int v, int u, int weight);

void DFS(Graph* g, int v, int* visited, int index_component);

void print_graph(Graph* g);
void destroy_graph(Graph* g);

void destroy_connected_components(ConnectedComponents* cc);

int MBST(Graph* g);

#endif
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

Graph* create_graph(int V, int E) {
    Graph* g = (Graph*) malloc(sizeof(Graph));
    if (g == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    g->V = V;
    g->E = E;
    
    g->adj_list = (List**) malloc(V * sizeof(List*));
    if (g->adj_list == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    for (int i = 0; i < V; i++)
        g->adj_list[i] = create_list();

    return g;
}

void insert_edge(Graph* g, int v, int u, int weight) {
    insert_end(g->adj_list[v], u, weight);
}

void insert_edge_K(Graph* g, int v, int u, int weight) {
    insert_edge(g, v, u, weight);
    insert_edge(g, u, v, weight);
}

void print_graph(Graph* g) {
    for (int i = 0; i < g->V; i++) {
        printf("Vertice %d: ", i+1);
        print_list(g->adj_list[i]);
    }
}

void destroy_graph(Graph* g) {
    for (int i = 0; i < g->V; i++)
        destroy_list(g->adj_list[i]);

    destroy_list(g->adj_list);
    free(g);
}
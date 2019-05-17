#include <stdio.h>
#include <stdlib.h>

#include "matrix_graph.h"

Matrix_Graph* create_matrix_graph(int V, int E) {
    Matrix_Graph* g = (Matrix_Graph*) malloc(sizeof(Matrix_Graph));
    if (g == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    g->V = V;
    g->E = E;
    g->adj_matrix = (Matrix_Vertex**) malloc(V * sizeof(Matrix_Vertex*));

    for (int i = 0; i < V; i++) {
        g->adj_matrix[i] = (Matrix_Vertex*) malloc(V * sizeof(Matrix_Vertex));
    
        for (int j = 0; j < V; j++) {
            g->adj_matrix[i][j].exist = 0;
            g->adj_matrix[i][j].weight = 0;
        }
    }

    return g;
}

void insert_edge_matrix_graph(Matrix_Graph* g, int v, int u, int weight) {
    g->adj_matrix[v][u].exist = 1;
    g->adj_matrix[v][u].weight = weight;
}

void insert_edge_matrix_graph_und(Matrix_Graph* g, int v, int u, int weight) {
    insert_edge_matrix_graph(g, v, u, weight);
    insert_edge_matrix_graph(g, u, v, weight);
}

void print_matrix_graph(Matrix_Graph* g) {
    for (int i = 0; i < g->V; i++) {
        printf("Vertice %d: ", i);
        
        for (int j = 0; j < g->V; j++) {
            if (g->adj_matrix[i][j].exist)
                printf("(id: %d, peso: %d) ", j, g->adj_matrix[i][j].weight);
        }
        printf("\n");
    }
}

void destroy_matrix_graph(Matrix_Graph* g) {
    for (int i = 0; i < g->V; i++)
        free(g->adj_matrix[i]);

    free(g->adj_matrix);
    free(g);
}
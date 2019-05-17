#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

typedef struct matrix_vertex {
    int exist;
    int weight;
} Matrix_Vertex;

typedef struct matrix_graph {
    int V;
    int E;
    Matrix_Vertex** adj_matrix;
} Matrix_Graph;

Matrix_Graph* create_matrix_graph(int V, int E);
void insert_edge_matrix_graph(Matrix_Graph* g, int v, int u, int weight);
void insert_edge_matrix_graph_und(Matrix_Graph* g, int v, int u, int weight);
void print_matrix_graph(Matrix_Graph* g);
void destroy_matrix_graph(Matrix_Graph* g);

#endif
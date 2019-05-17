#include <stdio.h>
#include <stdlib.h>

#include "list_graph.h"
#include "MoM.h"

List_Graph* create_list_graph(int V) {
    List_Graph* g = (List_Graph*) malloc(sizeof(List_Graph));
    if (g == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    g->V = V;
    g->E = 0;
    
    g->adj_list = (List**) malloc(V * sizeof(List*));
    if (g->adj_list == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    for (int i = 0; i < V; i++)
        g->adj_list[i] = create_list();

    return g;
}

Edge* get_edge(List_Graph* g, int v, int u) {
    Edge* aux = g->adj_list[v]->head;
    while (aux != NULL && aux->id != u)
        aux = aux->next;

    return aux;
}

void insert_edge_list_graph(List_Graph* g, int v, int u, int weight) {
    insert_end(g->adj_list[v], u, weight);

    if (!in_list(g->adj_list[u], v))
      g->E++;
}

void insert_edge_list_graph_und(List_Graph* g, int v, int u, int weight) {
    insert_edge_list_graph(g, v, u, weight);
    insert_edge_list_graph(g, u, v, weight);
}

void print_list_graph(List_Graph* g) {
    for (int i = 0; i < g->V; i++) {
        printf("Vertice %d: ", i);
        print_list(g->adj_list[i]);
    }
}

void destroy_list_graph(List_Graph* g) {
    for (int i = 0; i < g->V; i++)
        destroy_list(g->adj_list[i]);
    
    free(g->adj_list);
    free(g);
}

// TENTAR INSERIR APENAS UMA VEZ!
void partition_graph(List_Graph* g, List_Graph* less, List_Graph* greater, int pivot) {
    for (int i = 0; i < g->V; i++) {
        Edge* aux = g->adj_list[i]->head;
        while (aux != NULL) {
            if (aux->weight < pivot)
                insert_edge_list_graph(less, i, aux->id, aux->weight);
            else
                insert_edge_list_graph(greater, i, aux->id, aux->weight);

            aux = aux->next;
        }
    }
}

// CONTINUAR DEPOIS
int MBST(List_Graph* g) {
    int* dist = return_edges(g);
    int median = MoM_select(dist, g->E, g->E/2);

    List_Graph* A = create_list_graph(g->V);
    List_Graph* B = create_list_graph(g->V);
    partition_graph(g, A, B, median);

    printf("Grafo A:\n");
    print_list_graph(A);

    printf("Grafo B:\n");
    print_list_graph(B);

    destroy_list_graph(A);
    destroy_list_graph(B);
}

int* return_edges(List_Graph* g) {
    int* edges = (int*) malloc(g->E * sizeof(int));
    int k = 0;

    for (int i = 0; i < g->V; i++) {
        for (int j = i+1; j < g->V; j++) {
            Edge* e = get_edge(g, i, j);
            if (e != NULL)
                edges[k++] = e->weight;
        }
    }

    return edges;
}
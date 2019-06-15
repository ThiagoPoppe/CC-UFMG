#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

Graph* create_graph(int num_vertices, int num_edges) {
    // Alocando memória para um grafo e verificando se o mesmo foi devidamente alocado
    Graph* g = (Graph*) malloc(sizeof(Graph));
    if (g == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    // Inicializando os campos do grafo
    g->num_vertices = num_vertices;
    g->num_edges = num_edges;
    
    // Alocando memória para um vetor de vértices do nosso grafo
    g->vertices = (Adj_List**) malloc(sizeof(Adj_List*) * num_vertices);
    if (g->vertices == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    // Alocando uma lista de adjacência para cada vértice
    for (int i = 0; i < num_vertices; i++)
        g->vertices[i] = create_adj_list();

    // Retornando o grafo criado
    return g;
}

void insert_edge(Graph* g, int v, int u) {
    // Inserindo uma aresta não direcionada entre os vértices "v" e "u"
    insert_end(g->vertices[v], u);
    insert_end(g->vertices[u], v);
}

void remove_edge(Graph* g, int v, int u) {
    // Removendo uma aresta não direcionada entre os vértices "v" e "u"
    remove_connection(g->vertices[v], u);
    remove_connection(g->vertices[u], v);

    // Atualizando o número de arestas do grafo
    g->num_edges--;
}

int max_degree_id(Graph* g) {
    int max_id = 0;
    Adj_List* max = g->vertices[max_id];

    // Percorrendo os vértices do nosso grafo, atualizando o max e o max_id
    for (int i = 1; i < g->num_vertices; i++)
        if (g->vertices[i]->degree > max->degree) {
            max_id = i;
            max = g->vertices[i];
        }

    return max_id;
}

void aprox_min_vertex_cover(Graph* g) {
    // Iremos executar o algoritmo enquanto nosso grafo possuir arestas
    while (g->num_edges != 0) {
        int max_id = max_degree_id(g);
        Vertex* max_vertex = g->vertices[max_id]->head;

        // Removemos todas as arestas que incidem sobre o vértice de maior grau
        while (max_vertex != NULL) {
            remove_edge(g, max_id, max_vertex->id);
            max_vertex = max_vertex->next;
        }

        // Imprimimos o id do vértice de maior grau
        printf("%d ", max_id);
    }

    printf("\n");
}

// Função auxiliar que retorna o mínimo de dois valores inteiros
// int min(int a, int b) {
//     return a < b ? a : b;
// }

// int min_vertex_cover(Graph* g, Vertex* current) {
//     int size_including = 0, size_excluding = 0;
//     Vertex* aux;

//     // Caso o vértice não esteja ligado com nenhum outro, retornamos 0
//     if (g->vertices[current->id]->degree == 0 || current == NULL)
//         return 0;

//     // Caso onde o vértice atual faz parte do vertex cover
//     aux = current;
//     while(aux != NULL) {
//         if (g->vertices[aux->id]->head->id != aux->id)
//             size_including += 1 + min_vertex_cover(g, g->vertices[aux->id]->head);
//         aux = aux->next;
//     }

//     // Caso onde o vértice atual não faz parte do vertex cover
//     aux = current;
//     while (aux != NULL) {
//         size_excluding += 1 + min_vertex_cover(g, g->vertices[aux->id]->head);
//         aux = aux->next;
//     }

//     printf("%d, %d\n", size_including, size_excluding);

//     return min(size_including, size_excluding);
// }

void print_graph(Graph* g) {
    for (int i = 0; i < g->num_vertices; i++) {
        printf("Vértice %d:\n", i);
        printf("Grau: %d\n", g->vertices[i]->degree);
        printf("Conexões: ");
        print_adj_list(g->vertices[i]);
        printf("\n");
    }
}

void destroy_graph(Graph* g) {
    // Desalocando cada lista de adjacência
    for (int i = 0; i < g->num_vertices; i++)
        destroy_adj_list(g->vertices[i]);

    // Desalocando o vetor de vértices e o grafo em si
    free(g->vertices);
    free(g);
}
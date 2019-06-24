#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

// Função que cria um grafo
Graph* create_graph(int num_vertices, int num_edges) {
    // Alocando memória para um grafo
    Graph* g = (Graph*) malloc(sizeof(Graph));
    if (g == NULL) {
        printf("*** Erro de memória ao criar um grafo ***\n");
        exit(1);
    }

    // Inicializando os campos
    g->num_vertices = num_vertices;
    g->num_edges = num_edges;

    g->vertices = (List**) malloc(num_vertices * sizeof(List*));
    if (g->vertices == NULL) {
        printf("*** Erro de memória ao criar uma lista de adjacência ***\n");
        exit(1);
    }

    // Criando uma lista de adjacência para cada vértice do grafo
    for (int i = 0; i < num_vertices; i++)
        g->vertices[i] = create_list();

    // Retornando o grafo gerado
    return g;
}

// Função que insere uma aresta em um grafo genérico
void insert_edge(Graph* g, int u, int v) {
    // Inserindo uma aresta na direção de u para v
    insert_end(g->vertices[u], v);

    // Inserindo uma aresta na direção de v para u
    insert_end(g->vertices[v], u);
}

// Função que remove uma aresta do grafo
void remove_edge(Graph* g, int u, int v) {
    // Removendo a aresta de u para v
    remove_id(g->vertices[u], v);

    // Removendo a aresta de v para u
    remove_id(g->vertices[v], u);
}

// Função que remove todas as arestas de um vértice
void remove_incident_edges(Graph* g, int v) {
    // Criando Node auxiliar para percorrer a lista de adjacência do vértice
    Node* aux = g->vertices[v]->head;

    // Removendo as arestas incidentes àquele vértice
    while(aux != NULL) {
        remove_edge(g, v, aux->id);
        aux = aux->next;
    }
}

// Função que imprime um grafo
void print_graph(Graph* g) {
    // Percorrendo todos os vértices do grafo e imprimindo suas listas de adjacência
    for (int i = 0; i < g->num_vertices; i++) {
        printf("Vértice %d: ", i);
        print_list(g->vertices[i]);
    }
}

// Função que desaloca um grafo
void destroy_graph(Graph* g) {
    // Percorrendo a lista de adjacência de cada vértice e desalocando elas
    for (int i = 0; i < g->num_vertices; i++)
        destroy_list(g->vertices[i]);

    // Desalocando o vetor de listas e o grafo
    free(g->vertices);
    free(g);
}
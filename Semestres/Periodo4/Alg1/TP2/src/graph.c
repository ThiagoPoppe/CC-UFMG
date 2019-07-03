#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

// Função que cria o grafo
Graph* create_graph(int V) {
    // Alocando espaço para o grafo
    Graph* g = (Graph*) malloc(sizeof(Graph));
    if (g == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    // Alocando espaço para o vetor de arestas
    g->edges = (Edge*) malloc(sizeof(Edge));
    if (g->edges == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    g->num_vertices = V;
    g->num_edges = 0;
    
    // Alocando espaço para a lista de adjacência do nosso grafo
    g->adj_list = (List**) malloc(V * sizeof(List*));
    if (g->adj_list == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    // Iniciando cada posição dela como uma nova lista
    for (int i = 0; i < V; i++)
        g->adj_list[i] = create_list();

    return g;
}

// Função que retorna os componentes conexos do nosso grafo no formato da struct ConnectedComponents
ConnectedComponents* return_connected_components(Graph* g) {
    ConnectedComponents* cc = (ConnectedComponents*) malloc(sizeof(ConnectedComponents));
    cc->num_components = 0;

    // Alocando memória para o vetor que irá guardar os componentes conexos
    cc->vertices = (int*) malloc(g->num_vertices * sizeof(int));
    if (cc->vertices == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    // Inicializando nosso vetor de vértices
    for (int i = 0; i < g->num_vertices; i++)
        cc->vertices[i] = -1;

    // Executando a DFS até que visitemos todos os vértices do nosso grafo.
    // Caso achamos um vértice não visitado, incrementamos o número de componentes
    // conexos e executamos uma DFS a partir daquele vértice
    for (int i = 0; i < g->num_vertices; i++) {
        if (cc->vertices[i] == -1) {
            DFS(g, i, cc->vertices, cc->num_components);
            cc->num_components++;
        }
    }

    return cc;
}

// Função que retorna se um grafo é conexo ou não utilizando DFS
int is_connected(Graph* g) {
    // Criando o vetor de vértices visitados
    int visited[g->num_vertices];

    // Inicializando o vetor de vértices visitados
    for (int i = 0; i < g->num_vertices; i++)
        visited[i] = -1;

    // Rodando a DFS para o vértice 0
    DFS(g, 0, visited, 0);

    // Caso encontremos um vértice não visitado, retornamos que o grafo não é conexo
    for (int i = 1; i < g->num_vertices; i++)
        if (visited[i] == -1)
            return 0;

    // Caso contrário, retornamos que o grafo é conexo
    return 1;
}

// Função que insere uma aresta em um grafo não direcionado, salvando a mesma no vetor de Edge
void insert_undirected_edge(Graph* g, int v, int u, int weight) {
    // Inserimos a mesma aresta 2 vezes visto que o grafo é não direcionado
    insert_end(g->adj_list[v], u, weight);
    insert_end(g->adj_list[u], v, weight);

    // Copiando as informações para o vetor de arestas
    g->edges[g->num_edges].v = v;
    g->edges[g->num_edges].u = u;
    g->edges[g->num_edges].weight = weight;
    g->num_edges++;

    // Ampliando o espaço do vetor de arestas (ideia similiar ao vector de C++)
    Edge* aux = realloc(g->edges, (g->num_edges + 1) * sizeof(Edge));
    if (aux == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    g->edges = aux;
}

// Função que cria grafos induzidos A e B tal que:
// 1) As arestas de A são maiores ou iguais a mediana
// 2) As arestas de B são menores ou iguais a mediana
// 3) A quantidade de arestas do grafo original esteja bem distribuida
void create_induce_graphs(Graph* g, Graph* A, Graph* B, int pivot) {
    for (int i = 0; i < g->num_edges; i++) {
        if (g->edges[i].weight <= pivot && B->num_edges < g->num_edges / 2)
            insert_undirected_edge(B, g->edges[i].v, g->edges[i].u, g->edges[i].weight);

        else if (g->edges[i].weight >= pivot)
            insert_undirected_edge(A, g->edges[i].v, g->edges[i].u, g->edges[i].weight);
    }
}

// Função que executa uma DFS
void DFS(Graph* g, int v, int* visited, int index_component) {
    // Marcando o vértice atual com o identificador do componente conexo ao qual faz parte
    visited[v] = index_component;

    Node* aux = g->adj_list[v]->head;
    while (aux != NULL) {
        // Caso o vértice não foi visitado, exploramos ele
        if (visited[aux->id] == -1)
            DFS(g, aux->id, visited, index_component);
        
        aux = aux->next;
    }
}

// Função que imprime o grafo
void print_graph(Graph* g) {
    for (int i = 0; i < g->num_vertices; i++) {
        printf("Vertice %d: ", i);
        print_list(g->adj_list[i]);
    }
}

// Função que desaloca o grafo
void destroy_graph(Graph* g) {
    // Desalocando cada lista de adjacência
    for (int i = 0; i < g->num_vertices; i++)
        destroy_list(g->adj_list[i]);

    free(g->adj_list);
    free(g->edges);
    free(g);
}

// Função que desaloca os componentes conexos do grafo
void destroy_connected_components(ConnectedComponents* cc) {
    free(cc->vertices);
    free(cc);
}
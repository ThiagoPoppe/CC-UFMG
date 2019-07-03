// ORDENAR!! EDGE, USAR EDGE!!!!!
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "divide_and_conquer.h"
#include "sort.h"

// Função que cria o grafo
Graph* create_graph(int V) {
    Graph* g = (Graph*) malloc(sizeof(Graph));
    if (g == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    g->edges = (Edge*) malloc(sizeof(Edge));
    if (g->edges == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    g->num_vertices = V;
    g->num_edges = 0;
    
    g->adj_list = (List**) malloc(V * sizeof(List*));
    if (g->adj_list == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    for (int i = 0; i < V; i++)
        g->adj_list[i] = create_list();

    return g;
}

// Função que pega as arestas do grafo no formato da struct Edge
void get_edges(Graph* g, Edge* edges) {
    int k = 0;
    for (int i = 0; i < g->num_vertices; i++) {
        for (int j = i+1; j < g->num_vertices; j++) {
            Node* n = get_node(g->adj_list[i], j);

            if (n != NULL) {
                edges[k].v = i;
                edges[k].u = j;
                edges[k].weight = n->weight;
                k++;
            }
        }
    }
}

// Função que retorna os componentes conexos do nosso grafo no formato da struct ConnectedComponents
ConnectedComponents* return_connected_components(Graph* g) {
    ConnectedComponents* cc = (ConnectedComponents*) malloc(sizeof(ConnectedComponents));
    cc->num_components = 0;
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

// Função que retorna se um grafo é conexo ou não
int is_connected(Graph* g) {
    int visited[g->num_vertices];

    for (int i = 0; i < g->num_vertices; i++)
        visited[i] = -1;

    DFS(g, 0, visited, 0);

    // Caso encontremos um vértice não visitado, retornamos que o grafo não é conexo
    for (int i = 1; i < g->num_vertices; i++)
        if (visited[i] == -1)
            return 0;

    // Caso contrário, retornamos que o grafo é conexo
    return 1;
}

// Função que insere uma aresta em um grafo não direcionado
void insert_undirected_edge(Graph* g, int v, int u, int weight) {
    insert_end(g->adj_list[v], u, weight);
    insert_end(g->adj_list[u], v, weight);

    g->edges[g->num_edges].v = v;
    g->edges[g->num_edges].u = u;
    g->edges[g->num_edges].weight = weight;
    g->num_edges++;

    Edge* aux = realloc(g->edges, (g->num_edges + 1) * sizeof(Edge));
    if (aux == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    g->edges = aux;
}

Graph* create_induce_graphs(Graph* g, Graph* A, Graph* B, int pivot) {
    for (int i = 0; i < g->num_edges; i++) {
        if (g->edges[i].weight <= pivot && B->num_edges < g->num_edges / 2)
            insert_undirected_edge(B, g->edges[i].v, g->edges[i].u, g->edges[i].weight);
        else if (g->edges[i].weight >= pivot)
            insert_undirected_edge(A, g->edges[i].v, g->edges[i].u, g->edges[i].weight);
    }
}

// Função que cria um grafo induzido tal que suas arestas são menores que o pivot
Graph* create_induced_graph_less(Graph* g, int pivot) {
    Graph* less = create_graph(g->num_vertices);

    for (int i = 0; i < g->num_edges && less->num_edges < g->num_edges/2; i++) {
        if (g->edges[i].weight <= pivot)
            insert_undirected_edge(less, g->edges[i].v, g->edges[i].u, g->edges[i].weight);
    }

    return less;
}

// Função que executa uma DFS
void DFS(Graph* g, int v, int* visited, int index_component) {
    // Marcando o vértice atual como visitado
    visited[v] = index_component;

    Node* aux = g->adj_list[v]->head;
    while (aux != NULL) {
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
 
// Função que atualiza nossos componentes conexos
void update_connected_components(ConnectedComponents* cc, int n, int i, int new_index_component) {
    int prev_index_component = cc->vertices[i];
    
    for (int j = 0; j < n; j++)
        if (cc->vertices[j] == prev_index_component)
            cc->vertices[j] = new_index_component;
}

// Função que retorna a aresta "bottleneck" da nossa MSBT 
int MBST(Graph* g) {
    if (g->num_edges == 1)
        return g->edges[0].weight;

    // int pos_median;
    int median = MoM_select_edge(g->edges, g->num_edges, g->num_edges / 2);

    // int pesos[g->num_edges];
    // for (int i = 0; i < g->num_edges; i++)
    //     pesos[i] = g->edges[i].weight;

    // insertion_sort(pesos, g->num_edges);
    // printf("Mediana esperada: %d\n", pesos[g->num_edges/2]);
    // printf("Mediana obtida: %d\n", median);
    // printf("Numero de arestas: %d\n", g->num_edges);
    // printf("K: %d\n", g->num_edges/2);

    // for (int i = 0; i < g->num_edges; i++)
    //     printf("%d ", pesos[i]);
    // printf("\n");
    // getchar();

    Graph* A = create_graph(g->num_vertices);
    Graph* B = create_graph(g->num_vertices);

    create_induce_graphs(g, A, B, median);

    if (is_connected(B))
        return MBST(B);

    ConnectedComponents* cc = return_connected_components(B);
    Graph* C = create_graph(cc->num_components);
    
    for (int i = 0; i < A->num_edges; i++) {
        int v = A->edges[i].v;
        int u = A->edges[i].u;

        if (cc->vertices[v] != cc->vertices[u])
            insert_undirected_edge(C, cc->vertices[v], cc->vertices[u], A->edges[i].weight);
    }

    // printf("Grafo A:\n");
    // print_graph(A);
    // getchar();

    // printf("Grafo B:\n");
    // print_graph(B);
    // getchar();

    // printf("Grafo C:\n");
    // print_graph(C);
    // getchar();

    destroy_graph(B);
    destroy_connected_components(cc);

    return MBST(C);
}
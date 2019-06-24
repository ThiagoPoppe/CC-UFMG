#include <stdio.h>

#include "vertex_cover.h"

// Função que retorna o mínimo entre dois valores
int min(int a, int b) {
    return a < b ? a : b;
}

// Função auxiliar que realiza o procedimento de encontrar o vertex-cover mínimo em uma árvore
int min_vertex_cover(Graph* g, int v, int* vertex_cover) {
    // Caso o valor do vertex-cover para aquele vértice já tenha sido computado, retornamos tal valor
    if (vertex_cover[v] != -1)
        return vertex_cover[v];

    // Caso o vértice seja uma folha (lista de adjacência de tamanho 0), retornamos 0
    if (g->vertices[v]->size == 0) {
        vertex_cover[v] = 0;
        return 0;
    }

    // Removendo os vértices que possuem o mesmo id que o pai
    Node* aux = g->vertices[v]->head;
    while (aux != NULL) {
        remove_id(g->vertices[aux->id], v);
        aux = aux->next;
    }

    // Caso o vértice faça parte da solução, chamamos a função para seus filhos
    int including = 1;
    Node* son = g->vertices[v]->head;

    while (son != NULL) {
        including += min_vertex_cover(g, son->id, vertex_cover);
        son = son->next;
    }

    // Caso o vértice não faça parte, seus filhos devem fazer e chamamos a função para seus netos
    int excluding = 0;
    son = g->vertices[v]->head;

    while (son != NULL) {
        Node* grandson = g->vertices[son->id]->head;
        excluding++;

        while (grandson != NULL) {
            excluding += min_vertex_cover(g, grandson->id, vertex_cover);
            grandson = grandson->next;
        }

        son = son->next;
    }

    // Retornamos o mínimo entre o vértice fazendo parte ou não da solução
    vertex_cover[v] = min(including, excluding);
    return vertex_cover[v];
}


// Função que retorna o tamanho de uma instância mínima de um vertex-cover em uma árvore
int tree_vertex_cover(Graph* g) {
    // Criando e inicializando um vetor que armazenará valores intermediários de tamanhos de vertex-covers
    int vertex_cover[g->num_vertices];
    for (int i = 0; i < g->num_vertices; i++)
        vertex_cover[i] = -1;

    // Retornando o tamanho mínimo do vertex-cover da árvore enraizada no vértice 0
    return min_vertex_cover(g, 0, vertex_cover);
}

// Função que mostra o tamanho e vértices de uma instância aproximada (no máximo 2 vezes pior) de um vertex-cover
void approx_vertex_cover(Graph* g) {
    // Criando a lista que irá conter a solução para nosso problema
    List* vertex_cover = create_list();
    
    // Iremos percorrer todos os vértices do nosso grafo
    for (int i = 0; i < g->num_vertices; i++) {
        // Criando um Node auxiliar para pegar uma conexão do vértice atual
        Node* aux = g->vertices[i]->head;
        if (aux != NULL) {
            // Adicionando ambos vértices à nossa solução
            insert_end(vertex_cover, i);
            insert_end(vertex_cover, aux->id);

            // Removemos todas as arestas incidentes nos dois vértices
            // Temos que remover primeiro aux senão o mesmo será NULL e resultará em seg fault
            remove_incident_edges(g, aux->id);
            remove_incident_edges(g, i);
        }

        // Caso não tenhamos mais arestas no grafo, podemos parar
        if (g->num_edges == 0)
            break;
    }

    // Imprimindo o tamanho do vertex-cover
    printf("%d\n", vertex_cover->size);

    // Imprimindo os vértices que participam do vertex-cover
    Node* aux = vertex_cover->head;
    while (aux != NULL) {
        printf("%d\n", aux->id);
        aux = aux->next;
    }

    // Desalocando a lista que contém a solução
    destroy_list(vertex_cover);
}
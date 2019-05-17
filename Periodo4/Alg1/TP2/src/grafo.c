#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"

GrafoK* criaGrafoK(int n) {
    GrafoK* g = (GrafoK*) malloc(sizeof(GrafoK));
    if (g == NULL) {
        printf("*** Erro de Memoria ***");
        exit(1);
    }

    g->vertices = (Lista**) malloc(n * sizeof(Lista*));
    if (g->vertices == NULL) {
        printf("*** Erro de Memoria ***");
        exit(1);
    }

    g->num_v = n;
    g->num_e = (n * (n - 1)) / 2;

    for (int i = 0; i < g->num_v; i++)
        g->vertices[i] = criaLista();

    return g;
}

void insereAresta(GrafoK* g, int u, int v, int peso) {
    insereNode(g->vertices[u], v, peso);
    insereNode(g->vertices[v], u, peso);
}

int retornaAresta(GrafoK* g, int u, int v) {
    Node* aux = g->vertices[u]->inicio;
    while (aux->id != v)
        aux = aux->prox;

    return aux->peso;
}

void printGrafoK(GrafoK* g) {
    for (int i = 0; i < g->num_v; i++) {
        Lista* aux = g->vertices[i];
        printf("Vertice %d:\n", i+1);
        printLista(aux);
    }
}

void destroyGrafoK(GrafoK* g) {
    for (int i = 0; i < g->num_v; i++)
        destroyLista(g->vertices[i]);
    
    free(g);
}
#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

Node* criaNode(int id, int peso) {
    Node* n = (Node*) malloc(sizeof(Node));
    if (n == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    n->id = id;
    n->peso = peso;
    n->prox = NULL;
    
    return n;
}

Lista* criaLista() {
    Lista* l = (Lista*) malloc(sizeof(Lista));
    if (l == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;

    return l;
}

void insereNode(Lista* l, int id, int peso) {
    Node* novo = criaNode(id, peso);

    if (l->inicio == NULL)
        l->inicio = novo;
    else
        l->fim->prox = novo;

    l->fim = novo;
    l->tam++;
}

void printLista(Lista* l) {
    Node* aux = l->inicio;
    while (aux != NULL) {
        printf("Conectado com %d com distancia %d\n", aux->id, aux->peso);
        aux = aux->prox;
    }
}

void destroyLista(Lista* l) {
    Node* aux = l->inicio;
    Node* del = NULL;

    while (aux != NULL) {
        del = aux;
        aux = aux->prox;
        free(del);
    }

    free(l);
}
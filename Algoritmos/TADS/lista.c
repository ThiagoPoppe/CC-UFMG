#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// Função para criar uma Lista
Lista* criaLista() {
    Lista* l = (Lista*) malloc(sizeof(Lista));
    if (l == NULL) {
        printf("*** Erro durante alocação de memória ***\n");
        exit(1);
    }

    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;

    return l;
}

// Função para criar um Node
Node* criaNode(int val) {
    Node* n = (Node*) malloc(sizeof(Node));
    if (n == NULL) {
        printf("*** Erro durante alocação de memória ***\n");
        exit(1);
    }

    n->val = val;
    n->prox = NULL;

    return n;
}

// Função que insere um elemento no fim da Lista
void insereFim(Lista* l, int val) {
    Node *novo = criaNode(val);

    if (l->inicio == NULL)
        l->inicio = novo;
    else
        l->fim->prox = novo;

    l->fim = novo;
    l->tam++;
}

// Função que remove um elemento do início da Lista
void removeInicio(Lista* l) {
    if (estaVazia(l))
        return;

    Node* del = l->inicio;
    
    l->inicio = l->inicio->prox;
    l->tam--;

    free(del);
}

// Função para imprimir uma Lista
void printLista(Lista* l) {
    Node* atual = l->inicio;
    while (atual != NULL) {
        printf("%d ", atual->val);
        atual = atual->prox;
    }
    printf("\n");
}

// Função que retorna se a lista está vazia
int estaVazia(Lista* l) {
    return l->inicio == NULL;
}

// Função que destrói uma Lista
void destroyLista(Lista* l) {
    Node* atual = l->inicio;
    Node* del = NULL;

    while (atual != NULL) {
        del = atual;
        atual = atual->prox;
        free(del);
    }
    
    l->tam = 0;
    free(l);
}
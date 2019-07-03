#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

// Função que cria nossa Pilha
Pilha* criaPilha() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("*** Erro de memoria ***\n");
        exit(1);
    }

    p->inicio = NULL;
    p->tam = 0;

    return p;
}

// Função que cria nosso Node
Node* criaNode(int val) {
    Node* n = (Node*) malloc(sizeof(Node));
    if(n == NULL) {
        printf("*** Erro de memoria ***\n");
        exit(1);
    }

    n->prox = NULL;
    n->val = val;

    return n;
}

// Função que insere no início da Pilha
void push(Pilha* p, int val) {
    Node* novo = criaNode(val);
    
    novo->prox = p->inicio;
    p->inicio = novo;
    p->tam++;
}

// Função que remove do início da Pilha
int pop(Pilha* p) {
    Node* del = p->inicio;
    int val = del->val;

    p->inicio = p->inicio->prox;
    p->tam--;

    free(del);
    return val;
}

// Função que verifica se um elemento está na Pilha
int busca(Pilha* p, int val) {
    Node* atual = p->inicio;

    while (atual != NULL) {
        if (val == atual->val)
            return 1;
        else
            atual = atual->prox;
    }
    return 0;
}

// Função que retorna se a Pilha está vazia
int estaVazia(Pilha* p) {
    return p->inicio == NULL;
}

// Função que imprime nossa Pilha
void printPilha(Pilha* p) {
    Node* atual = p->inicio;
    while (atual != NULL) {
        printf("%d ", atual->val);
        atual = atual->prox;
    }
    printf("\n");
}

// Função que desaloca nossa Pilha
void destroyPilha(Pilha* p) {
    while (p->inicio != NULL)
        pop(p);
    free(p);
}
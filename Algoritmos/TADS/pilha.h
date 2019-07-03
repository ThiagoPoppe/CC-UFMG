#ifndef PILHA_H
#define PILHA_H

typedef struct node {
    int val;
    struct node* prox;
} Node;

typedef struct pilha {
    Node* inicio;
    int tam;
} Pilha;

Pilha* criaPilha();
Node* criaNode(int val);

void push(Pilha* p, int val);
int pop(Pilha* p);

int busca(Pilha* p, int val);

int estaVazia(Pilha* p);

void printPilha(Pilha* p);
void destroyPilha(Pilha* p);

#endif
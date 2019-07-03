#ifndef LISTA_H
#define LISTA_H

typedef struct node {
    int val;
    struct node* prox;
} Node;

typedef struct lista {
    Node* inicio;
    Node* fim;
    int tam;
} Lista;

Lista* criaLista();
Node* criaNode(int val);

void insereFim(Lista* l, int val);
void removeInicio(Lista* l);
int estaVazia(Lista* l);

void printLista(Lista* l);
void destroyLista(Lista* l);

#endif
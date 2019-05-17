#ifndef LISTA_H
#define LISTA_H

typedef struct node {
    int peso;
    int id;
    struct node* prox;
} Node;

typedef struct lista {
    Node* inicio;
    Node* fim;
    int tam;
} Lista;

Node* criaNode(int id, int peso);
Lista* criaLista();

void insereNode(Lista* l, int id, int peso);
void printLista(Lista* l);
void destroyLista(Lista* l);

#endif
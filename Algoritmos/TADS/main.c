#include <stdio.h>
#include "lista.h"

#define N 3

int main() {
    Lista *lista_adj[N];
    for (int i = 0; i < N; i++)
        lista_adj[i] = criaLista();

    insereFim(lista_adj[0], 1);
    insereFim(lista_adj[0], 2);

    insereFim(lista_adj[1], 0);
    insereFim(lista_adj[1], 2);

    insereFim(lista_adj[2], 0);
    insereFim(lista_adj[2], 1);
    insereFim(lista_adj[2], 2);

    for (int i = 0; i < N; i++) {
        printf("Node %d: ", i);
        printLista(lista_adj[i]);
    }

    for (int i = 0; i < N; i++) {
        destroyLista(lista_adj[i]);
    }

    return 0;
}
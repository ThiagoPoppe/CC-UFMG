#include <stdio.h>
#include <stdlib.h>

#include "adj_list.h"

Adj_List* create_adj_list() {
    Adj_List* l = (Adj_List*) malloc(sizeof(Adj_List));
    if (l == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    l->head = NULL;
    l->tail = NULL;

    return l;
}

Vertex* create_vertex(int id, int degree) {
    Vertex* v = (Vertex*) malloc(sizeof(Vertex));
    if (v == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    v->next = NULL;
    v->degree = 0;

    return v;
}

void insert_end(Adj_List* l, int id, int degree) {
    Vertex* v = create_vertex(id, degree);

    if (l->head == NULL)
        l->head = v;
    else
        l->tail->next = v;

    l->tail = v;
}

void print_adj_list(Adj_List* l) {
    Vertex* aux = l->head;
    
    while (aux != NULL) {
        printf("%d ", aux->id);
        aux = aux->next;
    }

    printf("\n");
}

void destroy_adj_list(Adj_List* l) {
    Vertex* aux = l->head;
    Vertex* toFree = NULL;

    while (aux != NULL) {
        toFree = aux;
        aux = aux->next;
        free(toFree);
    }

    free(l);
}
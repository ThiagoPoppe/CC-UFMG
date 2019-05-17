#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// Função para criar uma Lista
List* create_list() {
    List* l = (List*) malloc(sizeof(List));
    if (l == NULL) {
        printf("*** Erro durante alocação de memória ***\n");
        exit(1);
    }

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;

    return l;
}

// Função para criar um Edge
Edge* create_edge(int id, int weight) {
    Edge* n = (Edge*) malloc(sizeof(Edge));
    if (n == NULL) {
        printf("*** Erro durante alocação de memória ***\n");
        exit(1);
    }

    n->id = id;
    n->weight = weight;
    n->next = NULL;

    return n;
}

// Função que verifica se temos o id na Lista
int in_list(List* l, int id) {
    Edge* aux = l->head;
    while (aux != NULL) {
        if (aux->id == id)
            return 1;
        aux = aux->next;
    }

    return 0;
}

// Função que insere um elemento no fim da Lista
void insert_end(List* l, int id, int weight) {
    Edge *n = create_edge(id, weight);

    if (l->head == NULL) {
        l->head = n;
    } else {
        l->tail->next = n;
    }

    l->tail = n;
    l->size++;
}

// Função que remove um elemento do início da Lista
void remove_begin(List* l) {
    if (l->head == NULL)
        return;

    Edge* del = l->head;
    
    l->head = l->head->next;
    l->size--;

    free(del);
}

// Função para imprimir uma Lista
void print_list(List* l) {
    Edge* current = l->head;
    
    while (current != NULL) {
        printf("(id: %d, peso: %d), ", current->id, current->weight);
        current = current->next;
    }
    printf("\n");
}

// Função que destrói uma Lista
void destroy_list(List* l) {
    Edge* current = l->head;
    Edge* del = NULL;

    while (current != NULL) {
        del = current;
        current = current->next;
        free(del);
    }
    
    l->size = 0;
    free(l);
}
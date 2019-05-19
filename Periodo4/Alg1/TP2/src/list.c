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

// Função para criar um Node
Node* create_node(int id, int weight) {
    Node* n = (Node*) malloc(sizeof(Node));
    if (n == NULL) {
        printf("*** Erro durante alocação de memória ***\n");
        exit(1);
    }

    n->id = id;
    n->weight = weight;
    n->next = NULL;

    return n;
}

// Função que retorna um nó
Node* get_node(List* l, int id) {
    Node* aux = l->head;
    while (aux != NULL && aux->id != id)
        aux = aux->next;

    return aux;
}

// Função que verifica se um elemento está na lista
int in_list(List* l, int id) {
    Node* aux = l->head;

    while (aux != NULL) {
        if (aux->id == id)
            return 1;
        aux = aux->next;
    }

    return 0;
}

// Função que insere um elemento no fim da Lista
void insert_end(List* l, int id, int weight) {
    Node *n = create_node(id, weight);

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

    Node* del = l->head;
    
    l->head = l->head->next;
    l->size--;

    free(del);
}

// Função para imprimir uma Lista
void print_list(List* l) {
    Node* current = l->head;
    
    while (current != NULL) {
        printf("(id: %d, weight: %d) ", current->id, current->weight);
        current = current->next;
    }
    printf("\n");
}

// Função que destrói uma Lista
void destroy_list(List* l) {
    Node* current = l->head;
    Node* del = NULL;

    while (current != NULL) {
        del = current;
        current = current->next;
        free(del);
    }
    
    l->size = 0;
    free(l);
}
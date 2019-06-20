#include <stdio.h>
#include <stdlib.h>

#include "adj_list.h"

Adj_List* create_adj_list() {
    // Alocando espaço para uma lista de adjacência e verificando se o mesmo foi devidamente alocado
    Adj_List* l = (Adj_List*) malloc(sizeof(Adj_List));
    if (l == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    // Inicializando os campos da lista de adjacência
    l->head = NULL;
    l->tail = NULL;
    l->lost_edge = 0;
    l->degree = 0;

    // Retornando a lista de adjacência
    return l;
}

Vertex* create_vertex(int id) {
    // Alocando espaço para um vértice e verificando se o mesmo foi devidamente alocado
    Vertex* v = (Vertex*) malloc(sizeof(Vertex));
    if (v == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    // Inicializando os campos do vértice
    v->id = id;
    v->next = NULL;

    // Retornando o vértice
    return v;
}

void insert_end(Adj_List* l, int id) {
    // Criando um novo vértice
    Vertex* v = create_vertex(id);

    // Inserindo o novo vértice na lista de adjacência
    if (l->head == NULL)
        l->head = v;
    else
        l->tail->next = v;

    l->tail = v;
    l->degree++;
}

void remove_connection(Adj_List* l, int id) {
    // Verificamos se o índice é válido
    if (id < 0) {
        printf("*** Erro ao remover uma conexão ***\n");
        exit(1);
    }

    // Criamos vértices auxiliares
    Vertex* prev = NULL;
    Vertex* aux = l->head;

    // Percorremos até o vértice desejado
    while(aux != NULL && aux->id != id) {
        prev = aux;
        aux = aux->next;
    }

    // Caso aux seja nulo, significa que não encontramos o vértice desejado
    if (aux == NULL) {
        printf("*** Este vértice não existe na lista de adjacência ***\n");
        return;
    }

    // Caso prev seja nulo, iremos remover o primeiro vértice da nossa lista de adjacência
    if (prev == NULL)
        l->head = aux->next;

    // Caso o próximo vértice do aux seja nulom iremos remover o último vértice da nossa lista de adjacência
    else if (aux->next == NULL) {
        prev->next = NULL;
        l->tail = prev;
    }

    // Caso contrário, estaremos removendo um vértice do "meio" da nossa lista de adjacência
    else
        prev->next = aux->next;

    // Desalocamos o vértice aux, e decrementamos o grau da nossa lista de adjacência
    free(aux);
    l->lost_edge = 1;
    l->degree--;
}

void print_adj_list(Adj_List* l) {
    Vertex* aux = l->head;
    
    // Percorrendo a lista de adjacência e imprimindo o "id" do vértice
    while (aux != NULL) {
        printf("%d ", aux->id);
        aux = aux->next;
    }

    printf("\n");
}

void destroy_adj_list(Adj_List* l) {
    Vertex* aux = l->head;
    Vertex* toFree = NULL;

    // Desalocando cada vértice da lista de adjacência
    while (aux != NULL) {
        toFree = aux;
        aux = aux->next;
        free(toFree);
    }

    // Desalocando a lista de adjacência em si
    free(l);
}
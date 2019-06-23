#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// Função que cria uma Lista
List* create_list() {
    // Alocando memória para uma lista
    List* l = (List*) malloc(sizeof(List));
    if (l == NULL) {
        printf("*** Erro de memória ao criar uma lista ***\n");
        exit(1);
    }

    // Inicializando seus campos
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;

    // Retornando a lista
    return l;
}

// Função que cria um Node
Node* create_node(int id) {
    // Alocando memória para um Node
    Node* n = (Node*) malloc(sizeof(Node));
    if (n == NULL) {
        printf("*** Erro de memória ao criar um Node ***\n");
        exit(1);
    }

    // Inicializando seus campos
    n->id = id;
    n->next = NULL;

    // Retornando o Node criado
    return n;
}

// Função que insere um elemento no final
void insert_end(List* l, int id) {
    // Criando um Node
    Node* n = create_node(id);

    // Se a lista estiver vazia, inserimos no início. Caso contrário, inserimos no fim
    if (l->head == NULL)
        l->head = n;
    else
        l->tail->next = n;

    // Atualizando o ponteiro para o último Node
    l->tail = n;

    // Atualizando o tamanho da lista
    l->size++;
}

// Função que remove um elemento dado seu id
void remove_id(List* l, int id) {
    // Verificando se o id é válido
    if (id < 0) {
        printf("*** Não existe elemento com id < 0 na lista ***\n");
        exit(1);
    }

    // Criando Nodes auxiliares
    Node* prev = NULL;
    Node* current = l->head;

    // Caminhando pela lista até encontrarmos o valor
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    // Caso não encontremos, imprimimos uma mensagem de erro
    if (current == NULL) {
        printf("*** Não existe elemento com id = %d na lista ***\n", id);
        exit(1);
    }

    // Verificando os casos possíveis: início da lista, fim ou meio
    if (current == l->head) {
        l->head = current->next;
    }
    else if (current == l->tail) {
        l->tail = prev;
        prev->next = NULL;
    }
    else {
        prev->next = current->next;
    }

    // Desalocando memória para o Node atual
    free(current);

    // Atualizando o tamanho da lista
    l->size--;
}

// Função que imprime uma Lista
void print_list(List* l) {
    // Criando Node auxiliar
    Node* aux = l->head;

    // Percorrendo toda lista e imprimindo o id dos Nodes
    while (aux != NULL) {
        printf("%d ", aux->id);
        aux = aux->next;
    }

    printf("\n");
}

// Função que desaloca uma Lista
void destroy_list(List* l) {
    // Criando Nodes auxiliares
    Node* toFree = NULL;
    Node* current = l->head;

    // Percorrendo toda a lista desalocando os Nodes
    while (current != NULL) {
        toFree = current;
        current = current->next;
        
        free(toFree);
    }

    // Desalocando a lista
    free(l);
}
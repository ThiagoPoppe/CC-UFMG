#include <stdio.h>
#include <stdlib.h>

#include "vetor.h"

Vetor* criaVetor(int n) {
    Vetor* v = (Vetor*) malloc(sizeof(Vetor));
    if (v == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    v->array = (int*) malloc(n * sizeof(int));
    if (v->array == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    v->tam = n;
    return v;
}

Vetor* slice(Vetor* v, int ini, int fim) {
    fim = fim > v->tam ? v->tam : fim;

    Vetor* subVetor = criaVetor(fim-ini);
    int k = 0;

    for (int i = ini; i < fim; i++)
        subVetor->array[k++] = v->array[i];

    return subVetor;
}

int achaIndice(Vetor* v, int val) {
    int indice = 0;
    while(v->array[indice] != val)
        indice++;
    
    if (indice >= v->tam)
        return -1;
    else
        return indice;
}

int partition(Vetor* v, int ini, int fim, int pivot) {
    // Acha o índice do pivot e coloca ele no final para realizarmos o partition
    int pos = achaIndice(v, pivot);
    swap(v, pos, fim-1);

    int i = 0;
    int j = fim - 2;
    while (i <= j) {
        if(v->array[i] > pivot) {
            swap(v, i, j);
            j--;
        }
        else
            i++;
    }

    swap(v, i, fim-1);
    return i;
}

int MoM(Vetor* v, int k) {
    // Computando o tamanho de subvetores de tamanho 5 ou menor
    int n = v->tam % 5 == 0 ? v->tam/5 : v->tam/5 + 1;

    // Alocando espaço para os subvetores
    Vetor** subV5 = (Vetor**) malloc(n * sizeof(Vetor*));
    if (subV5 == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    // Partindo nosso vetor em subvetores
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (j+5 < v->tam)
            subV5[i] = slice(v, j, j+5);
        else
            subV5[i] = slice(v, j, v->tam);
        
        j += 5;
    }

    // Ordenando os subvetores e computando a mediana deles
    Vetor* medianas = criaVetor(n);
    for (int i = 0; i < n; i++) {
        insertionSort(subV5[i]);
        medianas->array[i] = subV5[i]->array[subV5[i]->tam/2];
    }

    // Computando o pivot para realizar a partição
    int pivot;
    if (medianas->tam <= 5) {
        insertionSort(medianas);
        pivot = medianas->array[medianas->tam/2];
    }
    else
        pivot = MoM(medianas, medianas->tam/2);

    // Realizando a partição e obtendo os vetores da esquerda e direita
    int pos = partition(v, 0, v->tam, pivot);
    Vetor* esq = slice(v, 0, pos);
    Vetor* dir = slice(v, pos+1, v->tam);

    // Chamando recursivamente a função para achar a mediana
    if (k < esq->tam)
        pivot = MoM(esq, k);
    else if(k > esq->tam)
        pivot = MoM(dir, k-esq->tam-1);

    // Desalocando memória
    destroyVetor(medianas);
    destroyVetor(esq);
    destroyVetor(dir);
    for (int i = 0; i < n; i++)
        destroyVetor(subV5[i]);
    free(subV5);

    return pivot;
}

void swap(Vetor* v, int i, int j) {
    int aux = v->array[i];
    v->array[i] = v->array[j];
    v->array[j] = aux;
}

void insertionSort(Vetor* v) {
    for (int i = 0; i < v->tam; i++)
        for (int j = i; j > 0; j--)
            if (v->array[j] < v->array[j-1])
                swap(v, j, j-1);
}

void printVetor(Vetor* v) {
    for(int i = 0; i < v->tam; i++)
        printf("%d ", v->array[i]);
    printf("\n");
}

void destroyVetor(Vetor* v) {
    free(v->array);
    free(v);
}
#ifndef VETOR_H
#define VETOR_H

// Estrutura Vetor
typedef struct vetor {
    int* array;
    int tam;
} Vetor;

// Função que cria um Vetor
Vetor* criaVetor(int n);

// Função que retorna um subvetor dado um início e fim
Vetor* slice(Vetor* v, int ini, int fim);

// Função que acha o índice de um valor no vetor
int achaIndice(Vetor* v, int val);

// Função que realiza o processo de partition em um Vetor
int partition(Vetor* v, int ini, int fim, int pivot);

// Função que computa a mediana de um Vetor
int MoM(Vetor* v, int k);

// Função que troca dois elementos de um Vetor
void swap(Vetor* v, int i, int j);

// Função que ordena um Vetor usando Insertion Sort
void insertionSort(Vetor* v);

// Função que imprime um Vetor
void printVetor(Vetor* v);

// Função que desaloca um Vetor
void destroyVetor(Vetor* v);

#endif
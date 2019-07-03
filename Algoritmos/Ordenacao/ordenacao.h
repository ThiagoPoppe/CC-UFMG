#ifndef ORDENACAO_H
#define ORDENACAO_H

/* Troca dois valores do vetor */
void swap(int *v, int i, int j);

/* Realiza o merge de 2 vetores */
int *merge(int *v1, int *v2, int n, int m);

/* Ordena o vetor através do método Mergesort recursivamente
   passando um intervalo de início e fim */
int *mergesort(int *v, int ini, int end);

/* Imprime o vetor */
void printVetor(int *v, int n);

#endif
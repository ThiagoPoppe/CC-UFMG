#include <stdio.h>
#include <stdlib.h>
#include "ordenacao.h"

void swap(int *v, int i, int j) {
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

int *merge(int *v1, int *v2, int n, int m) {
    int i = 0, j = 0, k = 0;
    int *result = (int *) malloc(sizeof(int) * (n + m));

    while (i < n && j < m) {
        if (v1[i] < v2[j])
            result[k++] = v1[i++];
        else
            result[k++] = v2[j++];
    }

    while (i < n)
        result[k++] = v1[i++];

    while (j < m)
        result[k++] = v2[j++];

    return result;
}

void printVetor(int *v, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}
#include <stdio.h>
#include <stdlib.h>

#include "dinamic_programming.h"

int max(int a, int b) {
    return a > b ? a : b;
}

int* max_sum(int* a, int n) {
    int M[n];
    int start = 0;
    int end = n - 1;
    int ms = a[0];

    M[0] = a[0];
    for (int i = 1; i < n; i++) {
        M[i] = max(M[i-1] + a[i], a[i]);

        if (M[i] == a[i])
            start = i;
        else if (M[i] > ms) {
            ms = M[i];
            end = i;
        }
    }

    int len = end - start + 1;
    int* result = (int*) malloc((len + 1) * sizeof(int));
    if (result == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    result[0] = len;
    int k = 1;
    for (int i = start; i <= end; i++)
        result[k++] = a[i];

    return result;
}
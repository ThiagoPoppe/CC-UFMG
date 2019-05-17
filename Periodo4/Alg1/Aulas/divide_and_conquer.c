#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "divide_and_conquer.h"
#include "sort.h"

int* merge(int* a, int* b, int n, int m) {
    int* result = (int*) malloc((n + m) * sizeof(int));
    if (result == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
        if(a[i] < b[j])
            result[k++] = a[i++];
        else
            result[k++] = b[j++];
    }

    while (i < n)
        result[k++] = a[i++];

    while (j < m)
        result[k++] = b[j++];

    return result;
}

int* merge_and_count(int* a, int* b, int n, int m) {
    int* result = (int*) malloc((n+m+1) * sizeof(int));
    if (result == NULL) {
        printf("*** Erro de Memoria ***\n");
        exit(1);
    }

    int i = 0, j = 0, k = 1;
    while (i < n && j < m) {
        if(a[i] > b[j]) {
            result[k++] = b[j++];
            result[0] += n - i;
        }
        else
            result[k++] = a[i++];
    }

    while (i < n)
        result[k++] = a[i++];

    while (j < m)
        result[k++] = b[j++];

    return result;
}

int partition(int* a, int start, int end, int pivot) {
    swap(a, pivot, end - 1);
    int i = start;
    int j = end - 2;
    while (i <= j) {
        if (a[i] > a[end - 1]) {
            swap(a, i, j);
            j--;
        }
        else
            i++;
    }

    swap(a, i, end - 1);
    return i;
}

int partition_3way(int* a, int start, int end, int* lt, int* gt, int pivot) {
    swap(a, start, pivot);
    int i = start + 1;
    *lt = start;
    *gt = end - 1;

    while (i <= *gt) {
        if (a[i] < a[*lt]) {
            swap(a, i, *lt);
            (*lt)++;
            i++;
        }
        else if (a[i] > a[*lt]) {
            swap(a, i, *gt);
            (*gt)--;
        }
        else
            i++;
    }

    return *lt;
}

void randomized_quicksort(int* a, int start, int end) {
    if (end - start <= 1)
        return;

    srand(time(NULL));
    int p = start + rand() % (end - start);
    int less, greater;
    partition_3way(a, start, end, &less, &greater, p);

    randomized_quicksort(a, start, less);
    randomized_quicksort(a, greater + 1, end);
}

int quick_select(int* a, int start, int end, int k) {
    srand(time(NULL));
    int less, greater;

    int pivot = start + rand() % (end - start);
    pivot = partition_3way(a, start, end, &less, &greater, pivot);

    int len_L = less - start;
    int len_M = greater - less + 1;
    // int len_R = end - (greater + 1);

    if (k < len_L)
        return quick_select(a, start, less, k);
    else if (k > len_L)
        return quick_select(a, greater + 1, end, k - len_L - len_M);
    else
        return a[pivot];
}

int MoM_select(int* a, int size, int k) {    
    int n = size < 5 ? 1 : size / 5;
    int m = size < 5 ? size : 5;
    
    int subV[n][m];
    int mom[n];

    // Divindo o vetor em vetores de 5 elementos, ordenando e pegando a mediana deles
    for (int i = 0; i < n; i++) {
        int j = 0;
        for (int l = 5*i; l < (5*i) + 5 && j < m; l++)
            subV[i][j++] = a[l];

        insertion_sort(subV[i], m);
        mom[i] = subV[i][m/2];
    }

    // Escolhendo nosso pivot para realizar o partition
    int pivot;
    if (n <= 5) {
        insertion_sort(mom, n);
        pivot = mom[n/2];
    }
    else
        pivot = MoM_select(mom, n, n/2);

    // Pegando a posição do pivot no vetor original
    for (int i = 0; i < size; i++) {
        if (a[i] == pivot) {
            pivot = i;
            break;
        }
    }

    // Particionando o vetor
    int lt_pos, gt_pos;
    pivot = partition_3way(a, 0, size, &lt_pos, &gt_pos, pivot);

    // Computando o tamanho do vetor da esquerda e verificando os casos
    int len_L = lt_pos;
    int len_M = gt_pos - lt_pos + 1;
    int len_R = size - (len_L + len_M);

    if (k < len_L) {
        int left[len_L];
        for (int i = 0; i < len_L; i++)
            left[i] = a[i];

        return MoM_select(left, len_L, k);
    }
    else if (k > len_L) {
        int right[len_R];
        int j = 0;
        for (int i = len_L + len_M; i < size; i++)
            right[j++] = a[i];
        
        return MoM_select(right, len_R, k - len_L - len_M);
    }   
    else
        return a[pivot];
}
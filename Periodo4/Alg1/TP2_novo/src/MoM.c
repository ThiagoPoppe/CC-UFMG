#include "MoM.h"

void swap(int* a, int i, int j) {
    int aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}

void insertion_sort(int* a, int n) {
    for (int i = 0; i < n; i++)
        for (int j = i; j > 0; j--)
            if (a[j] < a[j-1])
                swap(a, j, j-1);
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
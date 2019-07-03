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

int partition_edges(Edge* edges, int start, int end, int pivot) {
    swap_edges(edges, pivot, end - 1);
    int i = start;
    int j = end - 2;
    while (i <= j) {
        if (edges[i].weight > edges[end - 1].weight) {
            swap_edges(edges, i, j);
            j--;
        }
        else
            i++;
    }

    swap_edges(edges, i, end - 1);
    return i;
}

void partition_3way(int* a, int start, int end, int* lt, int* gt, int pos_pivot) {
    int pivot = a[pos_pivot];
    int i = start + 1;

    *lt = start;
    *gt = end - 1;

    swap(a, start, pos_pivot);

    while (i <= *gt) {
        if (a[i] < pivot) {
            swap(a, i, *lt);
            (*lt)++;
            i++;
        }
        else if (a[i] > pivot) {
            swap(a, i, *gt);
            (*gt)--;
        }
        else
            i++;
    }
}

int median_of_medians(int* a, int n) {
    if (n <= 5) {
        insertion_sort(a, n);
        return a[n/2];
    }

    int group_size = n / 5;
    int aux[5];
    int medians[group_size];

    for (int i = 0; i < group_size; i++) {
        for (int j = 0; j < 5; j++)
            aux[j] = a[5*i + j];

        insertion_sort(aux, 5);
        medians[i] = aux[5/2];
    }

    return median_of_medians(medians, group_size);
}

int MoM_select(int* a, int n, int k) {
    int pivot = median_of_medians(a, n);

    int pos_pivot = -1;
    for (int i = 0; i < n; i++)
        if (a[i] == pivot) {
            pos_pivot = i;
            break;
        }


    int lt, gt;
    partition_3way(a, 0, n, &lt, &gt, pos_pivot);

    int left[lt];
    for (int i = 0; i < lt; i++)
        left[i] = a[i];
    
    int right[n - gt];
    int i = 0;
    for (int j = gt + 1; j < n; j++)
        right[i++] = a[j];

    if (k < lt)
        return MoM_select(left, lt, k);
    else if (k > gt)
        return MoM_select(right, n - (gt + 1), k - gt - 1);
    else
        return pivot;
}

// REFAZER DEPOIS
// void randomized_quicksort(int* a, int start, int end) {
//     if (end - start <= 1)
//         return;

//     srand(time(NULL));
//     int p = start + rand() % (end - start);
//     int less, greater;
//     partition_3way(a, start, end, &less, &greater, p);

//     randomized_quicksort(a, start, less);
//     randomized_quicksort(a, greater + 1, end);
// }

// REFAZER DEPOIS
// int quick_select(int* a, int start, int end, int k) {
//     srand(time(NULL));
//     int less, greater;

//     int pivot = start + rand() % (end - start);
//     partition_3way(a, start, end, &less, &greater, pivot);

//     int len_L = less - start;
//     int len_M = greater - less + 1;
//     // int len_R = end - (greater + 1);

//     if (k < len_L)
//         return quick_select(a, start, less, k);
//     else if (k > len_L)
//         return quick_select(a, greater + 1, end, k - len_L - len_M);
//     else
//         return a[pivot];
// }

void partition_3way_edge(Edge* edges, int start, int end, int* lt, int* gt, int pos_pivot) {
    int pivot = edges[pos_pivot].weight;
    int i = start + 1;

    *lt = start;
    *gt = end - 1;

    swap_edges(edges, start, pos_pivot);

    while (i <= *gt) {
        if (edges[i].weight < pivot) {
            swap_edges(edges, i, *lt);
            (*lt)++;
            i++;
        }
        else if (edges[i].weight > pivot) {
            swap_edges(edges, i, *gt);
            (*gt)--;
        }
        else
            i++;
    }
}

Edge median_of_medians_edge(Edge* edges, int n) {
    if (n <= 5) {
        insertion_sort_edges(edges, n);
        return edges[n/2];
    }

    int group_size = n / 5;
    Edge aux[5];
    Edge medians[group_size];

    for (int i = 0; i < group_size; i++) {
        for (int j = 0; j < 5; j++)
            aux[j] = edges[5*i + j];

        insertion_sort_edges(aux, 5);
        medians[i] = aux[5/2];
    }

    return median_of_medians_edge(medians, group_size);
}

int MoM_select_edge(Edge* edges, int n, int k) {
    Edge pivot = median_of_medians_edge(edges, n);

    int pos_pivot = -1;
    for (int i = 0; i < n; i++)
        if (edges[i].v == pivot.v && edges[i].u == pivot.u && edges[i].weight == pivot.weight) {
            pos_pivot = i;
            break;
        }


    int lt, gt;
    partition_3way_edge(edges, 0, n, &lt, &gt, pos_pivot);

    Edge left[lt];
    for (int i = 0; i < lt; i++)
        left[i] = edges[i];
    
    Edge right[n - gt];
    int i = 0;
    for (int j = gt + 1; j < n; j++)
        right[i++] = edges[j];

    if (k < lt)
        return MoM_select_edge(left, lt, k);
    else if (k > gt)
        return MoM_select_edge(right, n - (gt + 1), k - gt - 1);
    else
        return pivot.weight;
}

void print_array(Edge* a, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i].weight);
    printf("\n");
}

void print_edges(Edge* edges, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", edges[i].weight);
    printf("\n");
}
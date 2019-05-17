#include <stdlib.h>

#include "divide_and_conquer.h"
#include "sort.h"

void swap(int* a, int i, int j) {
    int aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}

void bubble_sort(int* a, int n) {
    for (int i = 0; i < n; i++)
        for(int j = 0; j < n-i-1; j++)
            if (a[j] > a[j+1])
                swap(a, j, j+1);
}

void selection_sort(int* a, int n) {
    for(int i = 0; i < n; i++) {
        int min_pos = select_min_pos(a, i, n);
        swap(a, i, min_pos);
    }
}

void insertion_sort(int* a, int n) {
    for (int i = 0; i < n; i++)
        for (int j = i; j > 0; j--)
            if (a[j] < a[j-1])
                swap(a, j, j-1); 
}

void quick_sort(int* a, int start, int end) {
    if (end - start <= 1)
        return;

    int p = start + rand() % (end - start);
    int less, greater;
    partition_3way(a, start, end, &less, &greater, p);

    randomized_quicksort(a, start, less);
    randomized_quicksort(a, greater + 1, end);
}

int select_min_pos(int* a, int start, int end) {
    int min_pos = start;
    int min = a[start];

    for (int i = start+1; i < end; i++) {
        if (a[i] < min) {
            min = a[i];
            min_pos = i;
        }
    }

    return min_pos;
}

int* merge_sort(int* a, int start, int end) {
    int* result;
    
    if (end == start) {
        result = (int*) malloc(sizeof(int));
        result[0] = a[start];
        return result;
    }

    int mid = (start + end) / 2;
    int* left = merge_sort(a, start, mid);
    int* right = merge_sort(a, mid + 1, end);
    
    result = merge(left, right, mid - start + 1, end - mid);
    free(left);
    free(right);

    return result;
}
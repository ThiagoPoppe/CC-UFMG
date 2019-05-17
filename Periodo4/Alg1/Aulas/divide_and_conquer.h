#ifndef DIVIDE_AND_CONQUER_H
#define DIVIDE_AND_CONQUER_H

void randomized_quicksort(int* a, int start, int end);

int partition(int* a, int start, int end, int pivot);
int partition_3way(int* a, int start, int end, int* lt, int *gt, int pivot);
int quick_select(int* a, int start, int end, int k);
int MoM_select(int* a, int n, int k);

int* merge(int* a, int* b, int n, int m);
int* merge_and_count(int* a, int* b, int n, int m);

#endif
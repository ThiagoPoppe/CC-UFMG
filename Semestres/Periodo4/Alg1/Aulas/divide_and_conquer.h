#ifndef DIVIDE_AND_CONQUER_H
#define DIVIDE_AND_CONQUER_H

#include "graph.h"

void randomized_quicksort(int* a, int start, int end);

int partition(int* a, int start, int end, int pivot);
void partition_3way(int* a, int start, int end, int* lt, int *gt, int pivot);
int quick_select(int* a, int start, int end, int k);
int median_of_medians(int* a, int n);
int MoM_select(int* a, int n, int k);

int MoM_select_edge(Edge* edges, int size, int k);
int partition_edges(Edge* edges, int start, int end, int pivot);
void partition_3way_edge(Edge* edges, int start, int end, int* lt, int* gt, int pivot);

int* merge(int* a, int* b, int n, int m);
int* merge_and_count(int* a, int* b, int n, int m);

#endif
#ifndef MOM_H
#define MOM_H

void swap(int* a, int i, int j);
void insertion_sort(int* a, int n);

int partition_3way(int* a, int start, int end, int* lt, int* gt, int pivot);
int MoM_select(int* a, int size, int k);

#endif
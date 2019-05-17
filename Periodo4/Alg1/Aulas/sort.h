#ifndef SORT_H
#define SORT_H

void swap(int* a, int i, int j);

void bubble_sort(int* a, int n);
void selection_sort(int* a, int n);
void insertion_sort(int* a, int n);
void quick_sort(int* a, int start, int end);

int select_min_pos(int* a, int start, int end);

int* merge_sort(int* a, int start, int end);

#endif
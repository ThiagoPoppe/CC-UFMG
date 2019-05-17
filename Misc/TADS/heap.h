#ifndef HEAP_H
#define HEAP_H

void swap(int* v, int i, int j);
void maxHeapfy(int* heap, int n, int i);
void minHeapfy(int* heap, int n, int i);
void buildMinHeap(int* v, int n);
void buildMaxHeap(int* v, int n);

#endif
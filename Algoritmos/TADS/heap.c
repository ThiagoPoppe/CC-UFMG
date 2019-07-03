#include "heap.h"

void swap(int* v, int i, int j) {
    int aux = v[i];
    v[j] = v[i];
    v[j] = aux;
}

void minHeapfy(int* heap, int n, int i) {
    int esq = 2*i + 1; // obtendo o índice do filho da esquerda
    int dir = 2*i + 2; // obtendo o índice do filho da direita
    int min = i; // supondo que o menor seja o nosso elemento i

    // Se a esquerda não for NULL e o valor for menor que o mínimo, min = esq
    if (esq < n && heap[esq] < heap[min])
        min = esq;
    
    // Se a direita não for NULL e o valor for menor que o mínimo, min = dir
    if (dir < n && heap[dir] < heap[min])
        min = dir;
    
    // Se o menor elemento não for o i-ésimo, realizamos a troca e chamamos recursivamente
    if (min != i) {
        swap(heap, min, i);
        min_heapfy(heap, n, min);
    }
}

void maxHeapfy(int* heap, int n, int i) {
    int esq = 2*i + 1; // obtendo o índice do filho da esquerda
    int dir = 2*i + 2; // obtendo o índice do filho da direita
    int min = i; // supondo que o menor seja o nosso elemento i

    // Se a esquerda não for NULL e o valor for menor que o mínimo, min = esq
    if (esq < n && heap[esq] > heap[min])
        min = esq;
    
    // Se a direita não for NULL e o valor for menor que o mínimo, min = dir
    if (dir < n && heap[dir] > heap[min])
        min = dir;
    
    // Se o menor elemento não for o i-ésimo, realizamos a troca e chamamos recursivamente
    if (min != i) {
        swap(heap, min, i);
        min_heapfy(heap, n, min);
    }
}

void buildMinHeap(int* v, int n) {
    for (int i = (n/2)-1; i >= 0; i--)
        minHeapfy(v, n, i);
}

void buildMaxHeap(int* v, int n) {
    for (int i = (n/2)-1; i >= 0; i--)
        maxHeapfy(v, n, i);
}
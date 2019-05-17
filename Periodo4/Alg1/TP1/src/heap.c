#include <stdio.h>
#include "heap.h"

void swap(Candidato** v, int i, int j) {
    Candidato* aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void minHeapfy(Candidato** heap, int n, int i) {
    int esq = 2*i + 1; // obtendo o índice do filho da esquerda
    int dir = 2*i + 2; // obtendo o índice do filho da direita
    int min = i; // supondo que o menor seja o nosso elemento i

    // Se a esquerda não for NULL e o valor for menor que o mínimo, min = esq
    if (esq < n && heap[esq]->nota < heap[min]->nota)
        min = esq;
    
    // Se a direita não for NULL e o valor for menor que o mínimo, min = dir
    if (dir < n && heap[dir]->nota < heap[min]->nota)
        min = dir;
    
    // Se o menor elemento não for o i-ésimo, realizamos a troca e chamamos recursivamente
    if (min != i) {
        swap(heap, min, i);
        minHeapfy(heap, n, min);
    }
}

void buildMinHeap(Candidato** v, int n) {
    for (int i = (n/2)-1; i >= 0; i--)
        minHeapfy(v, n, i);
}
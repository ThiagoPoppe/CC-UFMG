#ifndef HEAP_H
#define HEAP_H

#include "universidade.h"
#include "candidato.h"

// Função que troca dois candidatos
void swap(Candidato** v, int i, int j);

// Função que gera um min-heap a partir do i-ésimo nó
void minHeapfy(Candidato** heap, int n, int i);

// Função que constrói um min-heap
void buildMinHeap(Candidato** v, int n);

#endif
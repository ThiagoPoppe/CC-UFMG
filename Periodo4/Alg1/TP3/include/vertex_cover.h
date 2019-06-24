#ifndef VERTEX_COVER_H
#define VERTEX_COVER_H

#include "graph.h"

// Função que retorna o mínimo entre dois valores
int min(int a, int b);

// Função que retorna o tamanho de uma instância mínima de um vertex-cover em uma árvore
int tree_vertex_cover(Graph* g);

// Função que mostra o tamanho e vértices de uma instância aproximada (no máximo 2 vezes pior) de um vertex-cover
void approx_vertex_cover(Graph* g);

#endif
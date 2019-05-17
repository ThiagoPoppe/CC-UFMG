#ifndef GRAFO_H
#define GRAFO_H

#include "lista.h"

typedef struct grafoK {
    Lista **vertices;
    int num_v;
    int num_e;
} GrafoK;

GrafoK* criaGrafoK(int n);
void insereAresta(GrafoK* g, int u, int v, int peso);
int retornaAresta(GrafoK* g, int u, int v);
void printGrafoK(GrafoK* g);
void destroyGrafoK(GrafoK* g);

#endif
#include <stdio.h>
#include <stdlib.h>

#include "calculoDist.h"
#include "vetor.h"
#include "grafo.h"

int main(int argc, const char **argv) {
    // Abrindo o arquivo em modo de leitura
    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("*** Erro ao abrir o arquivo ***\n");
        exit(1);
    }

    // Lendo o número de cidades
    int n_cidades;
    fscanf(f, "%d", &n_cidades);

    // Lendo a latitude e longitude
    double lat[n_cidades], lon[n_cidades];
    for (int i = 0; i < n_cidades; i++)
        fscanf(f, "%lf %lf", &lat[i], &lon[i]);

    // Fechando o arquivo
    fclose(f);

    // Criando o grafo completo e computando as distâncias entre cada satélite
    GrafoK* satelites = criaGrafoK(n_cidades);
    Vetor* dist = criaVetor(satelites->num_e);
    int k = 0;
    for (int i = 0; i < n_cidades; i++) {
        for (int j = i+1; j < n_cidades; j++) {
            dist->array[k] = distanceEarthKm(lat[i], lon[i], lat[j], lon[j]);
            insereAresta(satelites, i, j, dist->array[k++]);
        }
    }

    // Imprimindo o grafo completo e desalocando o mesmo
    printGrafoK(satelites);
    destroyGrafoK(satelites);

    destroyVetor(dist);

    return 0;
}
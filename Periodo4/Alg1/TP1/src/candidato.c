#include <stdlib.h>
#include "candidato.h"

Candidato* iniciaCandidatos(FILE* f, int n_cand) {
    // Inicializando o vetor de candidatos
    Candidato* c = (Candidato*) malloc(n_cand * sizeof(Candidato));
    if (c == NULL) {
        printf("*** Erro de memoria ***\n");
        exit(1);
    }

    for (int i = 0; i < n_cand; i++) {
        // Lendo o número de aplicações e nota de cada candidato
        fscanf(f, "%d %d", &c[i].n_apli, &c[i].nota);
        
        // Inicializando o vetor de preferências
        c[i].pref = (int*) malloc(c[i].n_apli * sizeof(int));
        if (c[i].pref == NULL) {
            printf("*** Erro de memoria ***\n");
            exit(1);
        }

        // Iniciando o vetor de preferências de cada candidato
        for (int j = 0; j < c[i].n_apli; j++)
            fscanf(f, "%d", &c[i].pref[j]);

        // Inicializando outros atributos do candidato
        c[i].i_pref = 0;
        c[i].id_cand = i;
        c[i].id_uni = -1;
        c[i].alocado = FALSE;
    }
    fclose(f);

    return c;
}

int estaAlocado(Candidato c) {
    return c.alocado == TRUE;
}

void destroyCandidatos(Candidato c[], int n) {
    for (int i = 0; i < n; i++)
        free(c[i].pref);
    free(c);
}
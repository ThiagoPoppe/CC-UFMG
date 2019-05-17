#include <stdio.h>
#include <stdlib.h>

#include "candidato.h"
#include "universidade.h"

// Função auxiliar para verificar se o arquivo foi aberto com sucesso
void verificaArquivo(FILE* f) {
    if (f == NULL) {
        printf("*** Erro ao abrir o arquivo ***\n");
        exit(1);
    }
}

// Função auxiliar para imprimir o resultado obtido
void printResultado(Candidato c[], int n) {
    // Imprimindo os grupos com alocação
    printf("Grupos com alocacao\n");
    for (int i = 0; i < n; i++) {
        if (c[i].alocado)
            printf("%d %d\n", c[i].id_cand+1, c[i].id_uni+1);
    }

    // Imprimindo os candidatos não alocados
    printf("Candidatos nao alocados\n");
    for (int i = 0; i < n; i++) {
        if (!c[i].alocado)
            printf("%d\n", c[i].id_cand+1);
    }
}

// Função principal
int main(int argc, const char** argv) {   
    FILE* f;
    Candidato* cands;
    Universidade* univs;
    int n_univ, n_cand;

    // Abrindo o arquivo de universidades
    f = fopen(argv[1], "r");
    verificaArquivo(f);
    fscanf(f, "%d", &n_univ);
    univs = iniciaUniversidades(f, n_univ);

    // Abrindo o arquivo de candidatos
    f = fopen(argv[2], "r");
    verificaArquivo(f);
    fscanf(f, "%d", &n_cand);
    cands = iniciaCandidatos(f, n_cand);

    // Alocando nossos candidatos
    for (int i = 0; i < n_cand; i++)
        alocaCandidato(univs, cands, i);

    // Imprimindo o resultado obtido
    printResultado(cands, n_cand);

    // Desalocando os mallocs feitos
    destroyCandidatos(cands, n_cand);
    destroyUniversidades(univs, n_univ);
}

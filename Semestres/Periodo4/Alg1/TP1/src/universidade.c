#include <stdlib.h>

#include "universidade.h"
#include "heap.h"

Universidade* iniciaUniversidades(FILE* f, int n_univ) {
    // Inicializando o vetor de universidades
    Universidade* u = (Universidade*) malloc(n_univ * sizeof(Universidade));
    if (u == NULL) {
        printf("*** Erro de memoria ***\n");
        exit(1);
    }

    for (int i = 0; i < n_univ; i++) {
        // Lendo o número de vagas e a nota mínima da universidade
        fscanf(f, "%d %d", &u[i].n_vagas, &u[i].nota_min);

        // Inicializando o vetor de candidatos na universidade
        u[i].vetor_cand = (Candidato**) malloc(u[i].n_vagas * sizeof(Candidato*));
        if (u[i].vetor_cand == NULL) {
            printf("*** Erro de memoria ***\n");
            exit(1);
        }

        // Inicializando outros atributos da universidade
        u[i].id = i;
        u[i].n_vagas_restantes = u[i].n_vagas;
    }
    fclose(f);

    return u;
}

int estaCheia(Universidade u) {
    return u.n_vagas_restantes == 0;
}

void insereCandidato(Universidade *u, Candidato *c) {
    // Calculando a posição onde o novo candidato será inserido
    int pos = u->n_vagas - u->n_vagas_restantes;

    // Modificando os atributos do candidato para indicar que o mesmo foi alocado
    c->id_uni = u->id;
    c->alocado = TRUE;

    // Atualizando o vetor de candidatos da universidade
    u->vetor_cand[pos] = c;
    u->n_vagas_restantes--;

    // Caso o vetor estiver cheio, iremos transformar o mesmo em um min-heap;
    // Em outras palavras, a raiz será o candidato com a menor nota
    if (estaCheia(*u))
        buildMinHeap(u->vetor_cand, u->n_vagas);
}

int possuiNotaMinima(Universidade u, Candidato c) {
    return c.nota >= u.nota_min ? TRUE : FALSE; 
}

int possuiNotaMelhor(Universidade u, Candidato c) {
    if (c.nota > u.vetor_cand[0]->nota)
        return TRUE;

    // Caso a nota for igual, o candidato a ser escolhido será aquele que tiver 
    // a maior preferencia
    else if (c.nota == u.vetor_cand[0]->nota)
        return c.i_pref < u.vetor_cand[0]->i_pref ? TRUE : FALSE;

    else
        return FALSE;
}

void alocaCandidato(Universidade u[], Candidato c[], int i) {
    // Percorremos o vetor de preferências do candidato
    while (c[i].i_pref < c[i].n_apli) {
        printf("Tentando alocar cand %d\n", i+1);
        int pref = c[i].pref[c[i].i_pref] - 1;

        // Se a universidade não estiver cheia e o candidato possuir nota mínima
        // inserimos o mesmo
        if (!estaCheia(u[pref]) && possuiNotaMinima(u[pref], c[i])) {
            printf("Candidato %d foi inserido\n", i+1);
            insereCandidato(&u[pref], &c[i]);
            break;
        }

        // Se a universidade estiver cheia porém o novo canditato possui uma nota
        // melhor que o candidato com a menor nota, inserimos o primeiro e chamamos
        // recursivamente a mesma função para realocar o candidato retirado
        else if (estaCheia(u[pref]) && possuiNotaMelhor(u[pref], c[i])) {
            printf("Candidato %d foi inserido\n", i+1);
            int retirado = atualizaVetorCandidatos(&u[pref], &c[i]);
            printf("Retirando cand %d\n", retirado + 1);
            alocaCandidato(u, c, retirado);
            break;
        }

        // Senão, passamos para a próxima universidade
        else
            c[i].i_pref++;
    }
}

int atualizaVetorCandidatos(Universidade *u, Candidato *c) {
    // Primeiramente, obtemos o id do candidato a ser retirado
    int retirado = u->vetor_cand[0]->id_cand;

    // Desalocamos o candidato com a menor nota daquela universidade e
    // avançamos no vetor de preferência do mesmo
    u->vetor_cand[0]->alocado = FALSE;
    u->vetor_cand[0]->id_uni = -1;
    u->vetor_cand[0]->i_pref++;
    
    // Modificando os atributos do novo candidato para indicar que o mesmo foi alocado
    c->id_uni = u->id;
    c->alocado = TRUE;

    // Atualizando o vetor de candidatos e construindo um novo min-heap
    // a partir dessa atualização
    u->vetor_cand[0] = c;
    minHeapfy(u->vetor_cand, u->n_vagas, 0);

    return retirado;
}

void destroyUniversidades(Universidade u[], int n) {
    for (int i = 0; i < n; i++)
        free(u[i].vetor_cand);
    free(u);
}
#ifndef UNIVERSIDADE_H
#define UNIVERSIDADE_H

#include <stdio.h>
#include "candidato.h"

/*
    -> Estrutura da Universidade
    
    Atributos:
        id: Id da universidade
        n_vagas: Número de vagas
        n_vagas_restantes: Número de vagas restantes
        nota_min: Nota mínima para passar
        vetor_cand: vetor de candidatos alocados (um ponteiro para o candidato)
*/
typedef struct universidade {
    int id;                
    int n_vagas;
    int n_vagas_restantes;
    int nota_min;
    Candidato** vetor_cand;
} Universidade;

// Função que inicializa o vetor de universidades
Universidade* iniciaUniversidades(FILE* f, int n_univ);

// Função que retorna se a universidade está cheia
int estaCheia(Universidade u);

// Função que tenta alocar um candidato na universidade
void alocaCandidato(Universidade u[], Candidato c[], int i);

// Função que insere um candidato na universidade
void insereCandidato(Universidade *u, Candidato *c);

// Função que retorna se o candidato possui nota mínima
int possuiNotaMinima(Universidade u, Candidato c);

// Função que retorna se o candidato possui nota melhor do que o menor da vetor;
// Essa função também verifica um caso especial onde ambos possuem a mesma nota
// mas preferências diferentes
int possuiNotaMelhor(Universidade u, Candidato c);

// Função que atualiza o vetor de candidatos, retornando o id do candidato retirado
int atualizaVetorCandidatos(Universidade *u, Candidato *c);

// Função que desaloca o vetor de universidades
void destroyUniversidades(Universidade u[], int n);

#endif

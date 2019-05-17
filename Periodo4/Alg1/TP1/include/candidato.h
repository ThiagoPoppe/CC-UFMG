#ifndef CANDIDATO_H
#define CANDIDATO_H

// Definindo TRUE e FALSE apenas para melhorar a legibilidade do código
#define TRUE 1
#define FALSE 0

#include <stdio.h>

/*
    -> Estrutura do Candidato
    Atributos:
        id_cand: Id do candidato
        id_uni: Id da universidade
        nota: Nota do candidato
        n_apli: Número de aplicações
        pref: Vetor de preferências
        i_pref: Índice da preferência
        alocado: "Booleano" que verifica se está alocado
*/
typedef struct candidato {
    int id_cand;
    int id_uni;
    int nota;
    int n_apli;
    int *pref;
    int i_pref;
    int alocado;
} Candidato;

// Função que inicializa o vetor de candidatos
Candidato* iniciaCandidatos(FILE* f, int n_cand);

// Função que retorna se o candidato está alocado
int estaAlocado(Candidato c);

// Função que desaloca o vetor de candidatos
void destroyCandidatos(Candidato c[], int n);

#endif
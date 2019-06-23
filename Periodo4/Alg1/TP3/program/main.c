#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "vertex_cover.h"

int main(int argc, const char** argv) {
    // Abrindo o arquivo de leitura
    FILE* f_in = fopen(argv[2], "r");
    if (f_in == NULL) {
        printf("*** Não foi possível abrir o arquivo %s ***\n", argv[2]);
        exit(1);
    }

    // Lendo o número de vértices e arestas
    int num_vertices, num_edges;
    fscanf(f_in, "%d %d", &num_vertices, &num_edges);

    // Criando o grafo
    Graph* g = create_graph(num_vertices, num_edges);

    // Verificando qual tarefa iremos executar
    if (strcmp(argv[1], "tarefa1") == 0) {
        // Lendo as conexões e inserindo arestas na árvore
        int u, v;
        for (int i = 0; i < g->num_edges; i++) {
            fscanf(f_in, "%d %d", &u, &v);
            insert_edge_tree(g, u, v);
        }

        // Imprimindo o tamanho mínimo do vertex-cover
        printf("%d\n", tree_vertex_cover(g));
    }
    else if (strcmp(argv[1], "tarefa2") == 0) {
        // Lendo as conexões e inserindo arestas no grafo
        int u, v;
        for (int i = 0; i < g->num_edges; i++) {
            fscanf(f_in, "%d %d", &u, &v);
            insert_edge(g, u, v);
        }

        // Computando a solução aproximada para o vertex-cover
        aprox_vertex_cover(g);
    }
    else
        printf("*** Não foi possível realizar a tarefa %s ***\n", argv[1]);

<<<<<<< HEAD
    // Fechando o arquivo de entrada
    fclose(f_in);
=======
    aprox_min_vertex_cover(g);
>>>>>>> c89f06c320ce897255a002e10a5af0824294261a

    // Desalocando o grafo
    destroy_graph(g);

    return 0;
}
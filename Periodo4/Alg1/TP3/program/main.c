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

    // Lendo as conexões e inserindo arestas no grafo
    int u, v;
    for (int i = 0; i < g->num_edges; i++) {
        fscanf(f_in, "%d %d", &u, &v);
        insert_edge(g, u, v);
    }

    // Verificando qual tarefa iremos executar
    if (strcmp(argv[1], "tarefa1") == 0) {
        int ans = tree_vertex_cover(g);
        printf("%d\n", ans);
    }

    else if (strcmp(argv[1], "tarefa2") == 0)
        approx_vertex_cover(g);
    
    else
        printf("*** Não foi possível realizar a tarefa %s ***\n", argv[1]);

    // Fechando o arquivo de entrada
    fclose(f_in);

    // Desalocando o grafo
    destroy_graph(g);

    return 0;
}
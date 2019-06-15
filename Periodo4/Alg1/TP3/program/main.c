#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main(int argc, const char **argv) {
    // Abrindo o arquivo passado via linha de comando
    FILE* f = fopen(argv[2], "r");
    if (f == NULL) {
        printf("*** Erro ao abrir o arquivo ***\n");
        exit(1);
    }

    // Lendo o número de vértices e arestas do nosso grafo
    int num_vertices, num_edges;
    fscanf(f, "%d %d", &num_vertices, &num_edges);

    // Criando um grafo com esse número de vértices e arestas
    Graph* g = create_graph(num_vertices, num_edges);

    // Inserindo arestas no nosso grafo segundo o arquivo de texto
    int v, u;
    for (int i = 0; i < num_edges; i++) {
        fscanf(f, "%d %d", &v, &u);
        insert_edge(g, v, u);
    }

    printf("%d\n", min_vertex_cover(g, g->vertices[2]->head));
    aprox_min_vertex_cover(g);

    destroy_graph(g);

    return 0;
}
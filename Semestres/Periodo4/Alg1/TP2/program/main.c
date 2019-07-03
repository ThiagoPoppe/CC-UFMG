#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "camerini.h"
#include "distance.h"

int main(int argc, const char **argv) {
    // Abrindo o arquivo em modo de leitura
    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("*** Erro ao abrir o arquivo ***\n");
        exit(1);
    }

    // Lendo o número de cidades
    int n_tele;
    fscanf(f, "%d", &n_tele);

    // Lendo a latitude e longitude
    double lat[n_tele], lon[n_tele];
    for (int i = 0; i < n_tele; i++)
        fscanf(f, "%lf %lf", &lat[i], &lon[i]);

    // Fechando o arquivo
    fclose(f);

    // Criando o grafo completo e computando as distâncias entre cada telescópio
    Graph* telescopes = create_graph(n_tele);

    // Inserindo nossas arestas no grafo
    for (int i = 0; i < telescopes->num_vertices; i++) {
        for (int j = i+1; j < telescopes->num_vertices; j++) {
            int dist = distanceEarthKm(lat[i], lon[i], lat[j], lon[j]);
            insert_undirected_edge(telescopes, i, j, dist);
        }
    }
    
    // Imprimindo a aresta "bottleneck" do nosso grafo
    printf("%d\n", get_bottleneck_edge(telescopes));

    // Desalocando o grafo de telescópios
    destroy_graph(telescopes);

    return 0;
}
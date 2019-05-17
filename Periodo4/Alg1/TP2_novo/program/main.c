#include <stdio.h>
#include <stdlib.h>

#include "calculo_dist.h"
#include "matrix_graph.h"
#include "list_graph.h"
#include "MoM.h"

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
    List_Graph* telescopes = create_list_graph(n_tele);

    for (int i = 0; i < telescopes->V; i++) {
        for (int j = i+1; j < telescopes->V; j++) {
            int dist = distanceEarthKm(lat[i], lon[i], lat[j], lon[j]);
            insert_edge_list_graph_und(telescopes, i, j, dist);
        }
    }

    print_list_graph(telescopes);
    printf("V = %d\nE = %d\n", telescopes->V, telescopes->E);

    printf("\n");
    MBST(telescopes);

    // Desalocando o grafo de telescópios
    destroy_list_graph(telescopes);

    return 0;
}
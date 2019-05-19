#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

#include <math.h>

#define earthRadiusKm 6371.0
#define PI 3.14159265359

double deg2rad(double deg) {
    return (deg * PI / 180);
}

int distanceEarthKm(double lat1d, double lon1d, double lat2d, double lon2d) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return (int) 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}


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

    for (int i = 0; i < telescopes->num_vertices; i++) {
        for (int j = i+1; j < telescopes->num_vertices; j++) {
            int dist = distanceEarthKm(lat[i], lon[i], lat[j], lon[j]);
            insert_undirected_edge(telescopes, i, j, dist);
        }
    }

    Edge edges[telescopes->num_edges];
    get_edges(telescopes, edges);

    printf("%d\n", MBST(telescopes, edges));

    // Desalocando o grafo de telescópios
    destroy_graph(telescopes);

    return 0;
}
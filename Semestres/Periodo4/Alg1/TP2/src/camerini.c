#include "camerini.h"

// Função auxiliar para trocar duas arestas no vetor de arestas
void swap_edges(Edge* edges, int i, int j) {
    Edge aux = edges[i];
    edges[i] = edges[j];
    edges[j] = aux;
}

// Função que ordena o vetor de arestas usando insertion sort
void insertion_sort_edges(Edge* edges, int n) {
    for (int i = 0; i < n; i++)
        for (int j = i; j > 0; j--)
            if (edges[j].weight < edges[j-1].weight)
                swap_edges(edges, j, j-1); 
}

// Função que particiona o vetor de arestas em 3 grupos:
// 1) Left: Aquelas arestas que possuem peso menor que a aresta pivot
// 2) Middle: Aquelas arestas que possuem peso igual a aresta pivot
// 3) Right: Aquelas arestas que posseum peso maior que a aresta pivot
void partition_3way_edge(Edge* edges, int start, int end, int* lt, int* gt, int pos_pivot) {
    int pivot = edges[pos_pivot].weight;
    int i = start + 1;

    *lt = start;
    *gt = end - 1;

    swap_edges(edges, start, pos_pivot);

    while (i <= *gt) {
        if (edges[i].weight < pivot) {
            swap_edges(edges, i, *lt);
            (*lt)++;
            i++;
        }
        else if (edges[i].weight > pivot) {
            swap_edges(edges, i, *gt);
            (*gt)--;
        }
        else
            i++;
    }
}

// Função auxiliar que computa a mediana das medianas de um vetor de arestas
Edge median_of_medians_edge(Edge* edges, int n) {
    // Caso o tamanho seja menor ou igual a 5 podemos ordenar e retornar a aresta do meio
    if (n <= 5) {
        insertion_sort_edges(edges, n);
        return edges[n/2];
    }

    // Computando o número de grupos de tamanho 5
    int group_size = n / 5;
    Edge aux[5];
    Edge medians[group_size];

    for (int i = 0; i < group_size; i++) {
        for (int j = 0; j < 5; j++)
            aux[j] = edges[5*i + j];

        // Ordenando cada grupo de tamanho 5 e calculando sua mediana
        insertion_sort_edges(aux, 5);
        medians[i] = aux[5/2];
    }   

    // Chamando recursivamente para computar a mediana aproximada do vetor de medianas
    return median_of_medians_edge(medians, group_size);
}

// Função que retorna o peso da k-ésima menor aresta usando o algoritmo 
// de median_of_medians para garantir complexidade O(n)
int MoM_select_edge(Edge* edges, int n, int k) {
    // Definimos o pivot como sendo a mediana das medianas do vetor de arestas
    Edge pivot = median_of_medians_edge(edges, n);

    // Procuramos a posição daquele pivot no vetor de arestas
    int pos_pivot = -1;
    for (int i = 0; i < n; i++)
        if (edges[i].v == pivot.v && edges[i].u == pivot.u && edges[i].weight == pivot.weight) {
            pos_pivot = i;
            break;
        }


    // Repartimos o vetor de arestas em 3 grupos (Left, Middle, Right)
    // lt -> posição do primeiro pivot no grupo Middle
    // gt -> posição do último pivot no grupo Middle
    int lt, gt;
    partition_3way_edge(edges, 0, n, &lt, &gt, pos_pivot);

    // Caso a k-ésima posição seja menor que lt, realizamos o mesmo algoritmo no vetor da esquerda
    if (k < lt) {
        Edge left[lt];
        for (int i = 0; i < lt; i++)
            left[i] = edges[i];
    
        return MoM_select_edge(left, lt, k);
    }

    // Caso a k-ésima posição seja maior que gt, realizamos o mesmo algoritmo no vetor da direta
    // Obs.: Atualizamos o valor de k
    else if (k > gt) {
        Edge right[n - gt];
        int i = 0;
        for (int j = gt + 1; j < n; j++)
            right[i++] = edges[j];
    
        return MoM_select_edge(right, n - (gt + 1), k - gt - 1);
    }

    // Caso contrário, o pivot escolhido é o k-ésimo menor elemento
    else
        return pivot.weight;
}

// Função que executa o algoritmo de Camerini para encontrar a aresta bottleneck em um grafo
int get_bottleneck_edge(Graph* g) {
    // Caso tenhamos apenas uma aresta, retornamos o peso da mesma
    if (g->num_edges == 1) {
        return g->edges[0].weight;;   
    }

    // Computamos a mediana das arestas
    int bottleneck;
    int median = MoM_select_edge(g->edges, g->num_edges, g->num_edges / 2);

    // Criamos 2 grafos induzidos A e B utilizando a mediana como referência
    Graph* A = create_graph(g->num_vertices);
    Graph* B = create_graph(g->num_vertices);

    create_induce_graphs(g, A, B, median);

    // Caso B seja conexo, chamamos recursivamente o algoritmo para B
    if (is_connected(B)) {
        bottleneck = get_bottleneck_edge(B);
    }
    else {
            // Caso contrário achamos os componentes conexos de B
        ConnectedComponents* cc = return_connected_components(B);
        
        // Criamos um grafo C tal que o mesmo possui super vértices de B
        Graph* C = create_graph(cc->num_components);
        
        // Inserimos arestas de A no nosso grafo C tal que a aresta não ligue o mesmo componente conexo em B
        for (int i = 0; i < A->num_edges; i++) {
            int v = A->edges[i].v;
            int u = A->edges[i].u;

            if (cc->vertices[v] != cc->vertices[u])
                insert_undirected_edge(C, cc->vertices[v], cc->vertices[u], A->edges[i].weight);
        }

        // Chamamos recursivamente o algoritmo para o grafo C
        bottleneck = get_bottleneck_edge(C);

        // Desalocamos a memória alocada para C e para os componentes conexos de B
        destroy_graph(C);
        destroy_connected_components(cc);
    }

    // Desalocamos a memória alocada para A e B
    destroy_graph(A);
    destroy_graph(B);

    return bottleneck;
}
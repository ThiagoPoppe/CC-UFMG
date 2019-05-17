#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H

#include "list.h"

typedef struct list_graph {
    int V;
    int E;
    List** adj_list;
} List_Graph;

List_Graph* create_list_graph(int V);
Edge* get_edge(List_Graph* g, int v, int u);

void insert_edge_list_graph(List_Graph* g, int v, int u, int weight);
void insert_edge_list_graph_und(List_Graph* g, int v, int u, int weight);

void partition_graph(List_Graph* g, List_Graph* less, List_Graph* greater, int pivot);

void print_list_graph(List_Graph* g);
void destroy_list_graph(List_Graph* g);

int MBST(List_Graph* g);

int* return_edges(List_Graph* g);

#endif
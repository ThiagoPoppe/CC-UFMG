#ifndef CAMERINI_H
#define CAMERINI_H

#include "graph.h"

void swap_edges(Edge* edges, int i, int j);
void insertion_sort_edges(Edge* edges, int n);
void partition_3way_edge(Edge* edges, int start, int end, int* lt, int* gt, int pos_pivot);

Edge median_of_medians(Edge* edges, int n);

int MoM_select_edge(Edge* edges, int n, int k);
int get_bottleneck_edge(Graph* g);

#endif
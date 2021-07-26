#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"

#define INFINITIVE_VALUE 99999

typedef struct
{
    JRB edges;
    JRB vertices;
    JRB SP; // changed
} Graph;

Graph createGraph(); // changed
void addVertex(Graph, int id, char* name);
char *getVertex(Graph, int id);
void addEdge(Graph G, int v1, int v2, double weight);
int indegree(Graph, int v, int* output);
int outdegree(Graph, int v, int* output);
int isDAG(Graph);
void dropGraph(Graph); // changed
double getEdgeValue(Graph, int v1, int v2);
int getAdjacentVertices(Graph, int v, int *output, double *w);
double shortestPath(Graph, int s, int t, int* path, int* lengh);

#endif /* graph.h */

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 20
#define MAX_EDGES 100

#define FALSE 0
#define TRUE 1

typedef struct vertex VERTEX;
typedef struct edge EDGE;
typedef struct graph GRAPH;

GRAPH* createGraph(void);
void eraseGraph(GRAPH* g);
void insertVertex(GRAPH* g, double o);
void insertEdge(GRAPH* g, int v, int w, double o);

int numVertices(GRAPH* g);
int numEdges(GRAPH* g);
int *incidentEdges(GRAPH *g, int n);
int opposite(GRAPH *g, int i, int v);

GRAPH* BellmanFord (GRAPH *g, int ini);
double getMin (GRAPH *g, int ini, int fim);
int *getMenorCaminho (GRAPH *g, int ini, int fim, int *vSize);

void printGraph(GRAPH *graph);

#endif // GRAPH_H_INCLUDED


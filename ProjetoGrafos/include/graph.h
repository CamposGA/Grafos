#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define FALSE 0
#define TRUE 1

typedef struct vertex VERTEX;
typedef struct edge EDGE;
typedef struct graph GRAPH;
typedef struct iedge iEDGE;

GRAPH* createGraph(void);
void eraseGraph(GRAPH* g);
void *insertVertex(GRAPH* g, double value);
void *insertEdge(GRAPH* g, int v, int w, double value);

int numVertices(GRAPH* g);
int numEdges(GRAPH* g);
int *incidentEdges(GRAPH *g, int n);
int opposite(GRAPH *g, int i, int v);

GRAPH* BellmanFord (GRAPH *g, int ini);
double getMin (GRAPH *g, int ini, int fim);
int *getMenorCaminho (GRAPH *g, int ini, int fim, int *vSize);

void printGraph(GRAPH *graph);

#endif


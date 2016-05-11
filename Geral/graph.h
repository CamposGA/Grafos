#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "filas.h"

#define MAX_VERTICES 20
#define MAX_EDGES 100

#define FALSE 0
#define TRUE 1

typedef struct vertex Vertex;
typedef struct edge Edge;
typedef struct graph Graph;

Graph* createGraph(void);
void eraseGraph(Graph* g);
void insertVertex(Graph* g, int o);
void insertEdge(Graph* g, int v, int w, int o);

int numVertices(Graph* g);
int numEdges(Graph* g);

int *graphBFS (Graph *g, int v);
int *incidentEdges(Graph *g, int n);
int opposite(Graph *g, int i, int v);

//int *adjacentVertex (Graph *g, int n);

#endif // GRAPH_H_INCLUDED


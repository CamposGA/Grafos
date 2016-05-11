#include "graph.h"
#include "filas.h"

#define FALSE 0
#define TRUE 1

/* Vertex */
struct vertex {
	int value;
	int *edges;
	int nEdges;
    VERTEX * parent;

	int distancia;;
};

/* Edge */
struct edge {
    VERTEX *v1;
    VERTEX *v2;

    int value;
};

/* Graph
** implementado utilizando-se a estrutura: LISTA DE ARESTAS */
struct graph {
    
    VERTEX *vertices;
    EDGE *edges;

    int nVertices;
    int nEdges;
};

GRAPH* createGraph() {
    int i, j;
    GRAPH* g;

    /* Aloca dinamicamente um grafo que é retornado para o usuário */
    g = (GRAPH*) malloc(sizeof(GRAPH));

    if (g) {
        g->nVertices = 0;
        g->nEdges = 0;

        g->vertices = NULL;
        g->edges = NULL;
    }

    return g;
}

/* Apaga um grafo */
void eraseGraph(GRAPH* g) {
    /* Libera o espaço em memória alocado pela função createGraph() */
    free(g);
}

/* Função para adicionar um vértice ao grafo */
void insertVertex(GRAPH* g, int o) {
    int i;

    g->vertices = (VERTEX *) realloc(g->vertices, (g->nVertices + 1) * sizeof(VERTEX));

    g->vertices[g->nVertices].value = o;

    g->vertices[g->nVertices].edges = (int *) malloc (4 * sizeof(int));
    for (i = 0; i < 4; i++) g->vertices[g->nVertices].edges[i] = -1;

    g->vertices[g->nVertices].nEdges = 0;
    g->vertices[g->nVertices].parent = NULL;

    g->nVertices++;
}

/* Função para adicionar uma aresta ao grafo */
void insertEdge(GRAPH* g, int v, int w, int o)  {
    int i;

    g->edges = (EDGE *) realloc (g->edges, ((g->nEdges + 1) * sizeof(EDGE)));

    g->edges[g->nEdges].value = o;
    g->edges[g->nEdges].v1 = &g->vertices[v];
    g->edges[g->nEdges].v2 = &g->vertices[w];

   
    g->vertices[v].edges[g->vertices[v].nEdges] = g->nEdges;
    g->vertices[v].nEdges++;

    g->vertices[w].edges[g->vertices[w].nEdges] = g->nEdges;
    g->vertices[w].nEdges++;

    g->nEdges++;

}

/* MÉTODOS GERAIS */
/* Função para acessar o número de vértices de um grafo */
int numVertices(GRAPH* g) {
    return g->nVertices;
}

/* Função para acessar o número de arestas de um grafo */
int numEdges(GRAPH* g) {
    return g->nEdges;
}


int *incidentEdges(GRAPH *g, int n) {
    return g->vertices[n].edges;
}

int opposite(GRAPH *g, int i, int v) {
    return g->edges[i].v1->value == v ? g->edges[i].v2->value : g->edges[i].v1->value;
}

void printGraph (GRAPH *graph) {
    int i;

    for (i = 0; i < graph->nEdges; i++) {
        printf ("%d(%d) -(%d)- %d\n", graph->edges[i].v1->value, graph->edges[i].v1->nEdges, graph->edges[i].value, graph->edges[i].v2->value);
    }
}

GRAPH *BellmanFord (GRAPH* g, int ini) {
    int i, j, t;
    int *iEdges;
    int flag;

    VERTEX *v;
    VERTEX *z;
    EDGE *e;

    for (i = 0; i < g->nVertices; i++) {
        g->vertices[i].parent = NULL;
        
        if (g->vertices[i].value == ini) {
            g->vertices[i].distancia = 0; 
        } else  g->vertices[i].distancia = 2000;

    }

    for (t = 0; t < g->nVertices; t++) {
        flag = 1;

        for (i = 1; i < g->nVertices; i++) {
            iEdges = incidentEdges (g, i);
            v = &g->vertices[i];
            
            //printf("ola %d\n", g->vertices[i].nEdges);
            for (j = 0; j < v->nEdges; j++) {
                //printf("at'e aqui\n"); 
                e = &g->edges[iEdges[j]];
                z = &g->vertices[opposite (g, iEdges[j], v->value)];
                
                //printf("V: %d d: %d\nZ: %d d: %d\nE: %d\n", v->value, v->distancia, z->value, z->distancia, e->value);

                if (z->distancia + e->value < v->distancia) {
                    v->distancia = z->distancia + e->value;
                    v->parent = z;
                    flag = 0;
                    //printf("Nova distamcia do V: %d", v->distancia);
                }
                //printf("\n\n");
            }            
        }

         if (flag == 1) {
            //printf("\n%d\n", t);
            return g;
        }

    
    }

    return NULL;
}

int getMin (GRAPH *g, int ini, int fim) {
    
    if (BellmanFord (g, ini)) {
        return g->vertices[fim].distancia;

    } else return -1;
}

int *getMenorCaminho (GRAPH *g, int ini, int fim, int *vSize) {
    int *caminho = NULL;
    int size = 0;
    int i = 0;

    VERTEX *parent = NULL;

    if (BellmanFord (g, ini)) {
            
        parent = &g->vertices[fim];
        while (parent != NULL) {

            caminho = realloc (caminho, (size+1) * sizeof(int));
            caminho[size] = parent->value;
           
            size++;
            parent = parent->parent;       
        }

    }

    (*vSize) = size;
    return caminho;
}

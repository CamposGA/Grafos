#include "graph.h"
#include "filas.h"

#define FALSE 0
#define TRUE 1

#define EXPLORADO 1
#define DESCOBERTO 0
#define N_DESCOBERTO -1

/* Vertex */
struct vertex {
	int value;
	int *edges;
	int n_edges;
	int label;
};

/* Edge */
struct edge {
    Vertex *v1;
    Vertex *v2;
    int label;

    int value;
};

/* Graph
** implementado utilizando-se a estrutura: LISTA DE ARESTAS */
struct graph {
    /* vetor estático que armazena os vértices */
    Vertex *vertices;

    /* vetor estático que armazena as arestas */
    Edge *edges;

    /* armazena o número de vértices e o número de arestas do grafo*/
    int n_vertices, n_edges;
};

Graph* createGraph() {
    int i, j;
    Graph* g;

    /* Aloca dinamicamente um grafo que é retornado para o usuário */
    g = (Graph*) malloc(sizeof(Graph));

    if (g) {
        g->n_vertices = 0;
        g->n_edges = 0;

        g->vertices = NULL;
        g->edges = NULL;
    }

    return g;
}

/* Apaga um grafo */
void eraseGraph(Graph* g) {
    /* Libera o espaço em memória alocado pela função createGraph() */
    free(g);
}

/* Função para adicionar um vértice ao grafo */
void insertVertex(Graph* g, int o) {
    int i;

    g->vertices = (Vertex *) realloc(g->vertices, (g->n_vertices + 1) * sizeof(Vertex));

    g->vertices[g->n_vertices].value = o;

    g->vertices[g->n_vertices].edges = (int *) malloc (4 * sizeof(int));
    for (i = 0; i < 4; i++) g->vertices[g->n_vertices].edges[i] = -1;

    g->vertices[g->n_vertices].n_edges = 0;
    g->vertices[g->n_vertices].label = -1;

    g->n_vertices++;
}

/* Função para adicionar uma aresta ao grafo */
void insertEdge(Graph* g, int v, int w, int o)  {
    int i;

    g->edges = (Edge *) realloc (g->edges, ((g->n_edges + 1) * sizeof(Edge)));

    g->edges[g->n_edges].value = o;
    g->edges[g->n_edges].v1 = &g->vertices[v];
    g->edges[g->n_edges].v2 = &g->vertices[w];

    //printf("Aresta %d: %d %d\n", o, g->vertices[v].value, g->vertices[w].value);


    g->vertices[v].edges[g->vertices[v].n_edges] = g->n_edges;
    g->vertices[v].n_edges++;

    g->vertices[w].edges[g->vertices[w].n_edges] = g->n_edges;
    g->vertices[w].n_edges++;

    g->edges[g->n_edges].label = -1;
    g->n_edges++;

}

/* MÉTODOS GERAIS */
/* Função para acessar o número de vértices de um grafo */
int numVertices(Graph* g) {
    return g->n_vertices;
}

/* Função para acessar o número de arestas de um grafo */
int numEdges(Graph* g) {
    return g->n_edges;
}

int *graphBFS (Graph *graph, int v) {
    FILA *fila = createFila ();
    int *pais = (int *) calloc (graph->n_vertices, sizeof(int));
    int *edges = NULL;
    addNo(v, fila);

    int i;
    int x, y;

    for (i = 0; i < graph->n_vertices; i++) {
        pais[i] = -1;
    }

    while (!vazia(fila)) {
        x = rmNo(fila);

        //printf("Vertice %d explorado\n", x);
        graph->vertices[x].label = EXPLORADO;

        edges = incidentEdges(graph, x);
        for (i = 0; i < 4; i++) {
            if (edges[i] != -1) {
                y = opposite(graph, edges[i], x);

                if (graph->vertices[y].label == N_DESCOBERTO) {
                    //printf("Colocando na fila o no %d\n", y);
                    addNo(y, fila);
                    graph->vertices[y].label = DESCOBERTO;
                    pais[y] = x;
                }
            }
        }


    }

    /*
    for (i = 0; i < graph->n_vertices; i++) {
        printf("%d %d\n", i, pais[i]);
    }*/
    return pais;
}


int *incidentEdges(Graph *g, int n) {
    return g->vertices[n].edges;
}

int opposite(Graph *g, int i, int v) {
    return g->edges[i].v1->value == v ? g->edges[i].v2->value : g->edges[i].v1->value;
}
/*
void printGraph(Graph* g) {
    int i, j, num_vertices, num_edges;

    num_edges = numEdges(g);
    num_vertices = numVertices(g);
    printf("%d\n%d\n", num_vertices, num_edges);

    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == TRUE)
            printf("%d %d\n", i, g->vertices[i].value);
    }

    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == TRUE) {
            if (g->edges[j].v1 > g->edges[j].v2) {
                printf("%d %d %d %d\n", j, g->edges[j].v2, g->edges[j].v1, g->edges[j].value);
            } else {
                printf("%d %d %d %d\n", j, g->edges[j].v1, g->edges[j].v2, g->edges[j].value);
            }
        }
    }
}
*/


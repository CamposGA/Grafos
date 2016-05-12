#include "graph.h"

#define FALSE 0
#define TRUE 1

/* Vertex */
struct vertex {
	int value;
	int *edges;
	int nEdges;
    VERTEX * parent;

	double distancia;;
};

/* Edge */
struct edge {
    VERTEX *v1;
    VERTEX *v2;

    double value;
};

/* Graph*/
struct graph {
    
    VERTEX *vertices;
    EDGE *edges;

    int nVertices;
    int nEdges;
};

/* GRAPH* createGraph() - Inicializa um grafo vazio
 *
 *  Parameter:
 *      -
 *  Return:
 *      GRAPH * - Grafo inicializado
 */
GRAPH *createGraph() {
    int i, j;
    GRAPH* g;

    /* Aloca dinamicamente um grafo que é retornado para o usuário */
    g = (GRAPH*) malloc(sizeof(GRAPH));

    /*Iicializa as variaveis*/
    if (g) {
        g->nVertices = 0;
        g->nEdges = 0;

        g->vertices = NULL;
        g->edges = NULL;
    }

    return g;
}

/* void eraseGraph(GRAPH* g) - Libera a memoria ocupada por um grafo
 *
 *  Parameter:
 *      GRAPH *g - Grafo a ser apagado
 *  Return:
 *      -
 */
void eraseGraph(GRAPH *g) {
    int i, j;

    /*Libera o vetor de arestas de cada vertice*/
    for (i = 0; i < g->nVertices; i++) {
        free (g->vertices[i].edges);
    }
    
    /*Libera restante das listas e o espaço ocupado pela struct GRAPH*/
    free (g->vertices);
    free (g->edges);
    free(g);
}

/* void insertVertex(GRAPH* g, double o) - Adiciona um vertice no grafo g
 *
 *  Parameter:
 *      GRAPH *g - Grafo onde o vertice sera adicionado
 *      double o - Valor do vertice
 *  Return:
 *      -
 */
void insertVertex(GRAPH* g, double o) {
    int i;

    /*Aumenta o tamanho do vetor de vertices*/
    g->vertices = (VERTEX *) realloc(g->vertices, (g->nVertices + 1) * sizeof(VERTEX));

    /*Inicia as variaveis da aresta como 0 ou NULL, com exceç~ao do valor*/
    g->vertices[g->nVertices].value = o;
    g->vertices[g->nVertices].edges = NULL;
    g->vertices[g->nVertices].nEdges = 0;
    g->vertices[g->nVertices].parent = NULL;

    /*Atualiza o contador de vertices*/
    g->nVertices++;
}

/* void insertEdge(GRAPH* g, int v, int w, double o) - Adiciona uma aresta no grafo g
 *
 *  Parameter:
 *      GRAPH *g - Grafo onde a aresta sera adicionada
 *      int v - indice na lista de vertices de um dos vertices ligado a aresta
 *      int w - indice na lista de vertices de um dos vertices ligado a aresta
 *      double o - Peso da aresta
 * Return:
 *      -
 */
void insertEdge(GRAPH* g, int v, int w, double o)  {
    int i;

    /*Aumenta o vetor de arestas*/
    g->edges = (EDGE *) realloc (g->edges, ((g->nEdges + 1) * sizeof(EDGE)));

    /*Armazena dados na struct aresta*/
    g->edges[g->nEdges].value = o;
    g->edges[g->nEdges].v1 = &g->vertices[v];
    g->edges[g->nEdges].v2 = &g->vertices[w];

  
    /*Adiciona a aresta na lista de arestas do vertice v*/
    g->vertices[v].edges = (int *) realloc (g->vertices[v].edges, (g->vertices[v].nEdges + 1) * sizeof(int));
    g->vertices[v].edges[g->vertices[v].nEdges] = g->nEdges;
    g->vertices[v].nEdges++;

    /*Adiciona a aresta na lista de arestas do vertice v*/
    g->vertices[w].edges = (int *) realloc (g->vertices[w].edges, (g->vertices[w].nEdges + 1) * sizeof(int));
    g->vertices[w].edges[g->vertices[w].nEdges] = g->nEdges;
    g->vertices[w].nEdges++;

    /*Atualiza o contador de arestas*/
    g->nEdges++;
}

/* int numVertices(GRAPH* g) - Retorna o numero de vertices do grafo g
 *
 *  Parameter:
 *      GRAPH *g - Grafo
 *  Return:
 *      int - Numero de vertices do grafo g
 */
int numVertices(GRAPH* g) {
    return g->nVertices;
}

/* int numEdges(GRAPH* g) - Retorna o numero de arestas do grafo g
 *
 *  Parameter:
 *      GRAPH *g - Grafo
 *  Return:
 */
int numEdges(GRAPH* g) {
    return g->nEdges;
}


/* int *incidentEdges(GRAPH *g, int n) - Retorna as arestas do vertice n
 *
 *  Parameter:
 *      GRAPH *g - Grafo em que a aresta esta contina
 *      int n - Posiçao na lista de vertices do vertice (Vertice)
 *  Return:
 *      int * - Lista das arestas que incidentes ao vertice
 */
int *incidentEdges(GRAPH *g, int n) {
    return g->vertices[n].edges;
}

/* int opposite(GRAPH *g, int i, int v) - Retorna a aresta oposta ao vertice v pela aresta i
 *
 *  Parameter:
 *      GRAPH *g - Grafo
 *      int i - Posiç~ao da aresta na lista de arestas (Aresta)
 *      int v - Posiçao do vertice na lista de vertices (Vertice)
 *  Return:
 *      GRAPH * - Grafo inicializado
 */
int opposite(GRAPH *g, int i, int v) {
    return g->edges[i].v1->value == v ? g->edges[i].v2->value : g->edges[i].v1->value;
}

/* void printGraph (GRAPH *graph) - Imprime as arestas de um grafo no formato:
 *  v1-(o)-v2       Em que 'v' representa um vertice e 'o' o peso da aresta   
 *  v2-(o)-v4
 *  ...
 *
 *  Parameter:
 *      GRAPH *graph - Grafo
 *  Return:
 *      -
 */
void printGraph (GRAPH *graph) {
    int i;

    for (i = 0; i < graph->nEdges; i++) {
        printf ("%d-(%lf)- %d\n", graph->edges[i].v1->value, graph->edges[i].value, graph->edges[i].v2->value);
    }
}

/* GRAPH *BellmanFord (GRAPH* g, int ini) - Executa o algorismo de BellmanFord no grafo g a partir de um vertice ini
 *
 *  Parameter:
 *      GRAPH *g    - Grafo
 *      int ini     - Vertici inicial (distancia 0)
 *  Return:
 *      GRAPH * - Endereço para o grafo g se bem sucedido, NULL caso contrario
 */
GRAPH *BellmanFord (GRAPH* g, int ini) {
    int i, j, t;
    int *iEdges;
    int flag;

    VERTEX *v;
    VERTEX *z;
    EDGE *e;

    /*Limpa variaveis a serem utilizadas e inicia ini.distancia como 0*/
    for (i = 0; i < g->nVertices; i++) {
        g->vertices[i].parent = NULL;
        
        if (g->vertices[i].value == ini) {
            g->vertices[i].distancia = 0; 
        } else  g->vertices[i].distancia = 2000;

    }

    
    /*Roda uma vez para cada vertice*/
    for (t = 0; t < g->nVertices; t++) {
        flag = 1;

        /*Para cada vertice roda nVertices vezes*/
        for (i = 0; i < g->nVertices; i++) {
            iEdges = incidentEdges (g, i); 
            v = &g->vertices[i];
            
            /*Para cada aresta incidente no vertice v*/
            for (j = 0; j < v->nEdges; j++) {

                e = &g->edges[iEdges[j]]; //Aresta incidente
                z = &g->vertices[opposite (g, iEdges[j], v->value)]; //Vertice oposto
                
                /*Atualiza a distacia/pai se encontrou um caminho melhor*/
                if (z->distancia + e->value < v->distancia) {
                    v->distancia = z->distancia + e->value;
                    v->parent = z;
                    flag = 0; //Seta flag como 0 quando houver mudança
                }
            }            
        }

        if (flag == 1) return g;
    }

    return NULL;
}

/* double getMin (GRAPH *g, int ini, int fim) - Retorna a menor distancia do vertice ini ao vertice fim. Usando a funç~ao BellmanFord().
 *
 *  Parameter:
 *      GRAPH *g - Grafo
 *      int ini - Indice na lista de vertices do vertice inicial (Vertice)
 *      int fim - Indice na lista de vertices do vertice final (Vertice)
 *  Return:
 *      double - Menor distancia ou -1 caso nao seja possivel alcansar fim atravez de ini
 */
double getMin (GRAPH *g, int ini, int fim) {
    

    if (BellmanFord (g, ini)) {
        return g->vertices[fim].distancia;

    } else return -1;
}

/* int *getMenorCaminho (GRAPH *g, int ini, int fim, int *vSize) - Encontra o menor caminho entre do vertice ini ao vertice fim usando a funçao BellFord(). 
 *
 *  Parameter:
 *      GRAPH *g - Grafo
 *      int ini - Indice na lista de vertices do vertice inicial (Vertice)
 *      int fim - Indice na lista de vertices do vertice final (Vertice)
 *      int *vSize - Armazenara o numero de arestas percorridas (tamanho do vetor retornado)
 *  Return:
 *      int * - Vetor com as arestas a serem percorridas do fim para o inicio
 */
int *getMenorCaminho (GRAPH *g, int ini, int fim, int *vSize) {
    int *caminho = NULL;
    int size = 0;
    int i = 0;

    VERTEX *parent = NULL;

    if (BellmanFord (g, ini)) {
            
        /*Segue do fim at'e o ini pelos 'parents'*/
        parent = &g->vertices[fim];
        while (parent != NULL) {

            caminho = realloc (caminho, (size+1) * sizeof(int));
            caminho[size] = parent->value;
           
            size++;
            parent = parent->parent;       
        }

    }

    (*vSize) = size; //Armazena o tamnaho do vetor na variavel vSize
    return caminho;
}

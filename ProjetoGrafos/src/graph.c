#include "graph.h"

#define FALSE 0
#define TRUE 1

/*IncidentEdges*/
struct iedge {
    EDGES *;

    iEDGE *next;
    iEDGE *prior;
};

/*Vertex */
struct vertex {
	int id;

    //Valor
    int value;
	
    //Arestas incidentes
    iEDGE *iEdges;
	int nEdges;

    //Ponteiros para caimnhar na lista
    VERTEX *next;
    VERTEX *prior;
   
    //Variaveis para Execução
    VERTEX * parent;
	double disance;
};

/*Edge */
struct edge {
    int id;

    //Valor
    double value;

    
    VERTEX *v1; //Vertice final v1
    iEDGE *v1Edge; //Ponteiro para a posição no vetor de arestas incidentes 

    VERTEX *v2;
    iEDGE *v2Edge;

    EDGE *next;
    EDGE *prior;

};

/* Graph*/
struct graph {
    
    VERTEX *vertices;
    int nVertices;
    
    EDGE *edges;
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

//TODO
/* void eraseGraph(GRAPH* g) - Libera a memoria ocupada por um grafo
 *
 *  Parameter:
 *      GRAPH *g - Grafo a ser apagado
 *  Return:
 *      -
 */
void eraseGraph(GRAPH *g) {
    int i;

    /*Libera o vetor de arestas de cada vertice*/
    for (i = 0; i < g->nVertices; i++) {
        free (g->vertices[i].edges);
    }
    
    /*Libera restante das listas e o espaço ocupado pela struct GRAPH*/
    free (g->vertices);
    free (g->edges);
    free(g);
}

/* void *insertVertex(GRAPH* g, double value, int id) - Adiciona um vertice no grafo g
 *
 *  Parameter:
 *      GRAPH *g - Grafo onde o vertice sera adicionado
 *      double value - Valor do vertice
 *  Return:
 *      -
 */
void *insertVertex(GRAPH* g, double value, int id) {
    
    VERTEX *v;

    /*Cria o novo vertice inicia as variaveis da aresta*/
    v = (VERTEX *) malloc(sizeof(VERTEX));

    v->id = id;
    v->value = value;
    v->iEdges = NULL;
    v->nEdges = 0;
    v->parent = NULL;
    v->distance = 1000000;

    /*Adiciona aresta no grafo*/
    v->next = g->vertices;
    v->prior = NULL;

    if (g->vertices) g->vertives->prior = v;
    g->vertice = v;

    /*Atualiza o contador de vertices*/
    g->nVertices++;

    return (void *) v;
}

/* void *insertEdge(GRAPH* g, int v, int w, double value) - Adiciona uma aresta no grafo g
 *
 *  Parameter:
 *      GRAPH *g - Grafo onde a aresta sera adicionada
 *      int v - indice na lista de vertices de um dos vertices ligado a aresta
 *      int w - indice na lista de vertices de um dos vertices ligado a aresta
 *      double o - Peso da aresta
 * Return:
 *      -
 */
void *insertEdge(GRAPH* g, int v, int w, double value)  {

    EDGE *e;
    VERTEX *v1;
    VERTEX *v2;

    /*Cria a aresta*/
    e = (EDGE *) malloc (sizeof (EDGE));
    if (e == NULL) return NULL;


    //Busca, a partir do id, os vertices
    v1 = Vsearch (g, v);
    v2 = Vsearch (g, w);
    if (v1 == NULL || v2 == NULL) return NULL;


    /*Set variaveis*/
    e->v1 = v1;
    e->v1Edge = addEdge(v1, e);    

    e->v2 = v2;
    e->v2Edge = addEdge(v2, e);

    e->value = value;
   
    /*Atualiza o contador de arestas*/
    g->nEdges++;

    return (void *) e;
}

/* DONE!
 *  VERTEX *vSearch(GRAPH *g, int id);
 *  iEDGE *addEdge(GRAPH *g, VERTEX *v);
 */

VERTEX *vSearch (GRAPH *g, int id) {
    if (g == NULL) return null;

    VERTEX *aux;
    aux = g->vertices;

    while (aux) {
        if (aux->id == id) break;
        else aux = aux->next;
    }

    return aux;
}

iEDGE *addEdge (VERTEX *v, EDGE *e) {
    
    if (v == NULL) return null;

    /*Cria o novo 'Aresta Incidente'*/
    iEDGE *i;
    i = (iEDGE *) malloc(sizeof(iEDGE));

    /*Adiciona i na lista*/
    i->next = v->iEdges;
    i->prior = NULL;

    if (v->iEdges) v->iEdges->prior = i;
    v->iEdges = i;

    /*Atualiza o contador de arestas incidentes*/
    v->nEdges++;

    return i;

}


/* int numVertices(GRAPH* g) - Retorna o numero de vertices do grafo g
 *
 *  Parameter:
 *      GRAPH *g - Grafo
 *  Return:
 *      int - Numero de vertices do grafo g
 */
int numVertices(GRAPH* g) {
    if (g) return g->nVertices;
    else return -1;
}

/* int numEdges(GRAPH* g) - Retorna o numero de arestas do grafo g
 *
 *  Parameter:
 *      GRAPH *g - Grafo
 *  Return:
 */
int numEdges(GRAPH* g) {
    if (g) return g->nEdges;
    else return -1;
}


/* EDGE *incidentEdges(GRAPH *g, int n) - Retorna as arestas incidentes ao vertice n
 *
 *  Parameter:
 *      GRAPH *g - Grafo em que a aresta esta contina
 *      int n - Posiçao na lista de vertices do vertice (Vertice)
 *  Return:
 *      int * - Lista das arestas que incidentes ao vertice
 */
EDGE *incidentEdges(GRAPH *g, int n) {
    EDGE *iEdges;

    //Copia o vetor edges do vertice em um vetor auxiliar
    iEdges = (EDGE *) malloc (g->vertices[n].nEdges * sizeof (EDGE));
    memcpy (iEdges, g->vertices[n].edges, gg->vertices[n].nEdges * sizeof (EDGE));


    return iEdges;
}

/* TODO: int opposite(GRAPH *g, int i, int v) - Retorna a aresta oposta ao vertice v pela aresta i
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


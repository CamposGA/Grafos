#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "filas.h"

Graph *makeGraph(int m, int n);
int menorCaminho (int *pais, int ini, int fim);

int main(void)
{
    Graph *grafo;
    int m, n;
    int ini, fim;
    int *pais = NULL;
    int c;

    FILA *fila = createFila();

    scanf("%d %d", &n, &m);

    grafo = makeGraph(m, n);

    scanf("%d %d", &ini, &fim);
    pais = graphBFS(grafo, ini);

    c = menorCaminho (pais, ini, fim);
    if (c == -1) printf("NO EXIT");
    else printf("%d", c);


    return 0;
}

Graph *makeGraph(int m, int n) {
    Graph *grafo = NULL;
    grafo = createGraph();
    int i, j;

    int mat[n][m][2];

    //Insere n*m vertices no grafo
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            insertVertex(grafo, j + (i*m));
            scanf("%d", &mat[i][j][0]);
            mat[i][j][1] = 0;
        }
    }

    /*Dois vertices '0' adjacentes na matris recebido indica a existencia de umma aresta ligando-os
    add arestas no grafo*/
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            //printf("%d ", mat[i][j][0]);
            if (mat[i][j][0] == 0 && !mat[i][j][1]) {
                //printf("Inserindo em l: %d c: %d\n %d\n", i, j, ((i+1)*n)+j);

                if (j+1 < m && mat[i][j+1][0] == 0 && !mat[i][j+1][1]) insertEdge(grafo, (j + (i*m)), ((j+1) + (i*m)), 1);
                if (j-1 >= 0 && mat[i][j-1][0] == 0 && !mat[i][j-1][1]) insertEdge(grafo, (j + (i*m)), ((j-1) + (i*m)), 2);
                if (i+1 < n && mat[i+1][j][0] == 0 && !mat[i+1][j][1]) insertEdge(grafo, (j + (i*m)), (j + ((i+1)*m)), 3);
                if (i-1 >= 0 && mat[i-1][j][0] == 0 && !mat[i-1][j][1]) insertEdge(grafo, (j + (i*m)),(j + ((i-1)*m)), 4);

                mat[i][j][1] = 1;
            }
        }
        //printf("\n");
    }

    return grafo;
}


int menorCaminho (int *pais, int ini, int fim) {
    int aux;
    int i = 0;

    aux = fim;
    do {
        aux = pais[aux];
        i++;
    } while (aux != -1 && aux != ini);

    if (aux != ini) return -1;
    else return i;
}


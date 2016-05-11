/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
 ICMC/USP

 * Autor	: Guilherme Alves Campos
 * Nº USP	: 8522320

 * Disciplina : SCC0216 - Modelagem Computacional em Grafos 
 * Professor  :  Ricardo Campello
 * Descriçao  : Workaholic 
_._._._._._._._._._._._._._._._._._._._._.*/

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


double cost; //Custo fixo pago aos colegas
double hotel; //Custo da diaria

GRAPH *makeGraph (int vertex, int edges);
int *getFriends (int nFriends);
double choose (GRAPH *mapa, int *amigos, int nAmigos, int cidade, int *iMin);
void printIntVector (int *v, int n);

int main (int argc, char *argv[]) {

    int nCidades; //numero de cidades
    int nCaminhos; //Numero de caminhos
    int nAmigos; //Numero de amigos
    int *amigos = NULL; //vetor que armazena as cidades dos amigos
    int cidade; //local do serviço
    
    int mAmigo; //Pessa que atendera a chamada
    double tCusto; //Custo total do serviço
  
    int *menorCaminho = NULL; //Armazena o menor caminho em ordem inversa
    int nMenor; //Tamanho do vetor menorCaminho
  
    int op; //Operaç~ao a ser executada
   
    GRAPH *mapa = NULL;

    /*Recebendo entradas iniciais*/
    scanf("%d", &nCidades);
    scanf ("%lf %lf", &cost, &hotel);
    scanf("%d", &nCaminhos);

    /*Modelando o problema em um grafo*/
    mapa = makeGraph (nCidades, nCaminhos);

    /*Salvando amigos*/
    scanf ("%d", &nAmigos);
    amigos = getFriends (nAmigos);

    /*Recebe opç~ao*/
    scanf("%d %d", &op,  &cidade);
    
    /*seleciona a pessoa que respondera a chamada e calcula o custo total*/
    tCusto = choose(mapa, amigos, nAmigos, cidade, &mAmigo);

    /*traça o menor caminho*/
    menorCaminho = getMenorCaminho (mapa, amigos[mAmigo], cidade, &nMenor);
   
    /*Seleciona a saida*/
    switch (op) {
        
        case 1: printf("%.3lf\n", tCusto);
                break;
        case 2: printIntVector(menorCaminho, nMenor);
                printf("\n");
                break;
        case 3: if (mAmigo == -1) printf("Atende ");
                else printf("Repassa ");
                printf("%.3lf\n", tCusto);
                break;
    
        default: break;
    }

    /*Libera memoria utilizada*/
    free (menorCaminho);
    free (amigos);
    eraseGraph(mapa);

	return 0;
}

/* void printIntVector (int *v, int n) - Imprime um vetor de inteiros em ordem invertida
 * 
 * Parameters:
 *      int *v  - Vetor
 *      int n   - Numero de elementos a serem impressos a partir do zero
 * 
 * Returns:
 *      -
 */
void printIntVector (int *v, int n) {
    int i;
    for (i = n-1; i >= 0; i--) printf ("%d ", v[i]);
}

/* double choose (GRAPH *mapa, int *amigos, int nAmigos, int cidade, int *iMin) - Roda um algorismo de caminhos minimos para escolher a melhor pessoa para executar o trabalho (menor custo).
 *
 *  Parameters:
 *      GRAPH *mapa - Grafo
 *      int *amigos - Vetor com as cidades dos amigos de Joao
 *      int nAmigos - Tamanho do Vetor amigos
 *      int cidade  - Local do trabalho
 *      int *iMin   - Armazena o indice no vetor amigos daquele que realiza o trabalho com menor custo. Armazena -1 se joao possuir o menor custo
 *
 *  Returns:
 *      double - Custo referente ao amigo iMin (menor custo)
 */
double choose (GRAPH *mapa, int *amigos, int nAmigos, int cidade, int *iMin) {
    int i;
    double x; //Custo

    double min = (double) INT_MAX; //Inicia a variavel com "inf"
    double jMin; //Custo de joao


    /*Seleciona o menor custo entre os amigos*/
    for (i = 0; i < nAmigos; i++) {
        x = getMin (mapa, amigos[i], cidade);

        if (x < min) {
            min = x;
            (*iMin) = i;
        }
    }

    jMin = getMin (mapa, 1, cidade); //Encontra o custo para Joao

    /*Soma os custos extras ao custo da viagem (calcula custo total)*/
    jMin += hotel;
    min += cost;
    
    /*Seleciona o menor custo para ser retornado e o valor a ser salvo em iMenor*/
    (*iMin) = jMin <= min ? -1 : (*iMin); 
    return jMin <= min ? jMin : min;  

}

/* int *getFriends (int nFriends) - Recebe nFriends amigos e os armazena em um vetor
 *
 * Parameters:
 *      int nFriends  - Quantidade de amigos a serem recebidos do stdin
 * 
 * Returns:
 *      int * - Vetor contendo os nFriends amigos
 */
int *getFriends (int nFriends) {
    int i;
    int *friends = (int *) malloc (nFriends * sizeof(int)); 

    for (i = 0; i < nFriends; i++) {
        scanf ("%d", &friends[i]);
    }

    return friends;

}

/* GRAPH *makeGraph (int vertex, int edges) - Modela o problema em um grafo onde cada cidade 'e um vertice e cada caminho uma aresta. As arestas ser~ao recebidas por stdin.
 *
 * Parameters:
 *      int vertexs - Quantidade de cidades/ vertices
 *      int edges   - Quantidade de caminhos/arestas
 * 
 * Returns:
 *      GRAPH * - Grafo modelado 
 */
GRAPH *makeGraph (int vertex, int edges) {
    GRAPH *grafo = NULL;
    int cidade1, cidade2;
    double valor;
    int i, j;

    /*Cria um grafo vazio*/
    grafo = createGraph(); 

    /*Adiciona vertex vertices no grafo, seu valor 'e a posiç~ao em que foram adicionados*/
    //OBS: cidade 0 sera uma cidade fantasma, sem ligaçao com as demais
    for (i = 0; i < vertex + 1; i++) {
        insertVertex(grafo, i);    
    }

    /*Recebe do stdin edges caminhos/arestas e as adiciona no grafo*/
    for (i = 0; i < edges; i++) {
        scanf ("%d %d %lf", &cidade1, &cidade2, &valor);
        insertEdge (grafo, cidade1, cidade2, valor);
    }

    return grafo;
}

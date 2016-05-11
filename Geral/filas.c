#include "filas.h"

struct no {
    int elemento;
    NO *proximo;
    NO *anterior;
};

struct fila {
    NO *inicio;
    NO *fim;
    int n_nos;
};

FILA * createFila () {
    FILA *fila = NULL;
    fila = (FILA *) malloc(sizeof(FILA));

    if (fila) {
        fila->n_nos = 0;
        fila->inicio = NULL;
        fila->fim = NULL;
    }

    return fila;
}

void addNo (int n, FILA *fila) {
    NO *no = NULL;
    no = (NO *) malloc (sizeof(NO));

    if (no) {
        no->elemento = n;
        no->proximo = NULL;

        if (!fila->n_nos) {
            no->anterior = NULL;
            fila->inicio = no;

        } else {
            no->anterior = fila->fim;
        }

        fila->fim = no;
        fila->n_nos++;
    }
}

int rmNo(FILA *fila) {
   int n;
   NO *aux;
   if (fila) {
        n = fila->inicio->elemento;
        aux = fila->inicio;
        fila->inicio = aux->proximo;
        if (fila->inicio) fila->inicio->anterior = NULL;

        free(aux);
        aux = NULL;
   }
    fila->n_nos--;
    return n;
}

int vazia(FILA *fila) {
    return fila->n_nos ? 0 : 1;
}

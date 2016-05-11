#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct fila FILA;
typedef struct no NO;

FILA * createFila ();
void addNo (int n, FILA *fila);
int rmNo(FILA *fila);
int vazia(FILA *fila);

#endif // FILA_H_INCLUDED

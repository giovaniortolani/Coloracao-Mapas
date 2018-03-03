/*
 *  GRUPO 8
 */

#ifndef BUSCA_H
#define BUSCA_H

#include "tad.h"

int CheckColor(vertice *);
int CheckEnd(grafo *);
vertice* GetFirstUncolored(grafo *);
int ForwardCheck(grafo *);
vertice* GetMVR(grafo *);
vertice* GetMVR_Grau(grafo *); 
int b1(grafo *, vertice *, int *); 
int b2(grafo *, vertice *, int *); 
int b3(grafo *, vertice *, int *); 
int b4(grafo *, vertice *, int *); 
void backtracking(grafo *, char); 

#endif
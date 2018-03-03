/*
 *  GRUPO 8
 */

#ifndef TAD_H
#define TAD_H

typedef struct no
{
    char *nome;         //Vertice final da aresta
    int posicao;        //Posicao da regiao no vetor de struct
    struct no *prox;    //Ponteiro pro próximo vertice
}NO;

typedef struct{
    char *nome;
    int num;
    NO* adj;
}LISTA;

typedef struct grafo {											//struct de um grafo
	struct vertice **vlist;
	int grau;
	int garestas;
}grafo;

typedef struct vertice {										//struct de um vertice
	struct vertice **adj;
	int arestas;
	int info;
	int cor;
}vertice;

char* LerProximaLinha(void);
NO* CriaNo(NO *, const char *);
void IndexarPosicao(LISTA *, int);
void Adicionar(LISTA *, int, char *);
void InsereLista(LISTA *, int);
grafo* CriaGrafo (void);											//prototipos das funcoes
void DestroiGrafo (grafo *);
void AddVertice (grafo *, int);
vertice *BuscaVertice (grafo *, int);
void AddAresta (grafo *, int, int);
void PrintGrafo(grafo *, LISTA*); 

#endif
/*
 *	GRUPO 8
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"
#include "busca.h"

int main(int argc, char **argv) 
{
	int  i;
	int nRegioes;
	char heuristica;

	NO* aux;
	LISTA *vetorLISTA;
	grafo *g;

    printf("Entrar na pasta ENTRADAS e copiar e colar no programa.\n");
    printf("Na primeira linha de cada entrada, alterar o segundo valor\n");
    printf("para \"a, b, c, d\", que são as heurísticas.\n");
    
	scanf("%d %c", &nRegioes, &heuristica);
	getchar();

	vetorLISTA = (LISTA*) malloc(sizeof(LISTA)*nRegioes);
	InsereLista(vetorLISTA, nRegioes);	// le a entrada e cria a representacao em lista de adjacencia

    g = CriaGrafo();
	for (i = 0; i < nRegioes; i++) 
    {
		AddVertice(g, i);
	}
	for (i = 0; i < nRegioes; i++)
	{
		aux = vetorLISTA[i].adj;
		while(aux != NULL)
		{	
			AddAresta(g, i, aux->posicao);
			aux = aux->prox;
		}
	}

	backtracking(g, heuristica);

	PrintGrafo(g, vetorLISTA);
	
	DestroiGrafo(g);

	return 0;
}

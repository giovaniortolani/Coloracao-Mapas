/*
 *  GRUPO 8
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"

char* LerProximaLinha(void)
{
    char *buffer = NULL;
    char character;
    int counter = 0;

    do
    {
        character = fgetc(stdin);
        buffer = (char *) realloc(buffer, sizeof(char) * (counter + 1));
        buffer[counter++] = character;
    }while(character != '.');

    getchar();  // Pega o '\n' inserido apos uma linha ser digitada.

    buffer[counter - 1] = '\0'; // Tira o ponto final e substitui por um '\0'.

    return buffer;
}

NO* CriaNo(NO *prox, const char *vert2)
{
    NO *no = (NO *) malloc(sizeof(NO)); //Aloco um novo ponteiro auxiliar

    no->nome = (char *) malloc(sizeof(char) * strlen(vert2));
    strcpy(no->nome, vert2);
    no->posicao = -1;
    no->prox = prox;

    return no;
}

void IndexarPosicao(LISTA *lista, int n_vertices)
{
    int i, j;
    NO *P;

    //Para cada vértice no vetor de structs...
    for(i = 0; i < n_vertices; i++)
    {
        P = lista[i].adj;
        while(P != NULL)
        {
            j = 0;
            //...procurando a posiçao do nome do nó no vetor de strucs
            while(strcmp(lista[j].nome, P->nome) != 0)
                j++;
            P->posicao = j;
            P = P->prox;
        }
    }
}

void Adicionar(LISTA *lista, int vert1, char *vert2)
{
    NO *p;
    NO *paux = lista[vert1].adj;
    p = CriaNo(paux, vert2);
    lista[vert1].adj = p;
}

void InsereLista(LISTA *lista, int nRegioes)
{
    int i;
    char *stringLinha = NULL, *token = NULL, *aux = NULL;

    for (i = 0; i < nRegioes; i++)
    {
        stringLinha = LerProximaLinha();
        token = strtok(stringLinha, ":");   //O strtok le ate' o caracter e coloca um '\0' nele.

        //Arrumo o nome da regiao
        lista[i].nome = (char *) malloc(sizeof(char) * ((int) strlen(token) + 1));   // Soma 1 ao tamanho pois a funcao nao conta o '\0'.
        strcpy(lista[i].nome, token);

        //Insiro os vizinhos e construo o grafo
        while((token = strtok(NULL, ",")) != NULL)
        {
            token++;    // Necessario para que o ' ' espaço anterior a palavra não entre na String. (Ex.: "_Amazonas")
            aux = (char *) malloc(sizeof(char) * ((int) strlen(token) + 1));
            strcpy(aux, token);
            Adicionar(lista, i, aux);
        }
    }
    IndexarPosicao(lista, nRegioes);
}

grafo* CriaGrafo(void)	//funcao que cria e inicializa um grafo 
{
	grafo *g;

	g = (grafo *) malloc(sizeof(grafo));
	g->grau = 0;
	g->garestas = 0;
	g->vlist = NULL;

	return g;
}

void DestroiGrafo(grafo *g) //funcao que libera um grafo da memoria
{
	int i;

	for (i=0; i<g->grau; i++) 
	{
		free(g->vlist[i]->adj);
		free(g->vlist[i]);
	}
	free(g->vlist);
	free(g);
}

void AddVertice(grafo *g, int val)	//funcao que insere um vertice no grafo, com sua informacao recebida como argumento
{
	int i, j;

	if (g->grau > 0)
	{
		for (i = 0; i < g->grau; i++) 
		{
			if (g->vlist[i]->info == val)	// se ja existe, nao faz nada
				return;
		}
		g->vlist = (vertice **) realloc(g->vlist, ((g->grau)+1) * sizeof(vertice*));	//aumenta um espaco no vetor de ponteiros pra vertice
		for (i = 0; i < g->grau; i++) 
		{
			if (g->vlist[i]->info > val) 
			{
				for (j = g->grau; j > i; j--) {		//abre espaco na posicao i para inserir um novo vertice (insercao ordenada), deslocando elementos para frente
					g->vlist[j] = g->vlist[j-1];
				}
				break;
			}
		}
	}
	else 
	{
		g->vlist = (vertice **) realloc(g->vlist, ((g->grau)+1) * sizeof(vertice*));
		i = 0;
	}

	g->vlist[i] = (vertice *) malloc(sizeof (vertice));		//aloca a memoria para o vertice e em seguida inicializa seus dados
	g->vlist[i]->info = val;
	g->vlist[i]->cor = -1;
	g->vlist[i]->adj = NULL;
	g->vlist[i]->arestas = 0;
	g->grau++;
}

vertice *BuscaVertice(grafo *g, int val)	//funcao que retorna o ponteiro para um vertice, recebe a chave de busca como argumento 
{			
	int i;
	for (i=0; i<g->grau; i++) {
		if (g->vlist[i]->info == val)
			return g->vlist[i];
	}
	return NULL;
}

void AddAresta(grafo *g, int val, int lig)	//adiciona uma aresta, recebendo como parametro o vertice de partida e o vertice de chegada
{		
	int i, j;
	vertice *aux = NULL;

	aux = BuscaVertice(g, val);
	if(aux == NULL)
		return;
	if(aux->arestas > 0) 
	{
		for (i = 0; i < aux->arestas; i++) 	//caso aresta ja existe
		{	
			if (aux->adj[i]->info == lig)	//nao adiciona ela
				return;						//e interrompe a rotina
		}
	}
	aux->adj = (vertice **) realloc(aux->adj, (aux->arestas+1) * sizeof(vertice *));	//aumenta uma posicao no vetor de ponteiros para vertice (adjacentes do vertice)
	if (aux->arestas > 0) 
	{
		for (i = 0; i < aux->arestas; i++) 
		{
			if (aux->adj[i]->info > lig) 
			{
				for (j = aux->arestas; j > i; j--)	//abre espaco na posicao i para inserir uma nova aresta (insercao ordenada), deslocando elementos para frente
				{		
					aux->adj[j] = aux->adj[j-1];
				}
				break;
			}
		}
	}
	else
		i = 0;

	aux->arestas++;
	aux->adj[i] = BuscaVertice(g, lig);	//define o vertice adjacente para um determinado vertice
	g->garestas++;
}

void PrintGrafo(grafo *g, LISTA* vetorLista) 
{
	int i;

	printf("\n");
	for (i = 0; i < g->grau; i++) 
	{
		if(g->vlist[i]->cor == 0)
		{
			printf ("%s:  Vermelho\n", vetorLista[g->vlist[i]->info].nome);
		}
		else if(g->vlist[i]->cor == 1)
		{
			printf ("%s:  Verde\n", vetorLista[g->vlist[i]->info].nome);
		}
		else if(g->vlist[i]->cor == 2)
		{
			printf ("%s:  Amarelo\n", vetorLista[g->vlist[i]->info].nome);
		}
		else if(g->vlist[i]->cor == 3)
		{
			printf ("%s:  Azul\n", vetorLista[g->vlist[i]->info].nome);
		}
	}
	printf ("\n");
}
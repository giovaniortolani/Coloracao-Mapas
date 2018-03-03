/*
 *  GRUPO 8
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tad.h"
#include "busca.h"

//verifica se a cor do vertice recebido como argumento e' valida
//retorna 1 caso for valida, retorna 0 caso for adjacente com a mesma cor
int CheckColor(vertice *v) 
{
    int i;

    for(i = 0; i < v->arestas; i++) 
    {
        if(v->adj[i]->cor == v->cor) 
        {
            return 0;
        }
    }
    return 1;
}

//verifica se a coloracao do grafo chegou ao fim
//retorna 0 caso existam vertices sem cor, retorna 1 caso contrario
int CheckEnd(grafo *g) 
{
    int i;
 
    for(i = 0; i < g->grau; i++) 
    {
        if(g->vlist[i]->cor == -1) 
        {
            return 0;
        }
    }
    return 1;
}

//retorna o primeiro vertice nao colorido do grafo, de forma ordenada
//retorna NULL caso nao existam vertices sem cor
vertice* GetFirstUncolored(grafo *g) 
{
    int i;

    for(i = 0; i < g->grau; i++) 
    {
        if(g->vlist[i]->cor == -1) 
        {
            return g->vlist[i];
        }
    }
    return NULL;
}

//faz o forward checking - caso algum vertice esteja sem opcoes, ou seja, impossibilitado
//de ser atribuido com uma das 4 cores, retorna 0, caso contrario retorna 1
int ForwardCheck(grafo *g) 
{
    int i, j, opts, color;

    for(i = 0; i < g->grau; i++) 
    {
        opts = 4;
        for(color = 0; color < 4; color++) 
        {
            for(j = 0; j < g->vlist[i]->arestas; j++) 
            {
                if(g->vlist[i]->adj[j]->cor == color) 
                {
                    opts--;
                    break;
                }
            }
        }
        if(opts == 0) 
        {
            return 0;
        }
    }
    return 1;
}

//funcao de obter o proximo vertice baseado nos minimos valores remanescentes (MVR)
vertice* GetMVR(grafo *g) 
{
    int i, j, opts, color, minopts = 4;
    vertice *v = NULL;

    for(i = 0; i < g->grau; i++) 
    {
        opts = 4;
        for(color = 0; color < 4; color++) 
        {
            for(j = 0; j < g->vlist[i]->arestas; j++) 
            {
                if(g->vlist[i]->adj[j]->cor == color) 
                {
                    opts--;
                    break;
                }
            }
        }
        if(opts < minopts && g->vlist[i]->cor == -1) 
        {
            minopts = opts;
            v = g->vlist[i];
        }
    }
    return v;
}

//funcao de obter o proximo vertice baseado nos minimos valores remanescentes (MVR), porem
//usando para vertices com mesmo MVR usa o criterio do grau para desempate
vertice* GetMVR_Grau(grafo *g) 
{
    int i, j, opts, color, minopts = 4, prevgrau = 0;
    vertice *v = NULL;

    for(i = 0; i < g->grau; i++) 
    {
        opts = 4;
        for(color = 0; color < 4; color++)
        {
            for(j = 0; j < g->vlist[i]->arestas; j++) 
            {
                if (g->vlist[i]->adj[j]->cor == color) 
                {
                    opts--;
                    break;
                }
            }
        }
        if(opts <= minopts && g->vlist[i]->cor == -1) 
        {
            if(g->vlist[i]->arestas > prevgrau)
            {
                prevgrau = g->vlist[i]->arestas;
                minopts = opts;
                v = g->vlist[i];
            }
        }
    }
    return v;
}

//funcao de backtracking recursivo - sem heuristicas (Busca Cega)
int b1(grafo *g, vertice *current_v, int *count) 
{
    int color, result;

    if(CheckEnd(g) == 1) 
    {
        return 1;
    }
    for(color = 0; color < 4; color++) 
    {
        current_v->cor = color;
        if(CheckColor(current_v) == 1) 
        {
            (*count)++;
            result = b1(g, GetFirstUncolored(g), count);
            if(result == 1) 
            {
                return result;
            }
        }
    }
    current_v->cor = -1;    // caso nao consiga atribuir nenhuma cor

    return 0;
}

//funcao de backtracking recursivo - com forward checking (Busca Informada)
int b2(grafo *g, vertice *current_v, int *count)
{
    int color, result;

    if(CheckEnd(g) == 1) 
    {
        return 1;
    }
    for(color = 0; color < 4; color++) 
    {
        current_v->cor = color;
        if(CheckColor(current_v) == 1) 
        {
            (*count)++;
            if(ForwardCheck(g) == 1) 
            {
                result = b2(g, GetFirstUncolored(g), count);
                if(result == 1) 
                {
                    return result;
                }
            }
        }
    }
    current_v->cor = -1;    // caso nao consiga atribuir nenhuma cor

    return 0;
}

//funcao de backtracking recursivo - com forward checking e MVR (Busca Informada)
int b3(grafo *g, vertice *current_v, int *count) 
{
    int color, result;

    if(CheckEnd(g) == 1) 
    {
        return 1;
    }
    for(color = 0; color < 4; color++) 
    {
        current_v->cor = color;
        if(CheckColor(current_v) == 1) 
        {
            (*count)++;
            if(ForwardCheck(g) == 1) 
            {
                result = b3(g, GetMVR(g), count);
                if(result == 1) 
                {
                    return result;
                }
            }
        }
    }
    current_v->cor = -1;    // caso nao consiga atribuir nenhuma cor

    return 0;
}

//funcao de backtracking recursivo - com forward checking, MVR e grau (Busca Informada)
int b4(grafo *g, vertice *current_v, int *count) 
{
    int color, result;

    if(CheckEnd(g) == 1) 
    {
        return 1;
    }
    for(color = 0; color < 4; color++) 
    {
        current_v->cor = color;
        if(CheckColor(current_v) == 1) 
        {
            (*count)++;
            if(ForwardCheck(g) == 1) {
                result = b4(g, GetMVR_Grau(g), count);
                if(result == 1) 
                {
                    return result;
                }
            }
        }
    }
    current_v->cor = -1;    // caso nao consiga atribuir nenhuma cores

    return 0;
}

//funcao principal do backtracking, escolhe heuristica e exibe o numero de operacoes
void backtracking(grafo *g, char heuristica) 
{
    int count = 0, result = 0;
    
    clock_t c0 = 0, c1 = 0;
    double runtime_diff_ms = 0;
    
    if (g != NULL) 
    {
        if (heuristica == 'a') 
        {
            c0 = clock();
            result = b1(g, g->vlist[0], &count);
            c1 = clock();
        }
        else if (heuristica == 'b') 
        {
            c0 = clock();
            result = b2(g, g->vlist[0], &count);
            c1 = clock();
        }
        else if (heuristica == 'c') 
        {
            c0 = clock();
            result = b3(g, g->vlist[0], &count);
            c1 = clock();
        }
        else if (heuristica == 'd') 
        {
            c0 = clock();
            result = b4(g, g->vlist[0], &count);
            c1 = clock();
        }
        if (result == 1) 
        {
            runtime_diff_ms = (c1 - c0) * 1000. / CLOCKS_PER_SEC;
            printf("\n\t\t\tUso da heurística: %c", heuristica);
            printf("\nMapa colorido com sucesso em %d atribuicoes de cor e em %f ms.\n", count, runtime_diff_ms);
        }
        else 
        {
            printf("Falha ao colorir o mapa!\n");
        }
    }
}
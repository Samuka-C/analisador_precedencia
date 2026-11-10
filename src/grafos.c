#include <grafos.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief retorna verdadeiro se o indice do vertice pertence ao grafo
 */
int eh_vertice(grafo* grafo, int vertice)
{
    if (grafo == NULL)
        return 0;

    return grafo->numero_vertices > vertice && vertice >= 0;
}

grafo* criar_grafo(int numero_vertices)
{
    grafo* novo_grafo = (grafo*)malloc(sizeof(grafo));

    if (novo_grafo == NULL)
        return NULL;

    novo_grafo->numero_vertices = numero_vertices;
    novo_grafo->matriz = (int**)calloc(numero_vertices, sizeof(int*));
    novo_grafo->nomes = (char**)calloc(numero_vertices, sizeof(char*));

    if (novo_grafo->matriz == NULL || novo_grafo->nomes == NULL)
    {
        destruir_grafo(novo_grafo);
        return NULL;
    }

    for (int i = 0; i < numero_vertices; i++)
    {
        novo_grafo->matriz[i] = (int*)malloc(numero_vertices * sizeof(int));

        if (novo_grafo->matriz[i] == NULL)
        {
            destruir_grafo(novo_grafo);
            return NULL;
        }

        for (int j = 0; j < numero_vertices; j++)
        {
            novo_grafo->matriz[i][j] = 0;
        }

        novo_grafo->nomes[i] = (char*)malloc(MAX_VERTICE_NOME_TAMANHO * sizeof(char));

        if (novo_grafo->nomes[i] == NULL)
        {
            destruir_grafo(novo_grafo);
            return NULL;
        }

        strcpy(novo_grafo->nomes[i], "sem nome");
    }

    return novo_grafo;
}

void destruir_grafo(grafo* grafo)
{
    if (grafo == NULL)
        return;

    if (grafo->matriz != NULL)
    {
        for (int i = 0; i < grafo->numero_vertices; i++)
        {
            free(grafo->matriz[i]);
        }
        free(grafo->matriz);
    }

    if (grafo->nomes != NULL)
    {
        for (int i = 0; i < grafo->numero_vertices; i++)
        {
            free(grafo->nomes[i]);
        }
        free(grafo->nomes);
    }

    free(grafo);
}

void nomear_vertice(grafo* grafo, int vertice, const char* nome)
{
    if (grafo == NULL)
        return;

    if (!eh_vertice(grafo, vertice))
        return;

    if (strlen(nome) > MAX_VERTICE_NOME_TAMANHO)
        return;

    strcpy(grafo->nomes[vertice], nome);
}

void conectar_vertice(grafo* grafo, int vertice_origem, int vertice_fim)
{
    if (grafo == NULL)
        return;

    if (!eh_vertice(grafo, vertice_origem) || !eh_vertice(grafo, vertice_fim))
        return;
    
    grafo->matriz[vertice_origem][vertice_fim] = 1;
}

void desconectar_vertice(grafo* grafo, int vertice_origem, int vertice_fim)
{
    if (grafo == NULL)
        return;

    if (!eh_vertice(grafo, vertice_origem) || !eh_vertice(grafo, vertice_fim))
        return;
    
    grafo->matriz[vertice_origem][vertice_fim] = 0;
}

void printar_grafo(grafo* grafo)
{
    for (int i = 0; i < grafo->numero_vertices; i++)
    {
        for (int j = 0; j < grafo->numero_vertices; j++)
        {
            if (grafo->matriz[i][j])
            {
                printf("%s -> %s\n", grafo->nomes[i], grafo->nomes[j]);
            }
        }
    }
}

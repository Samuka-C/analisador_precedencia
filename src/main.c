#include <logger.h>
#include <grafos.h>
#include <leitor_grafo.h>
#include <algoritimos_grafos.h>

#include <stdio.h>

int main()
{
    grafo* grafo = ler_grafo("grafo_0");

    // printf("grafo:\n");
    // printar_grafo(grafo);
    // printf("---\n");

    int ciclo = detectar_ciclo(grafo);

    if (ciclo)
        printf("CICLO: existe\n");
    else
        printf("CICLO: nao existe\n");

    /*
    int vertices_ordenados[grafo->numero_vertices];
    obter_ordem_topologica(grafo, vertices_ordenados);

    printf("ORDEM: ");

    for (int i = 0; i < grafo->numero_vertices; i++)
    {
        if (i != 0)
            printf(", ");

        int vertice = vertices_ordenados[i];
        printf("%s", grafo->nomes[vertice]);
    }

    printf("\n");
    */

    int vertices_ordenados[grafo->numero_vertices][4];
    obter_matriz_topologica(grafo, 4, vertices_ordenados);

    for (int i = 0; i < grafo->numero_vertices; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int vertice = vertices_ordenados[i][j];
            if (vertice == -1)
                break;

            if (j != 0)
                printf(", ");

            printf("%s", grafo->nomes[vertice]);
        }

        puts("\n");
    }

    return 0;
}
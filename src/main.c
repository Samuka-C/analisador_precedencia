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

    int vertices_ordenados[grafo->numero_vertices];
    obter_ordenacao(grafo, vertices_ordenados);

    printf("ORDEM: ");

    for (int i = 0; i < grafo->numero_vertices; i++)
    {
        if (i != 0)
            printf(", ");

        int vertice = vertices_ordenados[i];
        printf("%s", grafo->nomes[vertice]);
    }

    printf("\n");

    return 0;
}
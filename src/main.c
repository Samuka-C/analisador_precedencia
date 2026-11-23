#include <logger.h>
#include <grafos.h>
#include <leitor_grafo.h>
#include <algoritimos_grafos.h>

#include <stdio.h>

#define NUMERO_PROCESSADORES_TESTE 4

void escrever_ordem_topologica(grafo* grafo, int ordem_topologica[])
{
    for (int index = 0; index < grafo->numero_vertices; index++)
    {
        printf("%d | %s\n", index, grafo->nomes[ordem_topologica[index]]);
    }
}

void escrever_matriz_topologica(grafo* grafo, int numero_colunas, int matriz_topologica[][numero_colunas])
{
    for (int linha = 0; linha < grafo->numero_vertices; linha++)
    {
        if (matriz_topologica[linha][0] == -1)
            return;

        printf("%d | ", linha);

        for (int coluna = 0; coluna < numero_colunas; coluna++)
        {
            int vertice = matriz_topologica[linha][coluna];

            if (vertice == -1)
                break;

            if (coluna != 0)
                printf(", ");

            printf("%s", grafo->nomes[vertice]);
        }

        printf("\n");
    }
}

void analisar_grafo(grafo* grafo)
{
    int ciclo = detectar_ciclo(grafo);

    printf("grafo de tarefas:\n");
    printar_grafo(grafo);

    printf("\n");

    if (ciclo)
    {
        printf("CICLO: existe\n");
        printf("não é possivel encontrar uma ordem topologica\n");
        return;
    }

    printf("CICLO: nao existe\n\n");

    int vertices_ordenados[grafo->numero_vertices];
    int vertices_ordenados_matriz[grafo->numero_vertices][NUMERO_PROCESSADORES_TESTE];

    obter_ordem_topologica(grafo, vertices_ordenados);
    obter_matriz_topologica(grafo, NUMERO_PROCESSADORES_TESTE, vertices_ordenados_matriz);

    printf("ordem topologica:\n");
    escrever_ordem_topologica(grafo, vertices_ordenados);

    printf("\n");

    printf("ordem de processamento para tempo minimo com %d processadores:\n", NUMERO_PROCESSADORES_TESTE);
    escrever_matriz_topologica(grafo, NUMERO_PROCESSADORES_TESTE, vertices_ordenados_matriz);
}

int main()
{
    grafo* grafo = ler_grafo("grafo_0");

    analisar_grafo(grafo);

    return 0;
}
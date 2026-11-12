#include <algoritimos_grafos.h>

#include <logger.h>
#include <stdlib.h>
#include <encadeado.h>

enum estado_vertice {
    nao_visitado, // vertice não visitado
    visitado, // visitado, mas nem todos seus filhos foram concluidos
    concluido // não tem filhos ou todos eles foram concluidos
};

/**
 * @brief faz busca em profundidade a partir de um vertice
 * 
 * @param grafo grafo para fazer a busca
 * @param estado vetor de estados de cada vertice
 * @param vertice vertice para fazer a busca
 * 
 * @return 1 se houver um ciclo, 0 caso contrário
 */
int busca_profundidade_encontrar_ciclo(grafo* grafo, enum estado_vertice* estado, int vertice)
{
    estado[vertice] = visitado;

    for (int vertice_filho = 0; vertice_filho < grafo->numero_vertices; vertice_filho++)
    {
        if (!grafo->matriz[vertice][vertice_filho])
            continue;

        if (estado[vertice_filho] == concluido)
            continue;

        if (estado[vertice_filho] == visitado)
            return 1;

        if (busca_profundidade_encontrar_ciclo(grafo, estado, vertice_filho))
            return 1;
    }

    estado[vertice] = concluido;

    return 0;
}

int detectar_ciclo(grafo* grafo)
{
    enum estado_vertice estado[grafo->numero_vertices];

    for (int vertice = 0; vertice < grafo->numero_vertices; vertice++)
        estado[vertice] = nao_visitado;

    for (int vertice = 0; vertice < grafo->numero_vertices; vertice++)
    {
        if (estado[vertice] != nao_visitado)
            continue;

        if (busca_profundidade_encontrar_ciclo(grafo, estado, vertice))
            return 1;
    }

    return 0;
}

/**
 * @brief obtem um vertice de grau zero não visitado. marca ele como concluido e diminui o grau dos seus filhos
 * 
 * @param grafo grafo a qual os vertices pertecem
 * @param estado vetor de estado dos vertices
 * @param grau_entrada vetor de grau de entrada dos vertices
 * @param vertice_saida ponteiro para escrever o valor do vertice de saida
 * 
 * @return 1 se pode obter um vertice, 0 caso contrário
 */
int obter_vertice_grau_zero(grafo* grafo, enum estado_vertice* estado, int* grau_entrada, int* vertice_saida)
{
    int encontrou_vertice = 0;

    for (int vertice = 0; vertice < grafo->numero_vertices; vertice++)
    {
        if (estado[vertice] != nao_visitado)
            continue;

        if (grau_entrada[vertice] != 0)
            continue;
        
        for (int vertice_filho = 0; vertice_filho < grafo->numero_vertices; vertice_filho++)
        {
            if (!grafo->matriz[vertice][vertice_filho])
                continue;
            
            grau_entrada[vertice_filho]--;
        }

        estado[vertice] = concluido;

        *vertice_saida = vertice;

        return 1;
    }

    return 0;
}

void obter_ordenacao(grafo* grafo, int* array_vertices)
{
    // criar vetor de estado para os vertices e marcar todos como não visitados
    enum estado_vertice estado[grafo->numero_vertices];
    int grau_entrada[grafo->numero_vertices];

    for (int vertice = 0; vertice < grafo->numero_vertices; vertice++)
    {
        estado[vertice] = nao_visitado;
        grau_entrada[vertice] = 0;
    }

    // obter o grau de entrada de todos os vertices
    for (int vertice = 0; vertice < grafo->numero_vertices; vertice++)
    {
        for (int vertice_filho = 0; vertice_filho < grafo->numero_vertices; vertice_filho++)
        {
            if (!grafo->matriz[vertice][vertice_filho])
                continue;

            grau_entrada[vertice_filho]++;
        }
    }

    int index_array = 0;
    int vertice;

    while (obter_vertice_grau_zero(grafo, estado, grau_entrada, &vertice))
    {
        array_vertices[index_array] = vertice;
        index_array++;
    }
}

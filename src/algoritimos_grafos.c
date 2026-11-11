#include <algoritimos_grafos.h>

enum estado_vertice {
    nao_visitado, // vertice não visitado
    visitado, // visitado, mas nem todos seus filhos foram concluidos
    concluido // não tem filhos ou todos eles foram concluidos
};

/**
 * @brief faz busca em profundidade a partir de um vertice
 * atribuindo valores ao vetor pre indicando a ordem de visita de cada vertice
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
        if (estado[vertice] == nao_visitado)
        {
            if (busca_profundidade_encontrar_ciclo(grafo, estado, vertice))
                return 1;
        }
    }

    return 0;
}
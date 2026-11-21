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
 * @brief procura por vertices com grau zero não concluidos, e os escreve em um buffer.
 * 
 * @return 1 caso foi possivel encontrar vertices com grau zero não concluidos, 0 caso contrário.
 */
int procurar_vertices_grau_zero(grafo* grafo, enum estado_vertice* estado, int* grau_entrada, int* buffer_vertices, int* tamanho_buffer)
{
    int encontrou_vertice = 0;

    for (int vertice = 0; vertice < grafo->numero_vertices; vertice++)
    {
        if (estado[vertice] == concluido)
            continue;

        if (grau_entrada[vertice] != 0)
            continue;

        buffer_vertices[*tamanho_buffer] = vertice;
        (*tamanho_buffer)++;

        encontrou_vertice = 1;
    }

    return encontrou_vertice;
}

void obter_ordem_topologica(grafo* grafo, int array_vertices[])
{
    if (array_vertices == NULL)
    {
        log_error("ponteiro array_vertices é nulo!");
        return;
    }

    int matriz_intermediaria[grafo->numero_vertices][1];

    obter_matriz_topologica(grafo, 1, matriz_intermediaria);

    for (int index = 0; index < grafo->numero_vertices; index++)
        array_vertices[index] = matriz_intermediaria[index][0];
}

void obter_matriz_topologica(grafo* grafo, int numero_colunas, int matriz_saida[][numero_colunas])
{
    // verificar se os inputs estão okay
    if (numero_colunas < 1)
    {
        log_warning("impossivel aplicar a função com numero de colunas: %d menor do que 1", numero_colunas);
        return;
    }

    if (matriz_saida == NULL)
    {
        log_error("ponteiro matriz_saida é nulo!");
        return;
    }

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

    int index_linha = 0;
    int index_coluna = 0;

    // setar toda a matriz como -1
    for (; index_linha < grafo->numero_vertices; index_linha++)
    {
        for (; index_coluna < numero_colunas; index_coluna++)
        {
            matriz_saida[index_linha][index_coluna] = -1;
        }
    }

    index_linha = 0;
    index_coluna = 0;

    int buffer_vertices[grafo->numero_vertices];
    int tamanho_buffer = 0;

    while (procurar_vertices_grau_zero(grafo, estado, grau_entrada, buffer_vertices, &tamanho_buffer))
    {
        while (tamanho_buffer > 0)
        {
            // obter vertice para colocar na matriz
            int vertice = buffer_vertices[tamanho_buffer - 1];
            matriz_saida[index_linha][index_coluna] = vertice;

            // reduzir grau de entrada dos vertices filhos
            for (int vertice_filho = 0; vertice_filho < grafo->numero_vertices; vertice_filho++)
            {
                if (!grafo->matriz[vertice][vertice_filho])
                    continue;

                grau_entrada[vertice_filho]--;
            }

            // vertice finalizado
            estado[vertice] = concluido;
            tamanho_buffer--;

            // mover local de escrita na matriz
            index_coluna++;
            if (index_coluna >= numero_colunas)
            {
                index_coluna = 0;
                index_linha++;
            }
        }

        // garantir que os proximos vertices do buffer não sejam escritos em uma linha com outros vertices
        if (index_coluna > 0)
        {
            index_coluna = 0;
            index_linha++;
        }
    }
}

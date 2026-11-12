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
 * @brief faz busca em largura a partir de um vertice
 * 
 * @param grafo grafo para fazer a busca
 * @param estado vetor de estados de cada vertice
 * @param vertice vertice para fazer a busca
 * @param pilha_vertices pilha de vertices para inserir os proximos vertices a fazer busca em largura
 */
void busca_largura_obter_ordem(grafo* grafo, enum estado_vertice* estado, int vertice, pilha* pilha_vertices)
{
    estado[vertice] = visitado;

    for (int vertice_filho = 0; vertice_filho < grafo->numero_vertices; vertice_filho++)
    {
        if (!grafo->matriz[vertice][vertice_filho])
            continue;

        if (estado[vertice_filho] != nao_visitado)
            continue;

        int pai_nao_visitado = 0;

        for (int vertice_pai = 0; vertice_pai < grafo->numero_vertices; vertice_pai++)
        {
            if (!grafo->matriz[vertice_pai][vertice_filho])
                continue;

            if (estado[vertice_pai] == nao_visitado)
            {
                pai_nao_visitado = 1;
                break;
            }
        }

        if (pai_nao_visitado)
            continue;

        if (!pilha_push(pilha_vertices, vertice_filho))
        {
            log_error("falhou em adicionar item na pilha");
            return;
        }
    }
}

void obter_ordenacao(grafo* grafo, int* array_vertices)
{
    // criar vetor de estado para os vertices e marcar todos como não visitados
    enum estado_vertice estado[grafo->numero_vertices];

    for (int vertice = 0; vertice < grafo->numero_vertices; vertice++)
        estado[vertice] = nao_visitado;

    // criar fila de vertices ordenados que vai ser usado para povoar o array
    fila* vertices_ordenados = criar_fila();
    if (vertices_ordenados == NULL)
    {
        log_error("falhou em criar fila!");
        return;
    }

    for (int vertice = 0; vertice < grafo->numero_vertices; vertice++)
    {
        if (estado[vertice] != nao_visitado)
            continue;

        // para cada vertice não visitado, fazer busca em largura

        fila* vertices_ordenados_parcial = criar_fila();
        if (vertices_ordenados_parcial == NULL)
        {
            log_error("falhou em criar fila!");
            return;
        }
        
        pilha* pilha_vertices_para_fazer_busca = criar_pilha();
        if (pilha_vertices_para_fazer_busca == NULL)
        {
            log_error("falhou em criar pilha!");
            return;
        }

        if (!pilha_push(pilha_vertices_para_fazer_busca, vertice))
        {
            log_error("falhou em adicionar item na pilha");
            return;
        }

        while (pilha_vertices_para_fazer_busca->numero_items > 0)
        {
            int vertice_para_buscar = pilha_pop(pilha_vertices_para_fazer_busca);
            if (!fila_push_frente(vertices_ordenados_parcial, vertice_para_buscar))
            {
                log_error("falha em adicionar item na fila");
                return;
            }
            busca_largura_obter_ordem(grafo, estado, vertice_para_buscar, pilha_vertices_para_fazer_busca);
        }

        destruir_pilha(pilha_vertices_para_fazer_busca);

        // a busca em largura vai preencher a fila parcial até as folhas ou até os vertices explorados
        // em uma busca em largura anterior, portanto a fila parcial necessariament vem antes das filas obtidas anteriormente
        vertices_ordenados = fila_fundir(vertices_ordenados_parcial, vertices_ordenados);
        if (vertices_ordenados == NULL)
        {
            log_error("falhou em criar fila!");
            return;
        }
    }

    // todos os vertices foram explorados e portanto vertices_ordenados tem uma ordem correta dos vertices

    for (int indice = 0; indice < grafo->numero_vertices; indice++)
    {
        int vertice = fila_get(vertices_ordenados);
        array_vertices[indice] = vertice;
    }
}

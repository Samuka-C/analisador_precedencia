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
int busca_profundidade_encontrar_ciclo(grafo* grafo, enum estado_vertice estado[], int vertice)
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
int procurar_vertices_grau_zero(grafo* grafo, enum estado_vertice estado[], int grau_entrada[], int buffer_vertices[], int* tamanho_buffer)
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

/**
 * @brief ordena o buffer de vertices baseado no grau de saida do menor para o maior
 */
void ordenar_buffer(int buffer_vertices[], int tamanho_buffer, int grau_saida[], int maximo_grau_entrada)
{
    // ordenação por contagem O(n)

    int intermediario[maximo_grau_entrada + 1];
    int saida_temporaria[tamanho_buffer];

    for (int i = 0; i <= maximo_grau_entrada; i++)
        intermediario[i] = 0;

    for (int j = 0; j < tamanho_buffer; j++)
        intermediario[grau_saida[buffer_vertices[j]]]++;

    for (int i = 1; i <= maximo_grau_entrada; i++)
        intermediario[i] += intermediario[i-1];

    for (int j = tamanho_buffer - 1; j >= 0; j--)
    {
        saida_temporaria[intermediario[grau_saida[buffer_vertices[j]]] - 1] = buffer_vertices[j];
        intermediario[grau_saida[buffer_vertices[j]]]--;
    }

    for (int j = 0; j < tamanho_buffer; j++)
        buffer_vertices[j] = saida_temporaria[j];
}

void obter_ordem_topologica(grafo* grafo, int array_vertices[])
{
    if (array_vertices == NULL)
    {
        log_error("ponteiro array_vertices é nulo!");
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

    int index_array = 0;
    int vertice;

    while (obter_vertice_grau_zero(grafo, estado, grau_entrada, &vertice))
    {
        array_vertices[index_array] = vertice;
        index_array++;
    }
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
    int grau_saida[grafo->numero_vertices];

    for (int vertice = 0; vertice < grafo->numero_vertices; vertice++)
    {
        estado[vertice] = nao_visitado;
        grau_entrada[vertice] = 0;
    }

    // obter o grau de entrada e saida de todos os vertices
    for (int vertice = 0; vertice < grafo->numero_vertices; vertice++)
    {
        for (int vertice_filho = 0; vertice_filho < grafo->numero_vertices; vertice_filho++)
        {
            if (!grafo->matriz[vertice][vertice_filho])
                continue;

            grau_entrada[vertice_filho]++;
            grau_saida[vertice]++;
        }
    }

    int index_linha;
    int index_coluna;

    // setar toda a matriz como -1
    for (index_linha = 0; index_linha < grafo->numero_vertices; index_linha++)
    {
        for (index_coluna = 0; index_coluna < numero_colunas; index_coluna++)
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
        // garantir que os primeiros vertices a serem processados sejam os que tem mais filhos
        ordenar_buffer(buffer_vertices, tamanho_buffer, grau_saida, grafo->numero_vertices - 1);

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
                tamanho_buffer = 0; // resetar o buffer e buscar novamente para adicionar ao buffer
                                    // os vertices filhos dos vertices ja processados na linha anterior
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

#ifndef GRAFOS
#define GRAFOS

#define MAX_VERTICE_NOME_TAMANHO 50

typedef struct grafo_strct
{
    int numero_vertices;
    int** matriz;
    char** nomes;
} grafo;

/**
 * @brief cria um grafo com determinado número de vertices
 * 
 * @return um ponteiro para o struct do grafo
 */
grafo* criar_grafo(int numero_vertices);

/**
 * @brief limpa a memoria alocada por um grafo
 */
void destruir_grafo(grafo* grafo);

#endif

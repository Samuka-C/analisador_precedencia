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

/**
 * @brief nomeia um vertice do grafo
 * 
 * @param grafo grafo a qual o vertice pertence
 * @param vertice indice do vertice
 * @param nome novo nome do vertice
 */
void nomear_vertice(grafo* grafo, int vertice, const char* nome);

/**
 * @brief conecta 2 vertices
 * 
 * @param grafo grafo a qual o vertice pertence
 * @param vertice_origem vertice da qual sai o arco
 * @param vertice_fim vertice da qual onde o arco chega
 */
void conectar_vertice(grafo* grafo, int vertice_origem, int vertice_fim);

#endif

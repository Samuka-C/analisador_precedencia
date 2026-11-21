#ifndef GRAFOS_ALGORITIMOS
#define GRAFOS_ALGORITIMOS

#include <grafos.h>

/**
 * @brief retorna 1 se existir um loop no grafo. caso não haja, retorna 0
 */
int detectar_ciclo(grafo* grafo);

/**
 * @brief obtem um array de vertices onde todos os arcos seguem a ordem dos vertices no array
 * ou seja, se existe um arco u -> v então u estará antes de v no array
 * 
 * @param grafo o grafo a ser analisado
 * @param array_vertices ponteiro de um array de inteiros com tamanho igual ou maior ao numero de vertices do grafo
 */
void obter_ordem_topologica(grafo* grafo, int* array_vertices);

/**
 * @brief similar a obter a ordem topologica no entanto os vertices são colocados em uma matriz onde cada linha, os vertices não são requisitos um dos outros
 * 
 * @param grafo o grafo a ser analisado
 * @param numero_colunas numero de colunas da matriz_saida
 * @param matriz_saida ponteiro para a matriz de saida onde seram escritos os vertices.
 * o tamanho deve ser grafo->numero_vertices x numero_colunas
 */
void obter_matriz_topologica(grafo* grafo, int numero_colunas, int** matriz_saida);

#endif
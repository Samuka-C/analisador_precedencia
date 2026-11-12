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
void obter_ordenacao(grafo* grafo, int* array_vertices);

#endif
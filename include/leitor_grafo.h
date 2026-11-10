#ifndef GRAFOS_LEITOR
#define GRAFOS_LEITOR

#include <grafos.h>

/**
 * @brief cria um grafo a partir de um arquivo txt na pasta "grafos_teste"
 * 
 * @param grafo_txt_nome nome do arquivo txt (sem o .txt) no final
 */
grafo* ler_grafo(const char* grafo_txt_nome);

#endif
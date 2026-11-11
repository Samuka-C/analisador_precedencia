#ifndef PILHA
#define PILHA

typedef struct pilha_elemento_struct
{
    struct pilha_elemento_struct* proximo_elemento;
    int valor;
} pilha_elemento;

typedef struct pilha_struct
{
    pilha_elemento* elemento_topo;
    int numero_elementos;
} pilha;

/**
 * @brief cria uma pilha vazia
 * 
 * @return o ponteiro para a nova pilha
 */
pilha* criar_pilha();

/**
 * @brief destroi uma pilha desalocando o espaço dela
 */
void destruir_pilha(pilha* pilha);

/**
 * @brief remove o item do topo da pilha
 * 
 * @return o valor do item removido
 */
int pop(pilha* pilha);

/**
 * @brief coloca um item no topo da pilha
 * 
 * @return 1 se o elemento pode ser colocado, 0 caso tenha falhado
 */
int push(pilha* pilha, int valor);

#endif
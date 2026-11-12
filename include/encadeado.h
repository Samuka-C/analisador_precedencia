#ifndef ENCADEADO
#define ENCADEADO

typedef struct item_struct
{
    struct item_struct* proximo_item;
    int valor;
} item;

typedef struct pilha_struct
{
    item* item_topo;
    int numero_items;
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
int pilha_pop(pilha* pilha);

/**
 * @brief coloca um item no topo da pilha
 * 
 * @return 1 se o item pode ser colocado, 0 caso tenha falhado
 */
int pilha_push(pilha* pilha, int valor);

#endif
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
 * @attention se a pilha estiver vazia, retorna 0 (nem sempre que retornar 0, a pilha vai estar vazia)
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

typedef struct fila_struct
{
    item* primeiro_item;
    item* ultimo_item;
    int numero_items;
} fila;

/**
 * @brief cria uma fila vazia
 * 
 * @return o ponteiro para a nova fila
 */
fila* criar_fila();

/**
 * @brief destroi uma fila desalocando o espaço dela
 */
void destruir_fila(fila* fila);

/**
 * @brief remove o primeiro item da fila
 * 
 * @attention se a fila estiver vazia, retorna 0 (nem sempre que retornar 0, a fila vai estar vazia)
 * 
 * @return o valor do item removido
 */
int fila_get(fila* fila);

/**
 * @brief coloca um item no final da fila
 * 
 * @return 1 se o item pode ser colocado, 0 caso tenha falhado
 */
int fila_push_frente(fila* fila, int valor);

/**
 * @brief cria uma nova fila a partir de duas filas, colando o começo de uma no final da outra
 * 
 * @param filaInicio fila que vai ficar no começo
 * @param filaFinal fila que vai ser grudada no final de filaInicio
 * 
 * @return o ponteiro para a nova fila
 */
fila* fila_fundir(fila* fila_inicio, fila* fila_final);

#endif
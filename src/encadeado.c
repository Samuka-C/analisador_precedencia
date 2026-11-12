#include <encadeado.h>

#include <stdlib.h>

pilha* criar_pilha()
{
    pilha* nova_pilha = (pilha*)malloc(sizeof(pilha));
    if (nova_pilha == NULL)
        return NULL;

    nova_pilha->numero_items = 0;
    nova_pilha->item_topo = NULL;

    return nova_pilha;
}

void destruir_pilha(pilha* pilha)
{
    if (pilha == NULL)
        return;

    while (pilha->numero_items > 0)
    {
        pop(pilha);
    }

    free(pilha);
}

int pilha_pop(pilha* pilha)
{
    item* topo = pilha->item_topo;
    int valor_topo = topo->valor;

    item* item_depois_do_topo = topo->proximo_item; // pode ser NULL
    pilha->item_topo = item_depois_do_topo;
    pilha->numero_items--;

    free(topo);

    return valor_topo;
}

int pilha_push(pilha* pilha, int valor)
{
    item* novo_item = (item*)malloc(sizeof(item));
    if (novo_item == NULL)
        return 0;

    novo_item->valor = valor;

    item* ex_topo = pilha->item_topo;
    novo_item->proximo_item = ex_topo;
    pilha->item_topo = novo_item;
    pilha->numero_items++;

    return 1;
}

fila* criar_fila()
{
    fila* nova_fila = (fila*)malloc(sizeof(fila));
    if (nova_fila == NULL)
        return NULL;

    nova_fila->numero_items = 0;
    nova_fila->primeiro_item = NULL;
    nova_fila->ultimo_item = NULL;
}

void destruir_fila(fila* fila)
{
    if (fila == NULL)
        return;

    while (fila->numero_items > 0)
    {
        fila_get(fila);
    }

    free(fila);
}

int fila_get(fila* fila)
{
    item* primeiro_item = fila->primeiro_item;
    int valor = primeiro_item->valor;

    item* proximo_primeiro_item = primeiro_item->proximo_item;
    fila->primeiro_item = proximo_primeiro_item;
    fila->numero_items--;

    free(primeiro_item);

    return valor;
}

int fila_push_frente(fila* fila, int valor)
{
    item* novo_item = (item*)malloc(sizeof(item));
    if (novo_item == NULL)
        return 0;

    novo_item->valor = valor;
    novo_item->proximo_item = NULL;

    fila->ultimo_item->proximo_item = novo_item;
    fila->numero_items++;

    if (fila->numero_items == 1)
        fila->primeiro_item = novo_item;
}

fila* fila_fundir(fila* fila_inicio, fila* fila_final)
{
    fila* nova_fila = criar_fila();
    if (nova_fila == NULL)
        return NULL;

    while (fila_inicio->numero_items > 0)
        fila_push_frente(nova_fila, fila_get(fila_inicio));

    destruir_fila(fila_inicio);
    
    while (fila_final->numero_items > 0)
        fila_push_frente(nova_fila, fila_get(fila_final)); 
    
    destruir_fila(fila_final);

    return nova_fila;
}

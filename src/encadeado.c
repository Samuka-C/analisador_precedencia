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
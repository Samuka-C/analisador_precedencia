#include <encadeado.h>

#include <stdlib.h>

pilha* criar_pilha()
{
    pilha* nova_pilha = (pilha*)malloc(sizeof(pilha));
    if (nova_pilha == NULL)
        return NULL;

    nova_pilha->numero_elementos = 0;
    nova_pilha->elemento_topo = NULL;

    return nova_pilha;
}

void destruir_pilha(pilha* pilha)
{
    if (pilha == NULL)
        return;

    while (pilha->numero_elementos > 0)
    {
        pop(pilha);
    }

    free(pilha);
}

int pilha_pop(pilha* pilha)
{
    pilha_elemento* topo = pilha->elemento_topo;
    int valor_topo = topo->valor;

    pilha_elemento* elemento_depois_do_topo = topo->proximo_elemento; // pode ser NULL
    pilha->elemento_topo = elemento_depois_do_topo;
    pilha->numero_elementos--;

    free(topo);

    return valor_topo;
}

int pilha_push(pilha* pilha, int valor)
{
    pilha_elemento* novo_elemento = (pilha_elemento*)malloc(sizeof(pilha_elemento));
    if (novo_elemento == NULL)
        return 0;

    novo_elemento->valor = valor;

    pilha_elemento* ex_topo = pilha->elemento_topo;
    novo_elemento->proximo_elemento = ex_topo;
    pilha->elemento_topo = novo_elemento;
    pilha->numero_elementos++;

    return 1;
}
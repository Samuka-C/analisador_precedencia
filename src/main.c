#include <grafos.h>
#include <leitor_grafo.h>

#include <stdio.h>

int main()
{
    grafo* grafo = ler_grafo("grafo_0");

    printar_grafo(grafo);

    return 0;
}
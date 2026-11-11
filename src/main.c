#include <grafos.h>
#include <leitor_grafo.h>
#include <algoritimos_grafos.h>

#include <stdio.h>

int main()
{
    grafo* grafo = ler_grafo("grafo_0");

    printar_grafo(grafo);

    int ciclo = detectar_ciclo(grafo);

    if (ciclo)
        printf("existe ciclo");
    else
        printf("nao existe ciclo");

    return 0;
}
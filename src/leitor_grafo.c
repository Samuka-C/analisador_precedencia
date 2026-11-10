#include <leitor_grafo.h>

#define BUFFER_TAMANHO 256

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief le um arquivo e retorna um array de linhas
 * 
 * @param numero_de_linhas ponteiro para um inteiro para escrever o número de linhas
 */
char** ler_arquivo(const char* caminho_arquivo, int* numero_de_linhas)
{
    // abrir arquivo para leitura
    FILE* file_ptr = fopen(caminho_arquivo, "r");

    if (file_ptr == NULL)
        return NULL;

    // obter informações importantes sobre o arquivo de texto
    int numero_linhas = 1;
    int tamanho_linha = 0;
    int tamanho_maior_linha = 0;

    int proximo_charactere;

    while ((proximo_charactere = fgetc(file_ptr)) != EOF)
    {
        if (proximo_charactere == '\n')
        {
            numero_linhas++;
            tamanho_maior_linha = tamanho_maior_linha < tamanho_linha 
                ? tamanho_linha 
                : tamanho_maior_linha;
            tamanho_linha = 0;
            continue;
        }

        tamanho_linha++;
    }

    tamanho_maior_linha = tamanho_maior_linha < tamanho_linha 
        ? tamanho_linha 
        : tamanho_maior_linha;

    // alocar memoria para as linhas
    char** linhas = (char**)malloc(numero_linhas * sizeof(char*));

    if (linhas == NULL)
    {
        fclose(file_ptr);
        return NULL;
    }

    for (int i = 0; i < numero_linhas; i++)
    {
        linhas[i] = (char*)calloc(tamanho_maior_linha + 1, sizeof(char));

        if (linhas[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(linhas[j]);

            free(linhas);
            fclose(file_ptr);
            return NULL;
        }
    }

    // fazer rewind para ler novamente o arquivo, dessa vez escrevendo no espaço alocado
    rewind(file_ptr);

    int contador_linhas = 0;
    int contador_charactere = 0;

    while ((proximo_charactere = fgetc(file_ptr)) != EOF)
    {
        if (proximo_charactere == '\n')
        {
            contador_linhas++;
            contador_charactere = 0;
            continue;
        }

        linhas[contador_linhas][contador_charactere] = proximo_charactere;
        contador_charactere++;
    }

    fclose(file_ptr);

    *numero_de_linhas = numero_linhas;
    return linhas;
}

grafo* ler_grafo(const char* grafo_txt_nome)
{
    char caminho_arquivo[BUFFER_TAMANHO];
    snprintf(caminho_arquivo, sizeof(caminho_arquivo), "grafos_teste/%s.txt", grafo_txt_nome);

    int numero_de_linhas = 0;
    char** linhas = ler_arquivo(caminho_arquivo, &numero_de_linhas);

    int numero_vertices = 0;
    grafo* novo_grafo = NULL;

    for (int contador_linha = 0; contador_linha < numero_de_linhas; contador_linha++)
    {
        char* linha = linhas[contador_linha];
        
        if (contador_linha == 0)
        {
            sscanf(linha, "%d", &numero_vertices);
            novo_grafo = criar_grafo(numero_vertices);
            continue;
        }

        if (contador_linha <= numero_vertices)
        {
            int vertice_id = contador_linha - 1;
            nomear_vertice(novo_grafo, vertice_id, linha);
            continue;
        }

        int vertice_1, vertice_2;
        sscanf(linha, "%d->%d", &vertice_1, &vertice_2);

        conectar_vertice(novo_grafo, vertice_1, vertice_2);
    }

    return novo_grafo;
}

#include <stdio.h>
#include "headers/caverna.h"
#include "headers/dp.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Use: %s <arquivo_caverna>\n", argv[0]);
        return 1;
    }

    Caverna caverna;
    lerArquivo(argv[1], &caverna);

    int caminho[MAX_LINHAS * MAX_COLUNAS][2];
    int tamanho_caminho = encontrarMelhorCaminho(&caverna, caminho);

    gerarArquivoResultado(caminho, tamanho_caminho);

    return 0;
}
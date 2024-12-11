#include <stdio.h>
#include <stdlib.h>
#include "../headers/caverna.h"

void lerArquivo(char* caminho, Caverna* caverna) {
    FILE* arquivo = fopen(caminho, "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    fscanf(arquivo, "%d %d %d", 
           &caverna->linhas, 
           &caverna->colunas, 
           &caverna->pontos_iniciais);

    for (int i = 0; i < caverna->linhas; i++) {
        for (int j = 0; j < caverna->colunas; j++) {
            char celula[10];
            fscanf(arquivo, "%s", celula);

            if (celula[0] == 'F') 
                caverna->matriz[i][j] = 'F'; 
            else if (celula[0] == 'I') 
                caverna->matriz[i][j] = 'I'; 
            else 
                caverna->matriz[i][j] = atoi(celula); 
        }
    }

    fclose(arquivo);
}


void gerarArquivoResultado(int caminho[][2], int tamanho) {
    FILE* resultado = fopen("resultado.txt", "w");
    
    if (tamanho == 0) {
        fprintf(resultado, "impossível\n");
    } else {
        for (int i = 0; i < tamanho; i++) {
            fprintf(resultado, "%d %d\n", caminho[i][0], caminho[i][1]);
        }
    }
    
    fclose(resultado);
}
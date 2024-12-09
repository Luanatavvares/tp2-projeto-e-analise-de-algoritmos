#ifndef CAVERNA_H
#define CAVERNA_H

#define MAX_LINHAS 100
#define MAX_COLUNAS 100

typedef struct {
    int pontos_vida;
    int veio_x;
    int veio_y;
} CelulaDP;

typedef struct {
    int linhas;
    int colunas;
    int pontos_iniciais;
    int matriz[MAX_LINHAS][MAX_COLUNAS];
} Caverna;

void lerArquivo(char* caminho, Caverna* caverna);
void gerarArquivoResultado(int caminho[][2], int tamanho);

#endif
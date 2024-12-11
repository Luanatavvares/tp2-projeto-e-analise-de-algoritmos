#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../headers/caverna.h"
#include "../headers/dp.h"

#define MAX_CAMINHO (MAX_LINHAS * MAX_COLUNAS)

int encontrarMelhorCaminho(Caverna* caverna, int caminho[][2]) {
    CelulaDP dp[MAX_LINHAS][MAX_COLUNAS];
    int inicio_x = -1, inicio_y = -1, fim_x = -1, fim_y = -1;

    // Inicializar a matriz DP e encontrar pontos de início ('I') e fim ('F')
    for (int i = 0; i < caverna->linhas; i++) {
        for (int j = 0; j < caverna->colunas; j++) {
            dp[i][j].pontos_vida = INT_MIN; // Inicializa com o menor valor possível
            dp[i][j].veio_x = -1;
            dp[i][j].veio_y = -1;

            if (caverna->matriz[i][j] == 'I') {
                inicio_x = i;
                inicio_y = j;
            }

            if (caverna->matriz[i][j] == 'F') {
                fim_x = i;
                fim_y = j;
            }
        }
    }

    // Verificar se pontos inicial e final foram encontrados
    if (inicio_x == -1 || inicio_y == -1 || fim_x == -1 || fim_y == -1) {
        printf("Erro: pontos de entrada 'I' ou saída 'F' não encontrados na matriz.\n");
        return 0;
    }

    // Inicializar a posição inicial na matriz DP
    dp[inicio_x][inicio_y].pontos_vida = caverna->pontos_iniciais;

    // Usar uma fila para processar as células
    typedef struct {
        int x, y;
    } Posicao;

    Posicao fila[MAX_CAMINHO];
    int frente = 0, tras = 0;

    fila[tras++] = (Posicao){inicio_x, inicio_y};

    // Movimentos possíveis (cima e esquerda apenas)
    int dx[] = {-1, 0};
    int dy[] = {0, -1};

    while (frente < tras) {
        Posicao atual = fila[frente++];
        int x = atual.x;
        int y = atual.y;

        int pontos_atual = dp[x][y].pontos_vida;

        for (int d = 0; d < 2; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx >= 0 && ny >= 0 && caverna->matriz[nx][ny] != '#') {
                int valor_celula = (caverna->matriz[nx][ny] == 'F' || caverna->matriz[nx][ny] == 'I')
                                    ? 0
                                    : caverna->matriz[nx][ny];

                int novo_pontos = pontos_atual + valor_celula;

                if (novo_pontos > dp[nx][ny].pontos_vida) {
                    dp[nx][ny].pontos_vida = novo_pontos;
                    dp[nx][ny].veio_x = x;
                    dp[nx][ny].veio_y = y;
                    fila[tras++] = (Posicao){nx, ny};
                }
            }
        }
    }

    // Verificar se o ponto final foi alcançado
    if (dp[fim_x][fim_y].pontos_vida == INT_MIN) {
        printf("Nenhum caminho viável encontrado até o ponto de saída 'F'.\n");
        return 0;
    }

    // Reconstruir o caminho do ponto final para o inicial
    int caminho_length = 0;
    int atual_x = fim_x, atual_y = fim_y;

    while (atual_x != -1 && atual_y != -1) {
        caminho[caminho_length][0] = atual_x;
        caminho[caminho_length][1] = atual_y;
        caminho_length++;

        int prox_x = dp[atual_x][atual_y].veio_x;
        int prox_y = dp[atual_x][atual_y].veio_y;
        atual_x = prox_x;
        atual_y = prox_y;
    }

    // Inverter o caminho para começar do início
    for (int i = 0; i < caminho_length / 2; i++) {
        int temp_x = caminho[i][0];
        int temp_y = caminho[i][1];
        caminho[i][0] = caminho[caminho_length - 1 - i][0];
        caminho[i][1] = caminho[caminho_length - 1 - i][1];
        caminho[caminho_length - 1 - i][0] = temp_x;
        caminho[caminho_length - 1 - i][1] = temp_y;
    }

    printf("Melhor caminho encontrado com %d pontos de vida.\n", dp[fim_x][fim_y].pontos_vida);
    return caminho_length;
}

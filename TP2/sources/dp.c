#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../headers/caverna.h"
#include "../headers/dp.h"


int encontrarMelhorCaminho(Caverna* caverna, int caminho[][2]) {
    CelulaDP dp[MAX_LINHAS][MAX_COLUNAS];
    int fim_x = -1, fim_y = -1;

    for (int i = 0; i < caverna->linhas; i++) {
        for (int j = 0; j < caverna->colunas; j++) {
            dp[i][j].pontos_vida = -1; 
            dp[i][j].veio_x = -1;
            dp[i][j].veio_y = -1;

            if (caverna->matriz[i][j] == 'F') {
                fim_x = i;
                fim_y = j;
            }
        }
    }

    if (fim_x == -1 || fim_y == -1) {
        printf("Erro: posição de saída 'F' não encontrada.\n");
        return 0;
    }

    int melhor_pontos = INT_MIN;
    int melhor_inicio_x = -1, melhor_inicio_y = -1;

    for (int inicio_i = 0; inicio_i < caverna->linhas; inicio_i++) {
        for (int inicio_j = 0; inicio_j < caverna->colunas; inicio_j++) {
            if (inicio_i != 0 && inicio_i != caverna->linhas - 1 && 
                inicio_j != 0 && inicio_j != caverna->colunas - 1) 
                continue;


            for (int i = 0; i < caverna->linhas; i++) {
                for (int j = 0; j < caverna->colunas; j++) {
                    dp[i][j].pontos_vida = -1;
                    dp[i][j].veio_x = -1;
                    dp[i][j].veio_y = -1;
                }
            }

            dp[inicio_i][inicio_j].pontos_vida = caverna->pontos_iniciais + caverna->matriz[inicio_i][inicio_j];

            if (dp[inicio_i][inicio_j].pontos_vida <= 0) {
                printf("Caminho inicial inválido em (%d, %d) com pontos de vida: %d\n", inicio_i, inicio_j, dp[inicio_i][inicio_j].pontos_vida);
                continue;
            }

            // Computar caminhos
            for (int i = inicio_i; i < caverna->linhas; i++) {
                for (int j = (i == inicio_i ? inicio_j : 0); j < caverna->colunas; j++) {
                    if (i == inicio_i && j == inicio_j) continue;

                    int max_pontos = INT_MIN, origem_x = -1, origem_y = -1;

                    // Verificar movimentos válidos
                    if (i > 0 && dp[i - 1][j].pontos_vida > 0) {
                        int pontos_atual = dp[i - 1][j].pontos_vida + caverna->matriz[i][j];
                        if (pontos_atual > max_pontos && pontos_atual > 0) {
                            max_pontos = pontos_atual;
                            origem_x = i - 1;
                            origem_y = j;
                        }
                    }

                    if (j > 0 && dp[i][j - 1].pontos_vida > 0) {
                        int pontos_atual = dp[i][j - 1].pontos_vida + caverna->matriz[i][j];
                        if (pontos_atual > max_pontos && pontos_atual > 0) {
                            max_pontos = pontos_atual;
                            origem_x = i;
                            origem_y = j - 1;
                        }
                    }

                    if (max_pontos > INT_MIN) {
                        dp[i][j].pontos_vida = max_pontos;
                        dp[i][j].veio_x = origem_x;
                        dp[i][j].veio_y = origem_y;

                        if (i == fim_x && j == fim_y && max_pontos > melhor_pontos) {
                            melhor_pontos = max_pontos;
                            melhor_inicio_x = inicio_i;
                            melhor_inicio_y = inicio_j;
                        }
                    }
                }
            }
        }
    }

    if (melhor_pontos > INT_MIN) {
        printf("Melhor caminho encontrado com %d pontos de vida.\n", melhor_pontos);
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

        for (int i = 0; i < caminho_length / 2; i++) {
            int temp_x = caminho[i][0];
            int temp_y = caminho[i][1];
            caminho[i][0] = caminho[caminho_length - 1 - i][0];
            caminho[i][1] = caminho[caminho_length - 1 - i][1];
            caminho[caminho_length - 1 - i][0] = temp_x;
            caminho[caminho_length - 1 - i][1] = temp_y;
        }

        return caminho_length;
    }

    printf("Nenhum caminho viável encontrado.\n");
    return 0;
}

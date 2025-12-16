#  Trabalho Prático 2 — Projeto e Análise de Algoritmos  
## Navegação em Caverna com Programação Dinâmica

Este trabalho implementa um programa em **linguagem C** que simula a navegação de um estudante em uma **caverna cheia de desafios**, com o objetivo de alcançar a saída mantendo o **maior número possível de Pontos de Vida (PV)**. A caverna é representada como uma matriz, onde cada célula pode conter bônus, penalidades, obstáculos ou inimigos, tornando a escolha do caminho um problema de otimização.

O projeto foi desenvolvido no contexto da disciplina **Projeto e Análise de Algoritmos (PAA)** e tem como foco principal a aplicação de **Programação Dinâmica**, combinada com técnicas de busca e reconstrução de caminho, para resolver o problema de forma eficiente.

## Ideia Geral

O estudante inicia sua jornada em uma posição inicial da matriz e deve alcançar um ponto final específico. Ao longo do percurso, cada célula visitada altera seus pontos de vida, podendo aumentar ou diminuir o valor acumulado. O desafio consiste em encontrar um caminho viável que leve à saída **maximizando os PV finais**.

Caso não exista nenhum caminho que permita ao estudante sair da caverna com vida, o programa identifica corretamente que "não há solução possível".

## Funcionalidades Principais

- **Leitura da caverna a partir de arquivo**  
  O programa carrega a configuração da caverna, os pontos de vida iniciais e as posições inicial e final a partir de um arquivo de entrada.

- **Cálculo do caminho ótimo**  
  Utiliza Programação Dinâmica para determinar o trajeto que maximiza os pontos de vida acumulados até a saída.

- **Reconstrução do caminho**  
  Após o cálculo, o programa reconstrói o percurso ótimo, listando todas as coordenadas visitadas.

- **Geração de arquivo de saída**  
  O caminho encontrado é salvo em um arquivo texto. Caso não exista solução, o arquivo contém a palavra `impossível`.

## Desenvolvimento e Estruturas Utilizadas

O projeto foi desenvolvido de forma modular, com separação clara entre definição e implementação:

- **headers/**  
  Contém os arquivos `.h`, responsáveis pelas definições das estruturas de dados e protótipos das funções principais, como a estrutura da caverna e os métodos de programação dinâmica.

- **sources/**  
  Contém os arquivos `.c`, com as implementações das funções de leitura de arquivo, cálculo do caminho ótimo e geração do arquivo de saída.

A função central do projeto é responsável por:
- construir uma matriz de **Programação Dinâmica (DP)** para armazenar os melhores valores de PV em cada célula;
- utilizar uma **busca em largura (BFS)** para propagar os valores acumulados;
- garantir que apenas caminhos válidos e vantajosos sejam considerados;
- reconstruir o melhor caminho a partir dos ponteiros armazenados.

## Como Executar

O projeto utiliza um **Makefile**, que automatiza o processo de compilação.  
No terminal, dentro do diretório do trabalho, execute:

```bash
make
./programa entrada.txt

#include <stdio.h>

#include <stdlib.h> // para usar a função abs()

// Tamanho do tabuleiro e das habilidades
#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5

// Função para criar o tabuleiro todo com água (valor 0)
void criarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            tabuleiro[linha][coluna] = 0;
        }
    }
}

// Coloca navios fixos no tabuleiro (valor 3)
void colocarNavios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    tabuleiro[2][2] = 3;
    tabuleiro[2][3] = 3;
    tabuleiro[3][2] = 3;
    tabuleiro[3][3] = 3;
    tabuleiro[4][4] = 3;
}

// Cria a matriz de habilidade em forma de cone
void criarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= 2 - i && j <= 2 + i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Cria a matriz de habilidade em forma de cruz
void criarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == 2 || j == 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Cria a matriz de habilidade em forma de octaedro (losango)
void criarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int distancia = abs(2 - i) + abs(2 - j);
            if (distancia <= 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Aplica a habilidade no tabuleiro, marcando com 5
void aplicarHabilidadeNoTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                                   int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                                   int origemLinha, int origemColuna) {
    int meio = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linha = origemLinha + i - meio;
            int coluna = origemColuna + j - meio;

            // Verifica se está dentro do tabuleiro
            if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] != 3) {
                    tabuleiro[linha][coluna] = 5; // Marca área afetada
                }
            }
        }
    }
}

// Mostra o tabuleiro no console
void mostrarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    criarTabuleiro(tabuleiro); // Preenche com água
    colocarNavios(tabuleiro);  // Coloca navios

    // Criar e aplicar habilidade tipo CONE
    criarHabilidadeCone(habilidade);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidade, 2, 2); // Aplica no ponto (2,2)

    // Criar e aplicar habilidade tipo CRUZ
    criarHabilidadeCruz(habilidade);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidade, 5, 5); // Aplica no ponto (5,5)

    // Criar e aplicar habilidade tipo OCTAEDRO
    criarHabilidadeOctaedro(habilidade);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidade, 7, 7); // Aplica no ponto (7,7)

    // Mostrar resultado final
    printf("Tabuleiro final com habilidades aplicadas:\n");
    mostrarTabuleiro(tabuleiro);

    return 0;
}
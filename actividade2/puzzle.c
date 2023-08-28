#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAMANHO 3

typedef struct {
    int estado[TAMANHO][TAMANHO];
} Puzzle;

bool eh_objetivo(Puzzle *puzzle, Puzzle *objetivo) {
    return memcmp(puzzle, objetivo, sizeof(Puzzle)) == 0;
}

void gerar_estados_seguintes(Puzzle *puzzle, Puzzle *estados_seguintes[4]) {
    int linha, coluna;
    int linha_vazia, coluna_vazia;

    // Encontrar a posição da peça vazia (0)
    for (linha = 0; linha < TAMANHO; linha++) {
        for (coluna = 0; coluna < TAMANHO; coluna++) {
            if (puzzle->estado[linha][coluna] == 0) {
                linha_vazia = linha;
                coluna_vazia = coluna;
                break;
            }
        }
    }

    int dr[] = {-1, 1, 0, 0};  // Deslocamentos verticais
    int dc[] = {0, 0, -1, 1};  // Deslocamentos horizontais

    int i, nova_linha, nova_coluna;
    for (i = 0; i < 4; i++) {
        nova_linha = linha_vazia + dr[i];
        nova_coluna = coluna_vazia + dc[i];

        // Verificar se o novo estado é válido
        if (nova_linha >= 0 && nova_linha < TAMANHO && nova_coluna >= 0 && nova_coluna < TAMANHO) {
            Puzzle *novo_estado = (Puzzle *)malloc(sizeof(Puzzle));
            memcpy(novo_estado, puzzle, sizeof(Puzzle));

            // Trocar a posição da peça vazia com a peça adjacente
            novo_estado->estado[linha_vazia][coluna_vazia] = novo_estado->estado[nova_linha][nova_coluna];
            novo_estado->estado[nova_linha][nova_coluna] = 0;

            estados_seguintes[i] = novo_estado;
        } else {
            estados_seguintes[i] = NULL;
        }
    }
}

void imprimir_estado(Puzzle *puzzle) {
    int linha, coluna;
    for (linha = 0; linha < TAMANHO; linha++) {
        for (coluna = 0; coluna < TAMANHO; coluna++) {
            if (puzzle->estado[linha][coluna] == 0) {
                printf("# ");  // Peça vazia
            } else {
                printf("%d ", puzzle->estado[linha][coluna]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // Estado inicial e objetivo
    Puzzle estado_inicial = {
        {{1, 2, 3}, {6, 5, 4}, {0, 7, 8}}  // 0 representa a posição vazia
    };

    Puzzle estado_objetivo = {
        {{1, 2, 3}, {6, 5, 4}, {7, 8, 0}}
    };

    Puzzle *fila[10000];
    int frente = 0;
    int tras = 0;

    fila[tras++] = &estado_inicial;

    while (frente < tras) {
        Puzzle *estado_atual = fila[frente++];

        if (eh_objetivo(estado_atual, &estado_objetivo)) {
            printf("Puzzle resolvido!\n");
            break;
        }

        printf("Estado atual:\n");
        imprimir_estado(estado_atual);

        Puzzle *estados_seguintes[4];
        gerar_estados_seguintes(estado_atual, estados_seguintes);

        int i;
        for (i = 0; i < 4; i++) {
            if (estados_seguintes[i] != NULL) {
                fila[tras++] = estados_seguintes[i];
            }
        }
    }

    if (frente >= tras) {
        printf("Puzzle não pode ser resolvido.\n");
    }

    return 0;
}


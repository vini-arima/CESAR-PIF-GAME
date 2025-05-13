#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"

typedef struct {
    char nome[50];
    int pontos;
} JogadorRanking;

#define ARQUIVO_RANKING "ranking.txt"

void salvarPontuacao(const char* nome, int pontos) {
    FILE* f = fopen(ARQUIVO_RANKING, "a");
    if (f) {
        fprintf(f, "%s %d\n", nome, pontos);
        fclose(f);
    }
}

int comparar(const void* a, const void* b) {
    return ((JogadorRanking*)b)->pontos - ((JogadorRanking*)a)->pontos;
}

void exibirRanking() {
    mostrarRanking();
}

void mostrarRanking() {
    JogadorRanking jogadores[100];
    int count = 0;

    FILE* f = fopen(ARQUIVO_RANKING, "r");
    if (!f) return;

    while (fscanf(f, "%s %d", jogadores[count].nome, &jogadores[count].pontos) == 2) {
        count++;
    }
    fclose(f);

    qsort(jogadores, count, sizeof(JogadorRanking), comparar);

    printf("🏆 Ranking:\n");
    for (int i = 0; i < count && i < 10; i++) {
        printf("%d. %s - %d pts\n", i + 1, jogadores[i].nome, jogadores[i].pontos);
    }
}

void inicializarRanking() {
    FILE* f = fopen(ARQUIVO_RANKING, "a");
    if (f) fclose(f);
}

void salvarRanking() {
    // NOP - Apenas placeholder, já salva direto em salvarPontuacao
}

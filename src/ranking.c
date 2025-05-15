#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"
#include "screen.h"
#include "utils.h"

#define ARQUIVO_RANKING "ranking.txt"
#define MAX_LINHA 100

int compararPontuacao(const void* a, const void* b) {
    return ((JogadorRanking*)b)->pontos - ((JogadorRanking*)a)->pontos;
}

void salvarPontuacao(const char* nome, int pontos) {
    if (pontos <= 0) return;
    
    FILE* f = fopen(ARQUIVO_RANKING, "a");
    if (f) {
        fprintf(f, "\"%s\" %d\n", nome, pontos);
        fclose(f);
    }
}

void mostrarRanking() {
    FILE* f = fopen(ARQUIVO_RANKING, "r");
    if (!f) {
        f = fopen(ARQUIVO_RANKING, "w");
        if (f) fclose(f);
        return;
    }

    JogadorRanking jogadores[MAX_JOGADORES];
    int count = 0;
    char linha[MAX_LINHA];

    while (fgets(linha, sizeof(linha), f) && count < MAX_JOGADORES) {
        char nome[TAM_NOME];
        int pontos;
        
        if (sscanf(linha, "\"%49[^\"]\" %d", nome, &pontos) == 2) {
            strncpy(jogadores[count].nome, nome, TAM_NOME-1);
            jogadores[count].nome[TAM_NOME-1] = '\0';
            jogadores[count].pontos = pontos;
            count++;
        }
    }
    fclose(f);

    qsort(jogadores, count, sizeof(JogadorRanking), compararPontuacao);

    screenClear();
    
    // Configurações de posição alinhadas à esquerda
    const int coluna = 10;
    
    // Título do ranking
    screenGotoxy(coluna, 3);
    screenSetColor(YELLOW, -1);
    printf(" 🏆 TOP 10 RANKING 🏆 ");
    
    // Lista de jogadores - TODO EM AMARELO
    int maxToShow = (count > 10) ? 10 : count;
    for (int i = 0; i < maxToShow; i++) {
        screenGotoxy(coluna, 5 + i);
        screenSetColor(YELLOW, -1);  // Define cor amarela para todos os itens
        
        // Adiciona medalhas para os 3 primeiros
        if (i == 0) {
            printf("🥇 ");
        } else if (i == 1) {
            printf("🥈 ");
        } else if (i == 2) {
            printf("🥉 ");
        } else {
            printf("%2d.", i+1);
        }
        
        printf("%-15s%5d pts", jogadores[i].nome, jogadores[i].pontos);
    }

    // Mensagem do ENTER (azul)
    screenGotoxy(coluna, 5 + maxToShow + 2);
    screenSetColor(LIGHTBLUE, -1);
    printf("Pressione ENTER para voltar...");
    screenSetNormal();
    
    fflush(stdout);
    
    // Lógica simplificada - só verifica quebra de linha
    int c;
    do {
        c = getchar();
    } while (c != '\n'); // Só sai quando receber ENTER
}

    void inicializarRanking() {
    FILE* f = fopen(ARQUIVO_RANKING, "a");
    if (f) fclose(f);
}
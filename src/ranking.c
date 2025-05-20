#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"
#include "screen.h"
#include "utils.h"

#define ARQUIVO_RANKING "ranking.txt"  
#define MAX_LINHA 100                  
#define MAX_JOGADORES 100             


int compararPontuacao(const void* a, const void* b) {
    int pa = ((JogadorRanking*)a)->pontos;
    int pb = ((JogadorRanking*)b)->pontos;

    if (pb > pa) return 1;
    if (pb < pa) return -1;
    return 0;
}


void salvarPontuacao(const char* nome, int pontos) {
    if (pontos <= 0) return;  

    FILE* f = fopen(ARQUIVO_RANKING, "a");  
    if (!f) {
        
        return;
    }

    
    fprintf(f, "\"%s\" %d\n", nome, pontos);
    fclose(f);
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
           
            strncpy(jogadores[count].nome, nome, TAM_NOME - 1);
            jogadores[count].nome[TAM_NOME - 1] = '\0';
            jogadores[count].pontos = pontos;
            count++;
        }
       
    }
    fclose(f);

   
    qsort(jogadores, count, sizeof(JogadorRanking), compararPontuacao);

  
    screenClear();

    const int coluna = 10;  

    
    screenGotoxy(coluna, 3);
    screenSetColor(YELLOW, -1);
    printf(" 🏆 TOP 10 RANKING 🏆 ");

    
    int maxToShow = (count > 10) ? 10 : count;

    
    for (int i = 0; i < maxToShow; i++) {
        screenGotoxy(coluna, 5 + i);
        screenSetColor(YELLOW, -1);

        if (i == 0) {
            printf("🥇 ");
        } else if (i == 1) {
            printf("🥈 ");
        } else if (i == 2) {
            printf("🥉 ");
        } else {
            printf("%2d.", i + 1);
        }

       
        printf("%-15s%5d pts", jogadores[i].nome, jogadores[i].pontos);
    }

    
    screenGotoxy(coluna, 5 + maxToShow + 2);
    screenSetColor(LIGHTBLUE, -1);
    printf("Pressione ENTER para voltar...");
    screenSetNormal();

    fflush(stdout);


    int c;
    do {
        c = getchar();
    } while (c != '\n');
}

// Inicializa o arquivo de ranking se ainda não existir
void inicializarRanking() {
    FILE* f = fopen(ARQUIVO_RANKING, "a");
    if (f) fclose(f);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "manipulacao_txt.h"

void salvar_ranking(const char *nome_jogador, int vitoria_geral) {
    FILE *arquivo = fopen("ranking.txt", "a"); 
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de ranking.\n");
        return;
    }
    fprintf(arquivo, "Jogador: %s - Vitórias: %d\n", nome_jogador, vitoria_geral); 
    fclose(arquivo); 
}



void exibir_ranking() {

    screenClear();
    screenInit(1);
    int m = 7;
    FILE *arquivo = fopen("ranking.txt", "r");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo de ranking.\n");
        return;
    }

    Registro registros[100]; 
    int total = 0;

    
    while (total < 100 && fscanf(arquivo, "Jogador: %49[^-] - Vitórias: %d\n", registros[total].nome, &registros[total].vitorias) == 2) {
        total++;
    }

    fclose(arquivo);

    
    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (registros[i].vitorias < registros[j].vitorias) {
                Registro temp = registros[i];
                registros[i] = registros[j];
                registros[j] = temp;
            }
        }
    }

    screenGotoxy(20, 5);
    printf("===== RANKING - TOP 5 =====");
    for (int i = 0; i < total && i < 5; i++) {
        screenGotoxy(20, m);
        printf("%d. Jogador: %s - Vitórias: %d", i + 1, registros[i].nome, registros[i].vitorias);
        m++;
    }

    screenGotoxy(45,22 );
    printf("Pressione ENTER para continuar...");
    getchar();

    if (total == 0) {
        printf("Nenhum registro encontrado.\n");
    }
}
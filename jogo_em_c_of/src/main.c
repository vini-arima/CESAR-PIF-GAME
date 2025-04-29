#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "funcoes.h"
#include "manipulacao_txt.h"

int main() {
    screenInit(1);
    keyboardInit();

    Estatisticas *stats = malloc(sizeof(Estatisticas));
    if (stats == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        return 1;
    }

    logo_entrada();
    explicacao_jogo();

    int vitoria_geral = 0;
    int derrota_geral = 0;
    char opcao_sair;

    do {
        int round = 1;
        stats->vitorias = 0;
        stats->derrotas = 0;
        stats->empates = 0;

        do {
            int opcao_user = escolha_opcao(round);
            round++;
            verificacao_da_escolha(opcao_user, stats);

            screenGotoxy(22, 12);
            printf("Pressione ENTER para continuar...");
            getchar();
            getchar();

            screenClear();
            screenInit(1);
        } while (stats->vitorias < 3 && stats->derrotas < 3);

        mostrar_resultados(stats);
        if (stats->vitorias == 3) {
            vitoria_geral++;
        } else if (stats->derrotas == 3) {
            derrota_geral++;
        }

        screenClear();
        screenInit(1);

        logo_Apresentacao(); 
        screenGotoxy(36, 12);
        printf("Deseja jogar outra? Sim[S] Não[N]: ");
        scanf(" %c", &opcao_sair);

    } while (opcao_sair == 'S' || opcao_sair == 's');

   
    char nome_jogador[50];
    screenClear();
    screenInit(1);

    logo_Apresentacao(); 
    screenGotoxy(36, 10);
    printf("Digite seu nome para salvar no ranking: ");  
    fgets(nome_jogador, sizeof(nome_jogador), stdin);

    
    nome_jogador[strcspn(nome_jogador, "\n")] = '\0';

    salvar_ranking(nome_jogador, vitoria_geral);
    exibir_ranking();

    free(stats);

    keyboardDestroy();
    screenDestroy();

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/game.h"
#include "../include/ranking.h"
#include "../include/utils.h"

void exibirMenu() {
    limparTela();
    printf("🐸 JOGO FROGGER - CLI 🐸\n\n");
    printf("1. Iniciar Jogo\n");
    printf("2. Ver Ranking\n");
    printf("3. Sair\n");
    printf("\nEscolha uma opção: ");
}

int main() {
    int opcao;
    srand(time(NULL));

    inicializarRanking();

    while (1) {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // Limpa buffer

        switch (opcao) {
            case 1:
                limparTela();
                iniciarJogo();
                break;
            case 2:
                limparTela();
                exibirRanking();
                printf("\nPressione ENTER para voltar ao menu...");
                getchar();
                break;
            case 3:
                salvarRanking();
                printf("Saindo do jogo...\n");
                exit(0);
            default:
                printf("Opção inválida! Pressione ENTER para continuar...");
                getchar();
                break;
        }
    }

    return 0;
}

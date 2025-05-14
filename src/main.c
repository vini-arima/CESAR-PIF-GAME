#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/game.h"
#include "../include/ranking.h"
#include "../include/utils.h"
#include "../include/screen.h"

void imprimirTitulo() {
    screenSetColor(LIGHTGREEN, -1);  // Título verde claro sem fundo
    screenGotoxy(MINX+10, MINY+2);
    printf("███████╗██████╗  ██████╗  ██████╗  ██████╗ ███████╗██████╗ ");
    screenGotoxy(MINX+10, MINY+3);
    printf("██╔════╝██╔══██╗██╔═══██╗██╔════╝ ██╔════╝ ██╔════╝██╔══██╗");
    screenGotoxy(MINX+10, MINY+4);
    printf("█████╗  ██████╔╝██║   ██║██║  ███╗██║  ███╗█████╗  ██████╔╝");
    screenGotoxy(MINX+10, MINY+5);
    printf("██╔══╝  ██╔══██╗██║   ██║██║   ██║██║   ██║██╔══╝  ██╔══██╗");
    screenGotoxy(MINX+10, MINY+6);
    printf("██║     ██║  ██║╚██████╔╝╚██████╔╝╚██████╔╝███████╗██║  ██║");
    screenGotoxy(MINX+10, MINY+7);
    printf("╚═╝     ╚═╝  ╚═╝ ╚═════╝  ╚═════╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝");
    screenSetNormal();
}

void imprimirSapo() {
    screenSetNormal();  // Sapo na cor padrão
    screenGotoxy(MINX+19, MINY+12);
    printf("              _         _");
    screenGotoxy(MINX+19, MINY+13);
    printf("  __   ___.--'_`.     .'_`--.___   __");
    screenGotoxy(MINX+19, MINY+14);
    printf(" ( _`.'. -   'o` )   ( 'o`   - .`.'_ )");
    screenGotoxy(MINX+19, MINY+15);
    printf(" _\\.'_'      _.-'     `-._      `_`./_");
    screenGotoxy(MINX+19, MINY+16);
    printf("( \\`. )    //\\`         '/\\\\    ( .'/ )");
    screenGotoxy(MINX+19, MINY+17);
    printf(" \\_`-'`---'\\\\__,       ,__//`---'`-'_/");
    screenGotoxy(MINX+19, MINY+18);
    printf("  \\`        `-\\         /-'        '/");
    screenGotoxy(MINX+19, MINY+19);
    printf("   `                               '");
}

void exibirMenu() {
    screenInit(1);  // Inicializa com bordas
    
    imprimirTitulo();
    
    // Opções do menu com números amarelos
    screenGotoxy(MINX+30, MINY+9);
    screenSetColor(YELLOW, -1);
    printf("1. Iniciar Jogo 🎮");
    
    screenGotoxy(MINX+30, MINY+10);
    screenSetColor(YELLOW, -1);
    printf("2. Ver Ranking 🏆");
    
    screenGotoxy(MINX+30, MINY+11);
    screenSetColor(YELLOW, -1);
    printf("3. Sair 🚪");
    
    imprimirSapo();
    
    screenGotoxy(MINX+29, MINY+21);
    screenSetColor(LIGHTCYAN, -1);
    printf("Escolha uma opção: ");
    screenShowCursor();
}

int main() {
    int opcao;
    srand(time(NULL));
    inicializarRanking();

    while (1) {
        exibirMenu();
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
        }
        getchar();

        switch (opcao) {
            case 1:
                screenClear();
                iniciarJogo();
                break;
            case 2:
                screenClear();
                exibirRanking();
                screenGotoxy(MINX+15, MAXY-2);
                printf("Pressione ENTER para voltar...");
                while (getchar() != '\n');
                break;
            case 3:
                salvarRanking();
                screenGotoxy(MINX+25, MAXY-2);
                printf("Até logo! 👋");
                screenDestroy();
                exit(0);
            default:
                screenGotoxy(MINX+15, MAXY-2);
                printf("Opção inválida! Pressione ENTER...");
                while (getchar() != '\n');
                break;
        }
    }
    return 0;
}

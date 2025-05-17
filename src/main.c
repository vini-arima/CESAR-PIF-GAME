#include <stdio.h>      // Entrada e saída padrão
#include <stdlib.h>     // Funções gerais: malloc, free, exit, srand, etc
#include <time.h>       // Para inicializar a seed do rand()
#include "../include/game.h"      // Protótipos e funções do jogo principal
#include "../include/ranking.h"   // Funções para salvar e mostrar ranking
#include "../include/utils.h"     // Funções utilitárias como limpar tela etc
#include "../include/screen.h"    // Controle do terminal (cores, cursor, etc)

// Função que imprime o título do jogo em ASCII art colorido
void imprimirTitulo() {
    screenSetColor(LIGHTGREEN, -1);     // Define a cor do texto para verde claro, fundo transparente
    screenGotoxy(MINX+10, MINY+2);      // Posiciona cursor no terminal (coluna, linha)
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
    screenSetNormal();                  // Reseta formatação de texto para normal
}

// Função que imprime a arte ASCII do sapo no terminal
void imprimirSapo() {
    screenSetNormal();                  // Garante texto normal sem formatação
    screenGotoxy(MINX+19, MINY+12);
    printf("              _         _");
    screenGotoxy(MINX+19, MINY+13);
    printf("  __   ___.--'_`.     .'_`--.___   __");
    screenGotoxy(MINX+19, MINY+14);
    printf(" ( _`.'. -   'o` )   ( 'o`   - .`.'_ )");
    screenGotoxy(MINX+19, MINY+15);
    printf(" _\\.'_'      _.-'     `-._      `_`./_");
    screenGotoxy(MINX+19, MINY+16);
    printf("( \\`. )    //\\`         '/\\    ( .'/ )");
    screenGotoxy(MINX+19, MINY+17);
    printf(" \\_`-'`---'\\__,       ,__//`---'`-'_/");
    screenGotoxy(MINX+19, MINY+18);
    printf("  \\`        `-\\         /-'        '/'");
    screenGotoxy(MINX+19, MINY+19);
    printf("   `                               '");
}

// Função que exibe o menu principal do jogo com opções e título
void exibirMenu() {
    screenInit(1);                     // Inicializa tela, limpa e desenha bordas
    imprimirTitulo();                  // Chama função que imprime o título

    // Imprime opção 1 do menu
    screenGotoxy(MINX+30, MINY+9);
    screenSetColor(YELLOW, -1);
    printf("1. Iniciar Jogo 🎮");

    // Opção 2 do menu
    screenGotoxy(MINX+30, MINY+10);
    screenSetColor(YELLOW, -1);
    printf("2. Ver Ranking 🏆");

    // Opção 3 do menu
    screenGotoxy(MINX+30, MINY+11);
    screenSetColor(YELLOW, -1);
    printf("3. Sair 🚪");

    imprimirSapo();                   // Imprime a arte do sapo na tela

    // Pede para o usuário escolher uma opção
    screenGotoxy(MINX+29, MINY+21);
    screenSetColor(LIGHTCYAN, -1);
    printf("Escolha uma opção: ");
    screenShowCursor();               // Mostra o cursor para digitação
}

// Função para entrada segura do nome do jogador
void obterNomeJogador(char nome[]) {
    screenClear();                   // Limpa a tela
    screenGotoxy(MINX + 20, MINY + 5);
    screenSetColor(LIGHTCYAN, -1);
    printf("Digite seu nome: ");     // Solicita que usuário digite o nome
    screenSetNormal();

    fgets(nome, 50, stdin);          // Lê string com limite de 49 chars + \0
    nome[strcspn(nome, "\n")] = '\0'; // Remove o '\n' do final da string

    // Se o usuário não digitou nada, define nome padrão
    if (strlen(nome) == 0) {
        strncpy(nome, "Jogador", 49);
        nome[49] = '\0';
    }
}

// Função para ler a opção do menu de forma segura e tratar erros
int lerOpcao() {
    int opcao;
    if (scanf("%d", &opcao) != 1) {  // Tenta ler um inteiro
        while (getchar() != '\n');   // Limpa buffer se input inválido
        return -1;                   // Retorna valor inválido para tratar depois
    }
    getchar();                      // Consome o '\n' pendente após scanf
    return opcao;                   // Retorna opção válida
}

int main() {
    int opcao;                      // Variável para guardar a opção do menu
    char nome[50];                  // Buffer para guardar o nome do jogador
    srand(time(NULL));              // Inicializa seed para números aleatórios
    inicializarRanking();           // Inicializa sistema de ranking

    while (1) {                    // Loop infinito para exibir menu até sair
        exibirMenu();              // Exibe o menu na tela
        opcao = lerOpcao();        // Lê a opção digitada pelo usuário

        switch (opcao) {
            case 1:
                obterNomeJogador(nome); // Solicita e lê nome do jogador
                iniciarJogo(nome);      // Inicia o jogo com esse nome
                break;

            case 2:
                screenClear();          // Limpa a tela antes de mostrar ranking
                mostrarRanking();      // Chama função para mostrar o ranking
                break;

            case 3:
                screenGotoxy(MINX+25, MAXY-2);
                printf("Até logo! 👋"); // Mensagem de saída
                screenDestroy();         // Restaura terminal ao estado inicial
                exit(0);                 // Encerra o programa com sucesso

            default:
                // Caso a opção digitada seja inválida
                screenGotoxy(MINX+15, MAXY-2);
                printf("Opção inválida! Pressione ENTER...");
                while (getchar() != '\n'); // Espera o usuário pressionar Enter
                break;
        }
    }
    return 0; // nunca chega aqui pois tem loop infinito e exit
}

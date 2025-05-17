#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"
#include "screen.h"
#include "utils.h"

#define ARQUIVO_RANKING "ranking.txt"  // Nome do arquivo que armazena o ranking
#define MAX_LINHA 100                  // Tamanho máximo da linha lida do arquivo
#define MAX_JOGADORES 100              // Número máximo de jogadores a serem carregados do arquivo

// Função usada pelo qsort para ordenar jogadores pela pontuação (decrescente)
int compararPontuacao(const void* a, const void* b) {
    int pa = ((JogadorRanking*)a)->pontos;
    int pb = ((JogadorRanking*)b)->pontos;

    if (pb > pa) return 1;
    if (pb < pa) return -1;
    return 0;
}

// Salva a pontuação do jogador no arquivo de ranking, se a pontuação for maior que zero
void salvarPontuacao(const char* nome, int pontos) {
    if (pontos <= 0) return;  // Ignora pontuação inválida

    FILE* f = fopen(ARQUIVO_RANKING, "a");  // Abre arquivo para acrescentar dados
    if (!f) {
        // Se falhar ao abrir, pode logar erro aqui ou simplesmente retornar
        return;
    }

    // Grava linha com o formato: "Nome do jogador" pontos
    fprintf(f, "\"%s\" %d\n", nome, pontos);
    fclose(f);
}

// Exibe o ranking na tela, ordenado pelos melhores pontos
void mostrarRanking() {
    FILE* f = fopen(ARQUIVO_RANKING, "r");
    if (!f) {
        // Se não existe o arquivo, cria um arquivo vazio para evitar erros futuros
        f = fopen(ARQUIVO_RANKING, "w");
        if (f) fclose(f);
        return;
    }

    JogadorRanking jogadores[MAX_JOGADORES];
    int count = 0;
    char linha[MAX_LINHA];

    // Lê o arquivo linha a linha, até preencher o array ou acabar o arquivo
    while (fgets(linha, sizeof(linha), f) && count < MAX_JOGADORES) {
        char nome[TAM_NOME];
        int pontos;

        // Faz parsing da linha no formato esperado: "Nome" pontos
        // %49[^\"] lê até 49 caracteres até encontrar aspas (protege buffer)
        if (sscanf(linha, "\"%49[^\"]\" %d", nome, &pontos) == 2) {
            // Copia o nome para o struct, garantindo terminação nula
            strncpy(jogadores[count].nome, nome, TAM_NOME - 1);
            jogadores[count].nome[TAM_NOME - 1] = '\0';
            jogadores[count].pontos = pontos;
            count++;
        }
        // Se linha estiver mal formatada, simplesmente ignora
    }
    fclose(f);

    // Ordena o array pelo campo 'pontos' de forma decrescente
    qsort(jogadores, count, sizeof(JogadorRanking), compararPontuacao);

    // Limpa a tela antes de mostrar o ranking
    screenClear();

    const int coluna = 10;  // Coluna fixa para alinhamento da lista

    // Imprime título do ranking com cor amarela
    screenGotoxy(coluna, 3);
    screenSetColor(YELLOW, -1);
    printf(" 🏆 TOP 10 RANKING 🏆 ");

    // Define quantos jogadores mostrar (máximo 10)
    int maxToShow = (count > 10) ? 10 : count;

    // Imprime lista do ranking com medalhas para os 3 primeiros
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

        // Nome alinhado à esquerda, pontuação à direita
        printf("%-15s%5d pts", jogadores[i].nome, jogadores[i].pontos);
    }

    // Mensagem para o usuário pressionar ENTER para voltar (cor azul claro)
    screenGotoxy(coluna, 5 + maxToShow + 2);
    screenSetColor(LIGHTBLUE, -1);
    printf("Pressione ENTER para voltar...");
    screenSetNormal();

    fflush(stdout);

    // Espera o ENTER para voltar (consome qualquer outra tecla até o ENTER)
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


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "game.h"
#include "map.h"
#include "player.h"
#include "utils.h"
#include "ranking.h"
#include "obstacles.h"

#define FRAME_DELAY_MS 100

static struct termios original_termios;

void iniciarJogo() {
    char nome[50] = "Jogador";

    Player* jogador = criarPlayer(nome);
    Mapa* mapa = criarMapa();

    jogador->x = mapa->largura / 2;
    jogador->y = mapa->altura - 1;

    struct termios newt;
    tcgetattr(STDIN_FILENO, &original_termios);
    newt = original_termios;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    long last_update = get_current_time_ms();

    while (jogador->vidas > 0) {
        long now = get_current_time_ms();

        if (kbhit()) {
            char input = getchar();
            moverPlayer(jogador, input, mapa->largura, mapa->altura);
        }

        if (now - last_update >= FRAME_DELAY_MS) {
            atualizarMapa(mapa);
            atualizarBuff(jogador);

            int inv = jogador->ativoBuff == 1;
            int colidiu = verificarColisaoComObstaculoMapa(mapa, jogador->x, jogador->y, inv);
            if (colidiu && !inv && jogador->cooldownDano <= 0) {
                jogador->vidas--;
                jogador->cooldownDano = 10;
                jogador->x = mapa->largura / 2;
                jogador->y = mapa->altura - 1;
            }

            if (mapa->buffAtual.ativo &&
                jogador->x == mapa->buffAtual.x &&
                jogador->y == mapa->buffAtual.y) {
                jogador->ativoBuff = mapa->buffAtual.tipo;
                jogador->tempoBuff = 60;
                mapa->buffAtual.ativo = 0;
            }

            if (jogador->y == 0) {
                avancarFase(mapa, jogador);
            }

            renderizarMapa(mapa, jogador);
            last_update = now;
        }

        usleep(10000);
    }

    renderizarMapa(mapa, jogador);
    printf("\n💀 Fim de jogo! Pontuação: %d\n", jogador->pontos);
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n');
    getchar();

    salvarPontuacao(jogador->nome, jogador->pontos);
    destruirMapa(mapa);
    destruirPlayer(jogador);
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}

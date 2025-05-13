#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "map.h" // para ALTURA_MAPA, LARGURA_MAPA

Player* criarPlayer(const char* nome) {
    Player* jogador = malloc(sizeof(Player));
    strncpy(jogador->nome, nome, 49);
    jogador->nome[49] = '\0';

    jogador->x = 0;
    jogador->y = 0;
    jogador->vidas = 3;
    jogador->pontos = 0;
    jogador->ativoBuff = 0;
    jogador->tempoBuff = 0;
    jogador->cooldownDano = 0;

    return jogador;
}


void destruirPlayer(Player* jogador) {
    if (jogador) {
        free(jogador);
    }
}

void moverPlayer(Player* p, char direcao, int limiteX, int limiteY) {
    switch (direcao) {
        case 'w':
        case 'W':
            if (p->y > 0) {
                p->y--;
                p->pontos += (p->ativoBuff == 2) ? 2 : 1;
            }
            break;
        case 'a':
        case 'A':
            if (p->x > 0) p->x--;
            break;
        case 'd':
        case 'D':
            if (p->x < limiteX - 1) p->x++;
            break;
    }
}
void atualizarBuff(Player* p) {
    if (p->ativoBuff != 0) {
        p->tempoBuff--;
        if (p->tempoBuff <= 0) {
            p->ativoBuff = 0;
        }
    }
    if (p->cooldownDano > 0) {
        p->cooldownDano--;
    }
}


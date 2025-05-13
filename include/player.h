#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char nome[50];
    int x, y;
    int vidas;
    int pontos;
    int ativoBuff;
    int tempoBuff;
    int cooldownDano;  // <- adicione esse campo
} Player;

Player* criarPlayer(const char* nome);
void destruirPlayer(Player* p);
void moverPlayer(Player* p, char direcao, int limiteX, int limiteY);
void atualizarBuff(Player* p);
void moverPlayer(Player* p, char direcao, int limiteX, int limiteY);
void atualizarBuff(Player* p);


#endif

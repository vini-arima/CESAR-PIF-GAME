#ifndef PLAYER_H
#define PLAYER_H

#define TAM_NOME 50
#define VIDAS_INICIAIS 3
#define BUFF_INVENCIVEL 1
#define BUFF_DOBRA_PONTOS 2

typedef struct {
    char nome[TAM_NOME];
    int x, y;
    int vidas;
    int pontos;
    int ativoBuff;
    int tempoBuff;
    int cooldownDano;
    int faseAtual;
    int invencivel; // Novo campo para estado invencível
} Player;

Player* criarPlayer(const char* nome);
void destruirPlayer(Player* p);
void moverPlayer(Player* p, char direcao, int limiteX, int limiteY);
void atualizarBuff(Player* p);
void finalizarJogo(Player* p);
void aplicarBuff(Player* p, int tipoBuff, int duracao); // Nova função
void tomarDano(Player* p); // Nova função
#endif
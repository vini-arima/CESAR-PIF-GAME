
#ifndef PLAYER_H
#define PLAYER_H


#define TAM_NOME 50


#define VIDAS_INICIAIS 3


#define BUFF_INVENCIVEL 1     // Buff que impede o jogador de tomar dano
#define BUFF_DOBRA_PONTOS 2   // Buff que dobra os pontos adquiridos


typedef struct {
    char nome[TAM_NOME]; 
    int x, y;            
    int vidas;           
    int pontos;           
    int ativoBuff;        
    int tempoBuff;        
    int cooldownDano;    
    int faseAtual;       
    int invencivel;       
} Player;


Player* criarPlayer(const char* nome);


void destruirPlayer(Player* p);


void moverPlayer(Player* p, char direcao, int limiteX, int limiteY);


void atualizarBuff(Player* p);


void finalizarJogo(Player* p);


void aplicarBuff(Player* p, int tipoBuff, int duracao);


void tomarDano(Player* p);

#endif

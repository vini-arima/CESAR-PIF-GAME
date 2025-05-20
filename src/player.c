#include <stdlib.h>      
#include <string.h>      
#include "player.h"      
#include "map.h"         
#include "ranking.h"    
#include "screen.h"      


Player* criarPlayer(const char* nome) {
    Player* jogador = malloc(sizeof(Player));   
    if (!jogador) return NULL;                  

   
    strncpy(jogador->nome, nome, TAM_NOME-1);
    jogador->nome[TAM_NOME-1] = '\0';

    jogador->faseAtual = 1;         
    jogador->x = 0;                 
    jogador->y = 0;                 
    jogador->vidas = VIDAS_INICIAIS; 
    jogador->pontos = 0;             
    jogador->ativoBuff = 0;          
    jogador->tempoBuff = 0;          
    jogador->cooldownDano = 0;       
    jogador->invencivel = 0;         

    return jogador;                 
}


void destruirPlayer(Player* jogador) {
    free(jogador); 
}


void moverPlayer(Player* p, char direcao, int limiteX, int limiteY) {
    if (!p) return;

    switch (direcao) {
        case 'w': case 'W':
            if (p->y > 0) {
                p->y--; 
                
                p->pontos += (p->ativoBuff == BUFF_DOBRA_PONTOS) ? 2 : 1;
            }
            break;
        case 'a': case 'A':
            if (p->x > 0) p->x--;
            break;
        case 'd': case 'D': 
            if (p->x < limiteX - 1) p->x++;
            break;
    }
}


void aplicarBuff(Player* p, int tipoBuff, int duracao) {
    if (!p) return;

    p->ativoBuff = tipoBuff;    
    p->tempoBuff = duracao;    

   
    if (tipoBuff == BUFF_INVENCIVEL) {
        p->invencivel = 1;
    }
}


void tomarDano(Player* p) {
    if (!p || p->invencivel || p->cooldownDano > 0) return;

    p->vidas--;             
    p->cooldownDano = 3;   

    if (p->vidas <= 0) {
        finalizarJogo(p);   
    }
}


void atualizarBuff(Player* p) {
    if (!p) return;

    
    if (p->ativoBuff != 0) {
        p->tempoBuff--;
        if (p->tempoBuff <= 0) {
            p->ativoBuff = 0;    
            p->invencivel = 0;   
        }
    }

   
    if (p->cooldownDano > 0) {
        p->cooldownDano--;
    }
}


void finalizarJogo(Player* p) {
    if (!p) return;

    if (p->pontos > 0) {
        salvarPontuacao(p->nome, p->pontos); 
    }

  
}

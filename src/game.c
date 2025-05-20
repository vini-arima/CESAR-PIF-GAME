#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>          
#include <sys/time.h>        
#include "game.h"
#include "map.h"
#include "player.h"
#include "utils.h"
#include "ranking.h"
#include "obstacles.h"
#include "keyboard.h"        

#define FRAME_DELAY_MS 100   
#define W_COOLDOWN_MS 65     


void iniciarJogo(const char* nome) {
    
    
    Player* jogador = criarPlayer(nome);
    Mapa* mapa = criarMapa();

    
    jogador->x = mapa->largura / 2;
    jogador->y = mapa->altura - 1;

    
    keyboardInit(); 

    long last_update = get_current_time_ms();   
    long last_w_press = 0;                      
    int w_cooldown = 0;                         

    
    while (jogador->vidas > 0) {
        long now = get_current_time_ms();       

        
        if (keyhit()) {                         
            char input = readch();              

            
            if (input == 'w' || input == 'W') {
                if (!w_cooldown) {
                    moverPlayer(jogador, input, mapa->largura, mapa->altura); 
                    last_w_press = now;    
                    w_cooldown = 1;        
                }
            } else {
                
                if (input == 'a' || input == 'A' || 
                    input == 'd' || input == 'D') {
                    moverPlayer(jogador, input, mapa->largura, mapa->altura);
                }
            }
        }

        
        if (w_cooldown && (now - last_w_press >= W_COOLDOWN_MS)) {
            w_cooldown = 0;
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
    renderizarMapa(mapa, jogador);

    
    printf("\033[%d;1H", mapa->altura + 3); 
    printf("💀 Fim de jogo! Pontuação: %d\n", jogador->pontos);
    printf("Pressione Enter para continuar...");
    fflush(stdout); 
    while (readch() != '\n'); 

    
    salvarPontuacao(jogador->nome, jogador->pontos);

    
    destruirMapa(mapa);
    destruirPlayer(jogador);
    keyboardDestroy(); 
}

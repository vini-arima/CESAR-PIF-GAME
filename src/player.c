#include <stdlib.h>      // malloc, free
#include <string.h>      // strncpy
#include "player.h"      // definição da struct Player e constantes como TAM_NOME, VIDAS_INICIAIS etc
#include "map.h"         // definição da struct Mapa (provavelmente usada em outro lugar)
#include "ranking.h"     // função salvarPontuacao
#include "screen.h"      // para efeitos visuais ou sonoros (comentado no final)

// Cria e inicializa um novo jogador com nome dado
Player* criarPlayer(const char* nome) {
    Player* jogador = malloc(sizeof(Player));   // aloca memória para Player
    if (!jogador) return NULL;                   // retorna NULL se falhar alocação

    // copia o nome para o campo nome, garantindo que termine com '\0' e não ultrapasse TAM_NOME-1
    strncpy(jogador->nome, nome, TAM_NOME-1);
    jogador->nome[TAM_NOME-1] = '\0';

    jogador->faseAtual = 1;          // inicia na fase 1
    jogador->x = 0;                  // posição inicial x (esquerda)
    jogador->y = 0;                  // posição inicial y (topo)
    jogador->vidas = VIDAS_INICIAIS; // vidas iniciais (constante)
    jogador->pontos = 0;             // pontuação inicial 0
    jogador->ativoBuff = 0;          // nenhum buff ativo
    jogador->tempoBuff = 0;          // tempo do buff zerado
    jogador->cooldownDano = 0;       // cooldown de dano zerado (pode receber dano)
    jogador->invencivel = 0;         // não está invencível inicialmente

    return jogador;                  // retorna ponteiro para jogador criado
}

// Libera a memória do jogador
void destruirPlayer(Player* jogador) {
    free(jogador); // safe para NULL, simplesmente libera a memória
}

// Move o jogador em uma direção dada, respeitando limites da tela/mapa
void moverPlayer(Player* p, char direcao, int limiteX, int limiteY) {
    if (!p) return; // segurança: não faz nada se p for NULL

    switch (direcao) {
        case 'w': case 'W': // para cima
            if (p->y > 0) {
                p->y--; // sobe uma linha
                // Se estiver com buff que dobra pontos, ganha 2 pontos, senão 1 ponto
                p->pontos += (p->ativoBuff == BUFF_DOBRA_PONTOS) ? 2 : 1;
            }
            break;
        case 'a': case 'A': // esquerda
            if (p->x > 0) p->x--;
            break;
        case 'd': case 'D': // direita
            if (p->x < limiteX - 1) p->x++;
            break;
    }
}

// Aplica um buff (tipoBuff) por certa duração (duracao) ao jogador
void aplicarBuff(Player* p, int tipoBuff, int duracao) {
    if (!p) return;

    p->ativoBuff = tipoBuff;    // define o tipo de buff ativo
    p->tempoBuff = duracao;     // define por quanto tempo o buff vai durar

    // Se o buff for invencibilidade, ativa flag invencível
    if (tipoBuff == BUFF_INVENCIVEL) {
        p->invencivel = 1;
    }
}

// Jogador toma dano, desconta vida se não estiver invencível ou no cooldown
void tomarDano(Player* p) {
    if (!p || p->invencivel || p->cooldownDano > 0) return; // ignora se invencível ou em cooldown

    p->vidas--;             // perde uma vida
    p->cooldownDano = 3;    // ativa cooldown de dano por 3 frames (para evitar dano rápido demais)

    if (p->vidas <= 0) {
        finalizarJogo(p);    // finaliza jogo se sem vidas
    }
}

// Atualiza timers de buffs e cooldowns a cada frame
void atualizarBuff(Player* p) {
    if (!p) return;

    // Se houver buff ativo, decrementa o tempo restante
    if (p->ativoBuff != 0) {
        p->tempoBuff--;
        if (p->tempoBuff <= 0) {
            p->ativoBuff = 0;    // desativa buff ao acabar o tempo
            p->invencivel = 0;   // desativa invencibilidade também se buff era esse
        }
    }

    // Decrementa cooldown de dano, se ativo
    if (p->cooldownDano > 0) {
        p->cooldownDano--;
    }
}

// Finaliza o jogo, salva a pontuação do jogador se maior que zero
void finalizarJogo(Player* p) {
    if (!p) return;

    if (p->pontos > 0) {
        salvarPontuacao(p->nome, p->pontos); // salva pontuação no ranking
    }

    // Pode adicionar aqui efeitos visuais/sonoros de fim de jogo
}

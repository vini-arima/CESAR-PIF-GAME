#ifndef GAME_H
#define GAME_H

#include "obstacles.h"
#include "map.h"
#include "player.h"

void iniciarJogo();
void loopJogo(Mapa* mapa, Player* jogador);
void processarEntrada(char input, Player* jogador, Mapa* mapa);
int verificarColisoes(Mapa* mapa, Player* jogador);

#endif

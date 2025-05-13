#ifndef MAP_H
#define MAP_H

#include "player.h"
#include "obstacles.h"

#define MAX_OBSTACULOS 100

typedef enum {
    RUA,
    CAMPO_VERDE
} TipoTerreno;

typedef struct {
    int ativo;
    int tipo; // 1 = Invencibilidade, 2 = Dobra Pontos
    int x, y;
} Buff;

typedef struct Mapa {
    int altura;
    int largura;
    TipoTerreno* linhas;
    Obstaculo** obstaculos;
    int numObstaculos;

    Buff buffAtual;
    int fasesDesdeUltimoBuff;
} Mapa;

TipoTerreno tipoTerrenoLinha(Mapa* m, int linha);
Mapa* criarMapa();
void gerarLinha(Mapa* m, int linha);
void gerarObstaculos(Mapa* m);
void atualizarMapa(Mapa* m);
void avancarFase(Mapa* m, Player* p);
void renderizarMapa(Mapa* m, Player* p);
void destruirMapa(Mapa* m);

#endif


#ifndef OBSTACLES_H
#define OBSTACLES_H


struct Mapa;
typedef struct Mapa Mapa;

typedef enum {
    COBRA,
    TRONCO
} TipoObstaculo;


typedef struct Obstaculo {
    int x, y;
    int ativo;
    int largura;
    int velocidade;
    int frameDelay;
    TipoObstaculo tipo;
} Obstaculo;


Obstaculo* criarObstaculo(int y, TipoObstaculo tipo, int largura_max);


void atualizarObstaculo(Obstaculo* o);
void destruirObstaculo(Obstaculo* o);


const char* emojiObstaculo(TipoObstaculo tipo);


int verificarColisaoComObstaculoMapa(Mapa* mapa, int x, int y, int invencivel);

#endif

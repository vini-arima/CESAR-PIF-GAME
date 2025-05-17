#include <stdlib.h>     // malloc, free
#include <string.h>     // funções para strings, não usado diretamente aqui, mas incluído
#include "obstacles.h"  // definição da struct Obstaculo e enum TipoObstaculo
#include "map.h"        // definição da struct Mapa

// Cria um novo obstáculo na linha y, com tipo especificado, posicionado no lado direito do mapa
Obstaculo* criarObstaculo(int y, TipoObstaculo tipo, int largura_max) {
    Obstaculo* o = malloc(sizeof(Obstaculo));  // Aloca memória para o obstáculo
    if (!o) return NULL;                        // Retorna NULL se falhar

    o->tipo = tipo;               // Define tipo (CARRO ou TRONCO)
    o->y = y;                     // Linha do obstáculo
    o->x = largura_max - 1;       // Começa na última coluna (extremo direito)
    o->ativo = 1;                 // Obstáculo está ativo
    o->largura = 1;               // Largura do obstáculo (1 célula)
    o->velocidade = 1;            // Velocidade de movimento (1 célula por atualização)
    o->frameDelay = 0;            // Contador para controlar movimento a cada 2 frames

    return o;                     // Retorna ponteiro para obstáculo criado
}

// Atualiza posição do obstáculo
void atualizarObstaculo(Obstaculo* o) {
    o->frameDelay++;              // Incrementa contador de frames
    if (o->frameDelay >= 2) {     // Só move a cada 2 frames para desacelerar movimento
        o->x -= o->velocidade;    // Move obstáculo uma célula para a esquerda
        o->frameDelay = 0;        // Reseta contador de frames
    }

    if (o->x < 0) {               // Se obstáculo saiu da tela (coluna < 0)
        o->ativo = 0;             // Marca obstáculo como inativo (para remoção)
    }
}

// Libera a memória alocada para o obstáculo
void destruirObstaculo(Obstaculo* o) {
    if (o) free(o);               // Só libera se o ponteiro não for NULL
}

// Retorna emoji para representar o obstáculo no terminal (usado para renderizar)
const char* emojiObstaculo(TipoObstaculo tipo) {
    return (tipo == CARRO) ? "🐍" : "🪵";   // Cobra para carro, tronco para tronco
}

// Verifica se a posição (x,y) no mapa colide com algum obstáculo ativo
// Se o jogador estiver invencível, retorna 0 (sem colisão)
int verificarColisaoComObstaculoMapa(Mapa* mapa, int x, int y, int invencivel) {
    if (invencivel) return 0;     // Ignora colisão se invencível

    // Percorre todos os obstáculos ativos no mapa
    for (int i = 0; i < mapa->numObstaculos; i++) {
        Obstaculo* o = mapa->obstaculos[i];
        if (!o || !o->ativo) continue;   // Pula obstáculos nulos ou inativos

        // Se algum obstáculo está na mesma posição (x,y)
        if (y == o->y && x == o->x) {
            return 1;            // Colisão detectada
        }
    }

    return 0;                    // Sem colisão
}

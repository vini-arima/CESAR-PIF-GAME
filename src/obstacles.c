#include <stdlib.h>     
#include <string.h>     
#include "obstacles.h"  
#include "map.h"        


Obstaculo* criarObstaculo(int y, TipoObstaculo tipo, int largura_max) {
    Obstaculo* o = malloc(sizeof(Obstaculo));
    if (!o) return NULL;                        

    o->tipo = tipo;               
    o->y = y;                     
    o->x = largura_max - 1;       
    o->ativo = 1;                 
    o->largura = 1;               
    o->velocidade = 1;           
    o->frameDelay = 0;           

    return o;                     
}


void atualizarObstaculo(Obstaculo* o) {
    o->frameDelay++;              
    if (o->frameDelay >= 2) {     
        o->x -= o->velocidade;    
        o->frameDelay = 0;        
    }

    if (o->x < 0) {               
        o->ativo = 0;             
    }
}


void destruirObstaculo(Obstaculo* o) {
    if (o) free(o);              
}


const char* emojiObstaculo(TipoObstaculo tipo) {
    return (tipo == COBRA) ? "🐍" : "🪵";  
}



int verificarColisaoComObstaculoMapa(Mapa* mapa, int x, int y, int invencivel) {
    if (invencivel) return 0;     

   
    for (int i = 0; i < mapa->numObstaculos; i++) {
        Obstaculo* o = mapa->obstaculos[i];
        if (!o || !o->ativo) continue;   

        if (y == o->y && x == o->x) {
            return 1;        
        }
    }

    return 0;                    
}

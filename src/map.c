#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "map.h"
#include "utils.h"
#include "obstacles.h"
#include "screen.h"

#define COOLDOWN_MAX 3
int cooldownLinha[100];

Mapa* criarMapa() {
    Mapa* m = malloc(sizeof(Mapa));
    int termAltura, termLargura;
    getTerminalSize(&termAltura, &termLargura);

    int margemSuperior = 5;
    int margemInferior = 4;
    m->altura = termAltura - margemSuperior - margemInferior;
    if (m->altura > 20) m->altura = 20;
    m->largura = 20;
    m->linhas = malloc(sizeof(TipoTerreno) * m->altura);
    m->obstaculos = malloc(sizeof(Obstaculo*) * MAX_OBSTACULOS);
    m->numObstaculos = 0;
    m->fasesDesdeUltimoBuff = 0;
    m->buffAtual.ativo = 0;

    srand(time(NULL));
    for (int i = 0; i < m->altura; i++) {
        m->linhas[i] = (rand() % 2 == 0) ? CAMPO_VERDE : RUA;
        cooldownLinha[i] = 0;
    }

    return m;
}

void gerarLinha(Mapa* m, int linha) {
    m->linhas[linha] = (rand() % 2 == 0) ? CAMPO_VERDE : RUA;
    cooldownLinha[linha] = 0;
}

void gerarObstaculos(Mapa* m) {
    int geradosNoFrame = 0;
    const int maxPorFrame = 2;
    const int maxNoMapa = 25;

    if (m->numObstaculos >= maxNoMapa) return;

    for (int y = 1; y < m->altura - 1; y++) {
        if (cooldownLinha[y] > 0) {
            cooldownLinha[y]--;
            continue;
        }

        if ((rand() % 100) < 3 && m->numObstaculos < MAX_OBSTACULOS) {
            TipoTerreno terreno = m->linhas[y];
            TipoObstaculo tipo = (terreno == RUA) ? CARRO : TRONCO;

            Obstaculo* o = criarObstaculo(y, tipo, m->largura);
            if (o) {
                m->obstaculos[m->numObstaculos++] = o;
                cooldownLinha[y] = COOLDOWN_MAX;
                geradosNoFrame++;

                if (geradosNoFrame >= maxPorFrame) break;
            }
        }
    }
}

void atualizarMapa(Mapa* m) {
    for (int i = 0; i < m->numObstaculos; i++) {
        if (m->obstaculos[i]->ativo)
            atualizarObstaculo(m->obstaculos[i]);
    }

    int j = 0;
    for (int i = 0; i < m->numObstaculos; i++) {
        if (m->obstaculos[i]->ativo)
            m->obstaculos[j++] = m->obstaculos[i];
        else
            destruirObstaculo(m->obstaculos[i]);
    }
    m->numObstaculos = j;

    gerarObstaculos(m);
}

TipoTerreno tipoTerrenoLinha(Mapa* m, int linha) {
    return m->linhas[linha];
}

void avancarFase(Mapa* m, Player* p) {
    for (int i = 0; i < m->numObstaculos; i++) {
        if (m->obstaculos[i]->y == 0)
            m->obstaculos[i]->ativo = 0;
    }

    for (int i = 0; i < m->altura - 1; i++) {
        m->linhas[i] = m->linhas[i + 1];
        cooldownLinha[i] = cooldownLinha[i + 1];
    }

    gerarLinha(m, m->altura - 1);

    for (int i = 0; i < m->numObstaculos; i++) {
        m->obstaculos[i]->y--;
        if (m->obstaculos[i]->y < 0)
            m->obstaculos[i]->ativo = 0;
    }

    m->fasesDesdeUltimoBuff++;

    if (m->fasesDesdeUltimoBuff >= 3) {
        m->buffAtual.ativo = 1;
        m->buffAtual.tipo = (rand() % 2) ? 1 : 2;
        m->buffAtual.x = rand() % m->largura;
        m->buffAtual.y = rand() % (m->altura - 2) + 1;
        m->fasesDesdeUltimoBuff = 0;
    }

    p->x = m->largura / 2;
    p->y = m->altura - 1;
    p->pontos++;
    p->faseAtual++;
}

void renderizarMapa(Mapa* m, Player* p) {
    limparTela();

    
    int termAltura, termLargura;
    getTerminalSize(&termAltura, &termLargura);
    
    
    int larguraMapa = m->largura * 2;
    int offsetCentral = (termLargura - larguraMapa) / 2;

 
    char linha1[50], linha2[200];
    snprintf(linha1, sizeof(linha1), "Fase Atual: %d", p->faseAtual);
    
    if (p->ativoBuff == 1) {
        snprintf(linha2, sizeof(linha2), "🐸 %s | ❤️  Vidas: %d | ⭐ Pontos: %d | 🛡️ Invencibilidade (%ds)",
                p->nome, p->vidas, p->pontos, p->tempoBuff);
    } else if (p->ativoBuff == 2) {
        snprintf(linha2, sizeof(linha2), "🐸 %s | ❤️  Vidas: %d | ⭐ Pontos: %d | ✨ Dobra Pontos (%ds)",
                p->nome, p->vidas, p->pontos, p->tempoBuff);
    } else {
        snprintf(linha2, sizeof(linha2), "🐸 %s | ❤️  Vidas: %d | ⭐ Pontos: %d",
                p->nome, p->vidas, p->pontos);
    }

    
    screenSetColor(WHITE, BLACK);
    
    
    screenGotoxy(offsetCentral + (larguraMapa - strlen(linha1)) / 2, 1);
    printf("%s", linha1);
    
  
    screenGotoxy(offsetCentral + (larguraMapa ) / 26, 2);
    printf("%s", linha2);
    
    screenSetColor(LIGHTGRAY, -1);

  
    for (int y = 0; y < m->altura; y++) {
        screenGotoxy(offsetCentral, y + 4);
        
        TipoTerreno tipo = m->linhas[y];
        for (int x = 0; x < m->largura; x++) {
            int desenhado = 0;

            
            if (m->buffAtual.ativo && m->buffAtual.x == x && m->buffAtual.y == y) {
                if (tipo == RUA) {
                    if (m->buffAtual.tipo == 1)
                        printf("\033[33;42m🛡️ \033[0m");
                    else
                        printf("\033[33;42m✨\033[0m");
                } else {
                    if (m->buffAtual.tipo == 1)
                        printf("\033[34;44m🛡️ \033[0m");
                    else
                        printf("\033[34;44m✨\033[0m");
                }
                desenhado = 1;
            }


            for (int i = 0; !desenhado && i < m->numObstaculos; i++) {
                Obstaculo* o = m->obstaculos[i];
                if (o->x == x && o->y == y) {
                    if (tipo == RUA)
                        printf("\033[33;42m%s\033[0m", emojiObstaculo(o->tipo));
                    else        
                        printf("\033[34;44m%s \033[0m", emojiObstaculo(o->tipo));
                    desenhado = 1;
                }
            }

           
            if (!desenhado && x == p->x && y == p->y) {
                if (tipo == RUA)
                    printf("\033[33;42m🐸\033[0m");
                else
                    printf("\033[34;44m🐸\033[0m");
                desenhado = 1;
            }

           
            if (!desenhado) {
                if (tipo == RUA) {
                    if (y % 3 == 1)
                        printf("\033[90;42m──\033[0m");
                    else
                        printf("\033[33;42m  \033[0m");
                } else {
                    printf("\033[34;44m~~\033[0m");
                }
            }
        }
        printf("\n");
    }
}

void destruirMapa(Mapa* m) {
    for (int i = 0; i < m->numObstaculos; i++) {
        destruirObstaculo(m->obstaculos[i]);
    }
    free(m->linhas);
    free(m->obstaculos);
    free(m);
}

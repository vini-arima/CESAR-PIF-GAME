// Evita inclusões múltiplas do cabeçalho
#ifndef MAP_H
#define MAP_H

// Inclusão de dependências necessárias
#include "player.h"
#include "obstacles.h"

// Define o número máximo de obstáculos que podem existir no mapa
#define MAX_OBSTACULOS 100

// Enumeração que define os tipos de terreno possíveis em uma linha do mapa
typedef enum {
    RUA,         // Linha com obstáculos (por exemplo: carros)
    CAMPO_VERDE  // Linha segura onde o jogador pode descansar
} TipoTerreno;

// Estrutura que representa um buff temporário no jogo
typedef struct {
    int ativo;  // Indica se o buff está ativo (1) ou não (0)
    int tipo;   // Tipo do buff: 1 = Invencibilidade, 2 = Dobra Pontos
    int x, y;   // Posição do buff no mapa
} Buff;

// Estrutura que representa o mapa do jogo
typedef struct Mapa {
    int altura;                   // Quantidade de linhas do mapa
    int largura;                  // Quantidade de colunas do mapa
    TipoTerreno* linhas;         // Vetor com o tipo de cada linha (RUA ou CAMPO_VERDE)
    Obstaculo** obstaculos;      // Matriz de obstáculos posicionados no mapa
    int numObstaculos;           // Quantidade atual de obstáculos no mapa

    Buff buffAtual;              // Buff que está presente no mapa atualmente
    int fasesDesdeUltimoBuff;   // Contador de fases desde a última aparição de buff
} Mapa;

// Funções relacionadas à manipulação do mapa

// Retorna o tipo de terreno de uma linha específica
TipoTerreno tipoTerrenoLinha(Mapa* m, int linha);

// Cria e inicializa um novo mapa
Mapa* criarMapa();

// Gera uma nova linha no mapa com tipo e obstáculos apropriados
void gerarLinha(Mapa* m, int linha);

// Gera todos os obstáculos do mapa com base nas linhas
void gerarObstaculos(Mapa* m);

// Atualiza o estado do mapa, como o movimento de obstáculos
void atualizarMapa(Mapa* m);

// Avança para a próxima fase, atualizando o mapa e o jogador
void avancarFase(Mapa* m, Player* p);

// Exibe o mapa atual no terminal, incluindo jogador e obstáculos
void renderizarMapa(Mapa* m, Player* p);

// Libera toda a memória alocada para o mapa
void destruirMapa(Mapa* m);

#endif

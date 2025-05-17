// Previne múltiplas inclusões do cabeçalho
#ifndef OBSTACLES_H
#define OBSTACLES_H

// Declaração antecipada da struct Mapa para evitar dependência circular
struct Mapa;
typedef struct Mapa Mapa;

// Enumeração que define os tipos de obstáculos possíveis
typedef enum {
    CARRO,   // Obstáculo que provavelmente deve ser evitado
    TRONCO   // Pode ser usado como plataforma (como no Frogger clássico)
} TipoObstaculo;

// Estrutura que representa um obstáculo no mapa
typedef struct Obstaculo {
    int x, y;               // Posição do obstáculo no mapa
    int ativo;              // Indica se o obstáculo está ativo (1) ou não (0)
    int largura;            // Tamanho do obstáculo (quantos blocos ocupa na horizontal)
    int velocidade;         // Velocidade de deslocamento horizontal do obstáculo
    int frameDelay;         // Controla quantos frames esperar antes de mover (para regular a velocidade)
    TipoObstaculo tipo;     // Tipo do obstáculo: CARRO ou TRONCO
} Obstaculo;

// Cria e inicializa um novo obstáculo na linha y, do tipo especificado, respeitando a largura máxima
Obstaculo* criarObstaculo(int y, TipoObstaculo tipo, int largura_max);

// Atualiza a posição do obstáculo conforme sua velocidade e frameDelay
void atualizarObstaculo(Obstaculo* o);

// Libera a memória alocada para o obstáculo
void destruirObstaculo(Obstaculo* o);

// Retorna um emoji (ou string) representando visualmente o obstáculo, com base no tipo
const char* emojiObstaculo(TipoObstaculo tipo);

// Verifica se houve colisão entre o jogador (nas coordenadas x, y) e um obstáculo no mapa
// Considera se o jogador está invencível ou não
int verificarColisaoComObstaculoMapa(Mapa* mapa, int x, int y, int invencivel);

#endif

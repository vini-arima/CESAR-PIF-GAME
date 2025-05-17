// Previne múltiplas inclusões do mesmo cabeçalho
#ifndef PLAYER_H
#define PLAYER_H

// Define o tamanho máximo do nome do jogador
#define TAM_NOME 50

// Define o número de vidas iniciais que o jogador possui
#define VIDAS_INICIAIS 3

// Define os identificadores dos tipos de buffs disponíveis
#define BUFF_INVENCIVEL 1     // Buff que impede o jogador de tomar dano
#define BUFF_DOBRA_PONTOS 2   // Buff que dobra os pontos adquiridos

// Estrutura que representa o jogador
typedef struct {
    char nome[TAM_NOME];  // Nome do jogador
    int x, y;             // Posição atual no mapa (coordenadas)
    int vidas;            // Número de vidas restantes
    int pontos;           // Pontuação atual
    int ativoBuff;        // Tipo de buff ativo (0 = nenhum, 1 ou 2 conforme definido acima)
    int tempoBuff;        // Tempo restante de duração do buff
    int cooldownDano;     // Cooldown para evitar dano em intervalos muito curtos
    int faseAtual;        // Número da fase que o jogador está
    int invencivel;       // Estado de invencibilidade (1 = sim, 0 = não)
} Player;

// Cria e inicializa um novo jogador com o nome fornecido
Player* criarPlayer(const char* nome);

// Libera a memória alocada para o jogador
void destruirPlayer(Player* p);

// Move o jogador na direção fornecida ('W', 'A', 'S', 'D') respeitando os limites do mapa
void moverPlayer(Player* p, char direcao, int limiteX, int limiteY);

// Atualiza o estado do buff ativo (reduz tempo, desativa se necessário)
void atualizarBuff(Player* p);

// Finaliza o jogo (pode ser usada para mostrar pontuação ou mensagem final)
void finalizarJogo(Player* p);

// Aplica um buff ao jogador com tipo e duração específicos
void aplicarBuff(Player* p, int tipoBuff, int duracao);

// Aplica dano ao jogador (reduz vida, ativa cooldown, etc.)
void tomarDano(Player* p);

#endif

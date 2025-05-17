#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>          // Para usleep e manipulação do terminal
#include <termios.h>         // Para configurar entrada do teclado
#include <fcntl.h>           // Para kbhit (tecla sem bloqueio)
#include <sys/time.h>        // Para controle de tempo com gettimeofday
#include "game.h"
#include "map.h"
#include "player.h"
#include "utils.h"
#include "ranking.h"
#include "obstacles.h"

#define FRAME_DELAY_MS 100   // Intervalo de atualização do jogo (100ms por frame)
#define W_COOLDOWN_MS 65     // Delay para evitar múltiplos 'w' seguidos

static struct termios original_termios; // Para armazenar configuração original do terminal

// Função principal que executa o loop do jogo
void iniciarJogo(const char* nome) {
    // Cria o jogador e o mapa do jogo
    Player* jogador = criarPlayer(nome);
    Mapa* mapa = criarMapa();

    // Posiciona o jogador no meio da parte inferior do mapa
    jogador->x = mapa->largura / 2;
    jogador->y = mapa->altura - 1;

    // Configura o terminal para modo não-canônico (leitura de tecla sem ENTER)
    struct termios newt;
    tcgetattr(STDIN_FILENO, &original_termios); // Salva configurações atuais
    newt = original_termios;
    newt.c_lflag &= ~(ICANON | ECHO);           // Desativa entrada canônica e eco de caracteres
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);    // Aplica nova configuração

    long last_update = get_current_time_ms();   // Armazena tempo do último frame
    long last_w_press = 0;                      // Tempo do último 'w' pressionado
    int w_cooldown = 0;                         // Flag para controle do cooldown de 'w'

    // Loop principal do jogo, termina quando jogador fica sem vidas
    while (jogador->vidas > 0) {
        long now = get_current_time_ms();       // Tempo atual

        // Verifica se uma tecla foi pressionada
        if (kbhit()) {
            char input = getchar();             // Lê a tecla pressionada

            // Controle para impedir múltiplos 'w' seguidos rapidamente
            if (input == 'w' || input == 'W') {
                if (!w_cooldown) {
                    moverPlayer(jogador, input, mapa->largura, mapa->altura); // Move o jogador
                    last_w_press = now;    // Atualiza tempo do último 'w'
                    w_cooldown = 1;        // Ativa cooldown
                }
            } else {
                // Outras teclas: movimentação normal
                if (input == 'a' || input == 'A' || 
                    input == 's' || input == 'S' || 
                    input == 'd' || input == 'D') {
                    moverPlayer(jogador, input, mapa->largura, mapa->altura);
                }
            }
        }

        // Libera o cooldown após o tempo definido
        if (w_cooldown && (now - last_w_press >= W_COOLDOWN_MS)) {
            w_cooldown = 0;
        }

        // Atualiza o jogo se passou o tempo do próximo frame
        if (now - last_update >= FRAME_DELAY_MS) {
            atualizarMapa(mapa);            // Move obstáculos e atualiza estado do mapa
            atualizarBuff(jogador);         // Reduz tempo de buffs ativos no jogador

            int inv = jogador->ativoBuff == 1; // Verifica se jogador está invencível
            int colidiu = verificarColisaoComObstaculoMapa(mapa, jogador->x, jogador->y, inv);

            // Se houve colisão e o jogador não está invencível
            if (colidiu && !inv && jogador->cooldownDano <= 0) {
                jogador->vidas--;                   // Perde uma vida
                jogador->cooldownDano = 10;         // Ativa cooldown para não perder várias vidas seguidas
                jogador->x = mapa->largura / 2;     // Reposiciona o jogador
                jogador->y = mapa->altura - 1;
            }

            // Se o jogador pegou um buff
            if (mapa->buffAtual.ativo &&
                jogador->x == mapa->buffAtual.x &&
                jogador->y == mapa->buffAtual.y) {
                jogador->ativoBuff = mapa->buffAtual.tipo; // Ativa o tipo do buff
                jogador->tempoBuff = 60;                   // Define duração do buff
                mapa->buffAtual.ativo = 0;                 // Remove buff do mapa
            }

            // Se jogador chegou ao topo do mapa (objetivo da fase)
            if (jogador->y == 0) {
                avancarFase(mapa, jogador); // Avança para próxima fase
            }

            // Renderiza o mapa com jogador e obstáculos
            renderizarMapa(mapa, jogador);
            last_update = now; // Atualiza tempo do último frame
        }

        usleep(10000); // Pequeno delay para aliviar CPU (10ms)
    }

    // Fim do jogo: renderiza a última tela e exibe mensagem
    renderizarMapa(mapa, jogador);
    printf("\n💀 Fim de jogo! Pontuação: %d\n", jogador->pontos);
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n'); // Espera Enter para sair
    getchar();

    // Salva pontuação no ranking
    salvarPontuacao(jogador->nome, jogador->pontos);

    // Libera memória e restaura terminal
    destruirMapa(mapa);
    destruirPlayer(jogador);
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios); // Restaura configuração original do terminal
}

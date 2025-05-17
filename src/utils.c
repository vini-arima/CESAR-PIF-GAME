#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>      // usleep, STDIN_FILENO
#include <termios.h>     // configurações do terminal (modo raw, canonical)
#include <sys/ioctl.h>   // ioctl para pegar tamanho do terminal
#include <sys/time.h>    // gettimeofday para medir tempo
#include <sys/select.h>  // select para kbhit()
#include "utils.h"       // seu header local (confere duplicidade)
#include "../include/utils.h"  // cuidado com duplicação de includes

// Limpa a tela do terminal usando sequência ANSI
void limparTela() {
    // ESC [H posiciona o cursor no canto superior esquerdo
    // ESC [J limpa a partir do cursor até o final da tela
    printf("\033[H\033[J");
}

// Pausa a execução por um número dado de milissegundos
void esperar(int ms) {
    // usleep recebe microsegundos, por isso multiplica por 1000
    usleep(ms * 1000);
}

// Lê uma tecla da entrada padrão (bloqueante)
int lerTecla() {
    return getchar();
}

// Lê uma tecla da entrada padrão em modo raw (sem esperar ENTER e sem eco)
// Retorna o caractere digitado
char pegarTecla() {
    struct termios oldt, newt;
    char tecla;

    // Salva as configurações atuais do terminal
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Remove flags ICANON e ECHO:
    // ICANON desativa modo canônico (buffer até ENTER)
    // ECHO desativa exibição da tecla digitada no terminal
    newt.c_lflag &= ~(ICANON | ECHO);

    // Aplica as novas configurações imediatamente
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Lê o caractere pressionado
    tecla = getchar();

    // Restaura as configurações originais do terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return tecla;
}

// Verifica se há alguma tecla pressionada sem bloquear a execução
// Retorna diferente de zero se houver tecla pronta para leitura
int kbhit() {
    struct timeval tv = {0L, 0L}; // timeout zero (não bloqueia)
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    // select monitora a entrada padrão com timeout zero
    // se entrada estiver pronta retorna > 0, senão 0
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

// Retorna o tempo atual do sistema em milissegundos desde a época Unix
long get_current_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

// Obtém o tamanho do terminal (número de linhas e colunas)
// através da chamada ioctl
void getTerminalSize(int* linhas, int* colunas) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *linhas = w.ws_row;
    *colunas = w.ws_col;
}

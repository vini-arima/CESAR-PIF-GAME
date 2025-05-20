#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include "../include/utils.h"

void limparTela() {
    printf("\033[H\033[J");
}

long get_current_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void getTerminalSize(int* linhas, int* colunas) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *linhas = w.ws_row;
    *colunas = w.ws_col;
}

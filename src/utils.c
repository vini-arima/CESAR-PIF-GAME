#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     
#include <termios.h>    
#include <sys/ioctl.h>  
#include <sys/time.h>    
#include <sys/select.h> 
#include "utils.h"       
#include "../include/utils.h" 


void limparTela() {
    
  
    printf("\033[H\033[J");
}


void esperar(int ms) {
   
    usleep(ms * 1000);
}


int lerTecla() {
    return getchar();
}



char pegarTecla() {
    struct termios oldt, newt;
    char tecla;

  l
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

   
 
    
    newt.c_lflag &= ~(ICANON | ECHO);

   
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

   
    tecla = getchar();

   
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return tecla;
}


int kbhit() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

   
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
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

#ifndef UTILS_H
#define UTILS_H

void limparTela();
void esperar(int ms);
int lerTecla();
char pegarTecla();
int kbhit();
long get_current_time_ms();
void getTerminalSize(int* linhas, int* colunas);

#endif

// Previne múltiplas inclusões do mesmo cabeçalho
#ifndef UTILS_H
#define UTILS_H

/**
 * Limpa o terminal (substituto da função system("clear") ou system("cls"))
 */
void limparTela();

/**
 * Pausa o programa por uma quantidade de milissegundos
 * 
 */
void esperar(int ms);

/**
 * Lê uma tecla pressionada, retornando seu código (não espera ENTER)
 * Geralmente usada com terminal configurado em modo raw
 */
int lerTecla();

/**
 * Pega uma tecla pressionada e retorna como caractere
 * Sem esperar ENTER, útil para controles em tempo real
 */
char pegarTecla();

/**
 * Verifica se uma tecla foi pressionada (sem bloqueio)
 * Retorna 1 se houver tecla no buffer, 0 caso contrário
 */
int kbhit();

/**
 * Retorna o tempo atual em milissegundos (para controle de tempo, delays, etc.)
 */
long get_current_time_ms();


void getTerminalSize(int* linhas, int* colunas);

/**
 * Limpa o terminal (está duplicada — provavelmente um erro; remova uma das declarações)
 */
void limparTela();

/**
 * Imprime o título do jogo (ex: logo estilizado no topo)
 * Essa função pode ser usada no menu ou na tela inicial
 */
void imprimirTitulo(); // <- ADICIONADA conforme seu comentário

/**
 * Imprime um sapo em ASCII art (usado no menu, tela de vitória ou derrota, etc.)
 * Só mantenha essa função aqui se ela for definida no utils.c
 */
void imprimirSapoASCII(); // <- Incluída também

#endif

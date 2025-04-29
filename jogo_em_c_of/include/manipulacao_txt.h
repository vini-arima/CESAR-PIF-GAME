#ifndef MANIPULACAO_TXT_H
#define MANIPULACAO_TXT_H

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

 struct registro {
    char nome[50];
    int vitorias;
} typedef Registro;


void salvar_ranking(const char *nome_jogador, int vitoria_geral);
void exibir_ranking();

#endif // MANIPULACAO_TXT_H

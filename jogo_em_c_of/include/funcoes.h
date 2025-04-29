#ifndef FUNCOES_H
#define FUNCOES_H

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

struct estatisticas{
    int vitorias;
    int derrotas;
    int empates;
} typedef Estatisticas;

void logo_entrada();
void logo_Apresentacao();
void explicacao_jogo();
int escolha_opcao(int round);
void verificacao_da_escolha(int opcao_user, Estatisticas *stats);
void mostrar_resultados(Estatisticas *stats);
void mostrar_resultado_geral(int vitoria, int derrota);


#endif // FUNCOES_H

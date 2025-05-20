
#ifndef RANKING_H
#define RANKING_H


#define MAX_JOGADORES 100


#define TAM_NOME 50


typedef struct {
    char nome[TAM_NOME]; 
    int pontos;           
} JogadorRanking;


void salvarPontuacao(const char* nome, int pontos);


void mostrarRanking();


void inicializarRanking();

#endif

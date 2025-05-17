// Previne múltiplas inclusões do mesmo cabeçalho
#ifndef RANKING_H
#define RANKING_H

// Número máximo de jogadores a serem armazenados no ranking
#define MAX_JOGADORES 100

// Tamanho máximo permitido para o nome do jogador
#define TAM_NOME 50

// Estrutura que representa um jogador no ranking
typedef struct {
    char nome[TAM_NOME];  // Nome do jogador
    int pontos;           // Pontuação obtida
} JogadorRanking;

// Salva a pontuação de um jogador no ranking (nome + pontos)
void salvarPontuacao(const char* nome, int pontos);

// Exibe o ranking no terminal (ordenado, geralmente do maior para o menor)
void mostrarRanking();

// Inicializa o ranking (possivelmente carregando de um arquivo ou zerando)
void inicializarRanking();

#endif

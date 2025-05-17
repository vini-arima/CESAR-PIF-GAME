// Previne múltiplas inclusões do mesmo cabeçalho
#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdio.h> // Necessário para printf e fflush

// Sequência de escape ANSI para controle do terminal
#define ESC            "\033"

// Modos de formatação de texto ANSI
#define NORMALTEXT     "[0m"   // Texto normal
#define BOLDTEXT       "[1m"   // Texto em negrito
#define ITALICTEXT     "[3m"   // Texto em itálico
#define BLINKTEXT      "[5m"   // Texto piscando
#define REVERSETEXT    "[7m"   // Inverte cores (fundo e texto)

// Sequências para controle de cursor e tela
#define HOMECURSOR     "[f"        // Move cursor para o canto superior esquerdo
#define SHOWCURSOR     "[?25h"     // Mostra o cursor
#define HIDECURSOR     "[?25l"     // Esconde o cursor
#define CLEARSCREEN    "[2J"       // Limpa a tela inteira

// Caracteres gráficos especiais para desenhar caixas (modo BOX de terminais Unix)
#define BOX_ENABLE     "(0"    // Ativa o conjunto de caracteres BOX
#define BOX_DISABLE    "(B"    // Retorna ao conjunto normal de caracteres

// Caracteres específicos para desenho de bordas e formas
#define BOX_VLINE      0x78   // Linha vertical
#define BOX_HLINE      0x71   // Linha horizontal
#define BOX_UPLEFT     0x6C   // Canto superior esquerdo
#define BOX_UPRIGHT    0x6B   // Canto superior direito
#define BOX_DWNLEFT    0x6D   // Canto inferior esquerdo
#define BOX_DWNRIGHT   0x6A   // Canto inferior direito
#define BOX_CROSS      0x6E   // Cruzamento
#define BOX_TLEFT      0X74   // T para esquerda
#define BOX_TRIGHT     0X75   // T para direita
#define BOX_TUP        0X77   // T para cima
#define BOX_TDOWN      0X76   // T para baixo
#define BOX_DIAMOND    0x60   // Diamante
#define BOX_BLOCK      0x61   // Bloco preenchido
#define BOX_DOT        0x7E   // Ponto ou marcação

// Limites da área útil para o jogo no terminal
#define SCRSTARTX      3      // Posição X inicial do jogo
#define SCRENDX        75     // Posição X final do jogo (limite de área jogável)
#define SCRSTARTY      1      // Posição Y inicial
#define SCRENDY        23     // Posição Y final

// Limites absolutos da tela do terminal
#define MINX           1
#define MINY           1
#define MAXX           80     // Largura máxima padrão do terminal
#define MAXY           24     // Altura máxima padrão do terminal

/**
 * Enumeração com as cores disponíveis para texto e fundo
 */
typedef enum {
    BLACK, RED, GREEN, BROWN, BLUE, MAGENTA, CYAN, LIGHTGRAY,
    DARKGRAY, LIGHTRED, LIGHTGREEN, YELLOW, LIGHTBLUE, 
    LIGHTMAGENTA, LIGHTCYAN, WHITE
} screenColor;

/**
 * Move o cursor para a posição inicial da tela (0,0)
 */
static inline void screenHomeCursor()
{
    printf("%s%s", ESC, HOMECURSOR);
}

/**
 * Mostra o cursor no terminal
 */
static inline void screenShowCursor()
{
    printf("%s%s", ESC, SHOWCURSOR);
}

/**
 * Esconde o cursor no terminal
 */
static inline void screenHideCursor()
{
    printf("%s%s", ESC, HIDECURSOR);
}

/**
 * Limpa toda a tela e posiciona o cursor no início
 */
static inline void screenClear()
{
    screenHomeCursor();
    printf("%s%s", ESC, CLEARSCREEN);
}

/**
 * Força a atualização imediata do terminal
 */
static inline void screenUpdate() {
    fflush(stdout);
}

/**
 * Restaura o modo de texto normal (sem negrito, piscar, etc.)
 */
static inline void screenSetNormal()
{
    printf("%s%s", ESC, NORMALTEXT);
}

/**
 * Ativa o modo de texto em negrito
 */
static inline void screenSetBold()
{
    printf("%s%s", ESC, BOLDTEXT);
}

/**
 * Ativa o modo de texto piscando
 */
static inline void screenSetBlink()
{
    printf("%s%s", ESC, BLINKTEXT);
}

/**
 * Ativa o modo de cores invertidas (fundo <-> texto)
 */
static inline void screenSetReverse()
{
    printf("%s%s", ESC, REVERSETEXT);
}

/**
 * Ativa o conjunto de caracteres especiais para desenho de caixas
 */
static inline void screenBoxEnable()
{
    printf("%s%s", ESC, BOX_ENABLE);
}

/**
 * Restaura o conjunto padrão de caracteres (desativa BOX)
 */
static inline void screenBoxDisable()
{
    printf("%s%s", ESC, BOX_DISABLE);
}

/**
 * Inicializa a tela do jogo, limpa o terminal e desenha as bordas se indicado.
 * @param drawBorders Se diferente de zero, desenha bordas ao redor da área do jogo
 */
void screenInit(int drawBorders);

/**
 * Encerra o uso da tela personalizada, limpando ou restaurando o estado
 */
void screenDestroy();

/**
 * Move o cursor para uma posição específica (x, y)
 * @param x Posição horizontal (coluna)
 * @param y Posição vertical (linha)
 */
void screenGotoxy(int x, int y);

/**
 * Define as cores de texto e de fundo
 * @param fg Cor do texto (foreground)
 * @param bg Cor do fundo (background)
 */
void screenSetColor(screenColor fg, screenColor bg);

#endif /* __SCREEN_H__ */

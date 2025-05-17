/**
 * screen.c
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 * Modified by: [Seu Nome] - Added colored borders support and -1 bg support
*/

#include "screen.h"

// Função auxiliar para desenhar uma borda colorida com o caractere passado
static void drawColoredBorder(char character, screenColor color) {
    // Define a cor do texto (foreground) para 'color' e fundo para preto
    screenSetColor(color, BLACK);
    printf("%c", character);  // Desenha o caractere da borda na tela
}

// Função para desenhar as bordas da área de jogo com cor e estilo definidos
void screenDrawBorders() {
    // Caracteres usados para linhas horizontais e verticais da caixa
    char hbc = BOX_HLINE; // linha horizontal
    char vbc = BOX_VLINE; // linha vertical

    screenColor borderColor = LIGHTGREEN;  // Cor verde clara para bordas

    screenClear();      // Limpa a tela antes de desenhar
    screenBoxEnable();  // Ativa modo caixa (caso a biblioteca use algo interno)

    // Canto superior esquerdo
    screenGotoxy(MINX, MINY);
    drawColoredBorder(BOX_UPLEFT, borderColor);

    // Linha horizontal superior (do lado direito do canto superior esquerdo até o canto superior direito)
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MINY);
        drawColoredBorder(hbc, borderColor);
    }

    // Canto superior direito
    screenGotoxy(MAXX, MINY);
    drawColoredBorder(BOX_UPRIGHT, borderColor);

    // Linhas verticais laterais (do topo até a base)
    for (int i = MINY + 1; i < MAXY; i++) {
        screenGotoxy(MINX, i);
        drawColoredBorder(vbc, borderColor);
        screenGotoxy(MAXX, i);
        drawColoredBorder(vbc, borderColor);
    }

    // Canto inferior esquerdo
    screenGotoxy(MINX, MAXY);
    drawColoredBorder(BOX_DWNLEFT, borderColor);

    // Linha horizontal inferior
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MAXY);
        drawColoredBorder(hbc, borderColor);
    }

    // Canto inferior direito
    screenGotoxy(MAXX, MAXY);
    drawColoredBorder(BOX_DWNRIGHT, borderColor);

    screenBoxDisable(); // Desativa o modo caixa, se necessário
    screenSetColor(LIGHTGRAY, -1);  // Restaura cor padrão (texto cinza claro, fundo padrão)
}

// Inicializa a tela, limpa e opcionalmente desenha as bordas
void screenInit(int drawBorders) {
    screenClear();
    if (drawBorders) {
        screenDrawBorders();
    }
    screenHomeCursor();   // Move o cursor para o canto superior esquerdo
    screenHideCursor();   // Esconde o cursor para melhor visualização do jogo
}

// Restaura configurações da tela antes de sair do programa
void screenDestroy() {
    printf("%s[0;39;49m", ESC); // Reseta cores ANSI para padrão
    screenSetNormal();          // Restaura atributos normais de texto
    screenClear();              // Limpa a tela
    screenHomeCursor();         // Cursor no canto
    screenShowCursor();         // Mostra cursor novamente
}

// Move o cursor para a posição (x, y) na tela
void screenGotoxy(int x, int y) {
    // Limita x e y para estarem dentro dos limites da tela
    x = (x < 0 ? 0 : x >= MAXX ? MAXX - 1 : x);
    y = (y < 0 ? 0 : y > MAXY ? MAXY : y);

    // Envia sequência ANSI para posicionar cursor (linha, coluna)
    printf("%s[f%s[%dB%s[%dC", ESC, ESC, y, ESC, x);
}

// Define a cor do texto e fundo usando códigos ANSI
void screenSetColor(screenColor fg, screenColor bg) {
    char atr[] = "[0;";  // Código base ANSI para atributos (0 = reset)

    // Se a cor do foreground for uma cor clara (ex. LIGHTGRAY ou maior)
    if (fg > LIGHTGRAY) {
        atr[1] = '1';     // Usa atributo "bright" (texto brilhante)
        fg -= 8;          // Ajusta fg para a cor base correspondente
    }

    // Se o background for -1, significa usar fundo padrão do terminal
    if (bg == -1) {
        // Apenas seta a cor do texto (foreground)
        printf("%s%s%dm", ESC, atr, fg + 30);
    } else {
        // Seta a cor do texto e do fundo
        printf("%s%s%d;%dm", ESC, atr, fg + 30, bg + 40);
    }
}

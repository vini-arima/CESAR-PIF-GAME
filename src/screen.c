

#include "screen.h"

static void drawColoredBorder(char character, screenColor color) {
    screenSetColor(color, BLACK);
    printf("%c", character);  
}


void screenDrawBorders() {
    
    char hbc = BOX_HLINE;
    char vbc = BOX_VLINE;

    screenColor borderColor = LIGHTGREEN; 
    screenClear();      
    screenBoxEnable(); 

   
    screenGotoxy(MINX, MINY);
    drawColoredBorder(BOX_UPLEFT, borderColor);

    
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MINY);
        drawColoredBorder(hbc, borderColor);
    }

 
    screenGotoxy(MAXX, MINY);
    drawColoredBorder(BOX_UPRIGHT, borderColor);

    
    for (int i = MINY + 1; i < MAXY; i++) {
        screenGotoxy(MINX, i);
        drawColoredBorder(vbc, borderColor);
        screenGotoxy(MAXX, i);
        drawColoredBorder(vbc, borderColor);
    }

    
    screenGotoxy(MINX, MAXY);
    drawColoredBorder(BOX_DWNLEFT, borderColor);

   
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MAXY);
        drawColoredBorder(hbc, borderColor);
    }

   
    screenGotoxy(MAXX, MAXY);
    drawColoredBorder(BOX_DWNRIGHT, borderColor);

    screenBoxDisable(); 
    screenSetColor(LIGHTGRAY, -1);  
}


void screenInit(int drawBorders) {
    screenClear();
    if (drawBorders) {
        screenDrawBorders();
    }
    screenHomeCursor();   
    screenHideCursor();   
}


void screenDestroy() {
    printf("%s[0;39;49m", ESC); 
    screenSetNormal();         
    screenClear();            
    screenHomeCursor();        
    screenShowCursor();         
}


void screenGotoxy(int x, int y) {
   
    x = (x < 0 ? 0 : x >= MAXX ? MAXX - 1 : x);
    y = (y < 0 ? 0 : y > MAXY ? MAXY : y);

  
    printf("%s[f%s[%dB%s[%dC", ESC, ESC, y, ESC, x);
}


void screenSetColor(screenColor fg, screenColor bg) {
    char atr[] = "[0;";  

   
    if (fg > LIGHTGRAY) {
        atr[1] = '1';     
        fg -= 8;          
    }

  
    if (bg == -1) {
       
        printf("%s%s%dm", ESC, atr, fg + 30);
    } else {
      
        printf("%s%s%d;%dm", ESC, atr, fg + 30, bg + 40);
    }
}

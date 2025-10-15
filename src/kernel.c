#include "print.h"
#include "bga.h"
#include "graphics.h"

void main() {
    printf("Initializing VESA/VBE...");
    if(BgaIsAvailable()) {
        printf("all good bwa");
    }
    else {
        printf("uhhhhhhh fuck shit");
    }
    graphics_init();

    for (int i = 0; i < 400; i+=10) {
        clearScreen(COL(0,0,0));
        drawLine(0, 0, i, 300, COL(255,255,255));
        presentBuffer();
    }
    while(1);
}
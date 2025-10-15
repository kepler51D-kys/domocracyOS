#include "print.h"
#include "bga.h"
#include "graphics.h"
#include <stdbool.h>
#include "segTable.h"

bool VGA = true;

void main() {
    if (!VGA) {
        printf("Initializing VESA/VBE...");
        if(BgaIsAvailable()) {
            printf("all good bwa");
        }
        else {
            printf("uhhhhhhh fuck");
        }
        graphics_init();

        for (int i = 0; i < 400; i+=10) {
            clearScreen(COL(0,0,0));
            drawLine(0, 0, i, 300, COL(255,255,255));
            presentBuffer();
        }
    }
    else {
        printf("pointer at : %d",malloc(5));
    }
    while(1);
}
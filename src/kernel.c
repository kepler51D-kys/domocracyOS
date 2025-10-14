#include "print.h"
#include "bga.h"
#include "graphics.h"

int main() {
    printf("Initializing VESA/VBE...");
    if(BgaIsAvailable()) {
        printf("BGA is available!");
    }
    else {
        printf("BGA was not detected but lets see if it works.");
    }
    
    volatile uint8_t* framebuffer = graphics_init();

    for(int y = 0; y < GRAPHICS_HEIGHT * 3; y++) {
        for(int x = 0; x < GRAPHICS_WIDTH; x++) {
            int c = x == 0 ? 0x00 : x % 2 == 0 ? 0xFF : 0x00;
            putpixel(x, y, x == 0 ? 0xFF : c, c, c, framebuffer);
        }
    }
    while(1);
}
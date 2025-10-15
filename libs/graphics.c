#include "graphics.h"
#include <stdint.h>
#include <stdbool.h>

volatile uint8_t* framebuffer;
volatile uint8_t buffers[2][GRAPHICS_HEIGHT*GRAPHICS_WIDTH*3];
bool activeBuffer = false;

void graphics_init() {
    BgaSetVideoMode(GRAPHICS_WIDTH, GRAPHICS_HEIGHT, VBE_DISPI_BPP_24, 1, 0);
    uint32_t device = BgaFindDevice();
    if(device == 0xFFFF) {
        return;
    }
    framebuffer = (uint8_t*)(BgaGetFramebufferAddress(device));
}

void putpixel(int x, int y, colour col) {
    if (x < 0 || x >= GRAPHICS_WIDTH || y < 0 || y >= GRAPHICS_HEIGHT) return;
    int offset = (y * GRAPHICS_WIDTH + x) * 3;
    buffers[!activeBuffer][offset + 0] = col.b;
    buffers[!activeBuffer][offset + 1] = col.g;
    buffers[!activeBuffer][offset + 2] = col.r;
}

void putpixelUnchecked(int x, int y, colour col) {
    int offset = (y * GRAPHICS_WIDTH + x) * 3;
    buffers[!activeBuffer][offset + 0] = col.b;
    buffers[!activeBuffer][offset + 1] = col.g;
    buffers[!activeBuffer][offset + 2] = col.r;
}
void clearScreen(colour col) {
    for (int i = 0; i < GRAPHICS_WIDTH*GRAPHICS_HEIGHT*3; i+=3) {
        buffers[!activeBuffer][i] = col.b;
        buffers[!activeBuffer][i+1] = col.g;
        buffers[!activeBuffer][i+2] = col.r;
    }
}
void presentBuffer() {
    activeBuffer = !activeBuffer;
    for (int i = 0; i < GRAPHICS_WIDTH*GRAPHICS_HEIGHT*3; i++) {
        framebuffer[i] = buffers[activeBuffer][i];
    }
    // memcpy(framebuffer, buffers[activeBuffer], GRAPHICS_WIDTH*GRAPHICS_HEIGHT*3);
}
void drawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, colour col) {
    int gradient = (x2-x1)/(y2-y1);
    int intercept = y1 - gradient*x1;
    uint32_t inc = x1;
    uint32_t height = y1;
    if (x2 < x1) {
        uint32_t tempx = x2;
        uint32_t tempy = y2;
        x2 = x1;
        y2 = y1;
        x1 = tempx;
        y1 = tempy;
    }
    if (gradient > 0) {
        for (;inc <= x2; inc++) {
            for (; height <= (inc*gradient+intercept); height++) {
                putpixel(height,inc,col);
            }
        }
    }
    else {
        for (;inc <= x2; inc++) {
            for (; height >= (inc*gradient+intercept); height--) {
                putpixel(height,inc,col);
            }
        }
    }
}
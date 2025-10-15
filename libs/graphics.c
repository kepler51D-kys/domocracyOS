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
    
    for (int i = 0; i < GRAPHICS_WIDTH*GRAPHICS_HEIGHT*3; i++) {
        buffers[0][i] = 0;
        buffers[1][i] = 0;
        framebuffer[i] = 0;
    }
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
    float gradient = (float)(y2-y1)/(float)(x2-x1);
    float intercept = y1 - gradient*x1;
    if (x2 < x1) {
        uint32_t tempx = x2;
        uint32_t tempy = y2;
        x2 = x1;
        y2 = y1;
        x1 = tempx;
        y1 = tempy;
    }
    uint32_t height = y1;
    for (uint32_t inc = x1;inc <= x2; inc++) {
        uint32_t desiredPoint = ((float)inc)*gradient+intercept;
        if (height < desiredPoint) {
            for (; height <= desiredPoint; height++) {
                putpixel(inc, height, col);
            }
        }
        else if (height > desiredPoint) {
            for (; height >= desiredPoint; height--) {
                putpixel(inc, height, col);
            }
        }
        else {
            putpixel(inc, height, col);
        }
    }
}
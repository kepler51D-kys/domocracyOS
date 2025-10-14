#include "graphics.h"

uint8_t* graphics_init() {
    BgaSetVideoMode(GRAPHICS_WIDTH, GRAPHICS_HEIGHT, VBE_DISPI_BPP_24, 1, 0);
    
    uint32_t device = BgaFindDevice();
    if(device == 0xFFFF) {
        return (uint8_t *) ((void *) 0);
    }
    return (uint8_t*)(BgaGetFramebufferAddress(device));
}

void putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, volatile uint8_t* framebuffer) {
    int offset = (y * GRAPHICS_WIDTH + x) * 3;
    framebuffer[offset + 0] = b;
    framebuffer[offset + 1] = g;
    framebuffer[offset + 2] = r;
}
#include "graphics.h"

uint8_t* graphics_init() {
    BgaSetVideoMode(120, GRAPHICS_HEIGHT, VBE_DISPI_BPP_24, 1, 0);
    
    uint32_t device = BgaFindDevice();
    if(device == 0xFFFF) {
        return (uint8_t *) ((void *) 0);
    }
    return (uint8_t*)(BgaGetFramebufferAddress(device));
}

// int desired_x_to_real_x(int desired_x) {
//     return desired_x + ((desired_x / 100) * 8);
// }

void putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, volatile uint8_t* framebuffer) {
    // framebuffer[y * GRAPHICS_REAL_WIDTH + desired_x_to_real_x(x)] = color;
    int offset = (y * 120 + x) * 3;
    framebuffer[offset + 0] = b;
    framebuffer[offset + 1] = g;
    framebuffer[offset + 2] = r;
}
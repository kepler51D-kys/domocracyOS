#ifndef GRAPHICS_H
#define GRAPHICS_H 1

#include "vga.h"
#include "bga.h"

#define GRAPHICS_WIDTH 1280
#define GRAPHICS_HEIGHT 720

uint8_t* graphics_init();

void putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, volatile uint8_t* framebuffer);

#endif // GRAPHICS_H
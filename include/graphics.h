#ifndef GRAPHICS_H
#define GRAPHICS_H 1
#include <stdint.h>
#include "vga.h"
#include "bga.h"

#define GRAPHICS_WIDTH 1280
#define GRAPHICS_HEIGHT 720

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} colour;

#define COL(r,g,b) (colour){r,g,b}

void graphics_init();

void putpixel(int x, int y, colour col);

void clearScreen(colour col);

void drawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, colour col);

void presentBuffer();
#endif // GRAPHICS_H
#include "print.h"
#include "bga.h"
#include "graphics.h"
#include <stdbool.h>
#include "segTable.h"

bool VGA = false;

void main()
{
    mem_init();
    if (!VGA)
    {
        printf("Initializing VESA/VBE...");
        if (BgaIsAvailable())
        {
            printf("all good bwa");
        }
        else
        {
            printf("uhhhhhhh fuck");
        }
        graphics_init();
        while (1)
        {
            for (int i = 0; i < 400; i += 10)
            {
                clearScreen(COL(0, 0, 0));
                // drawLine_bresenham(0, 0, i, 300, COL(255, 0, 0));
                drawLine(0, 0, i, 300, COL(0, 255, 0));
                drawLine_DDA(0, 300, i, 600, COL(0, 0, 255));
                presentBuffer();
            }
        }
    }
    else
    {
        // malloc(5);
        // printf("pointer at : %d",malloc(5));
    }
    while (1)
        ;
}
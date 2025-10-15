#include <stdint.h>
#ifndef BGA_H
#define BGA_H 1

#include "vga.h"
#include "io.h"

#define BGA_VENDOR_ID 0x1234
#define BGA_DEVICE_ID 0x1111

void BgaWriteRegister(unsigned short IndexValue, unsigned short DataValue);

unsigned short BgaReadRegister(unsigned short IndexValue);

int BgaIsAvailable(void);

void BgaSetVideoMode(unsigned int Width, unsigned int Height, unsigned int BitDepth, int UseLinearFrameBuffer, int ClearVideoMemory);

void BgaSetBank(unsigned short BankNumber);

uintptr_t BgaGetFramebufferAddress(uint8_t slot);

uint32_t BgaFindDevice(void);

#endif // BGA_H
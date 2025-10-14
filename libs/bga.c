#include "bga.h"

void BgaWriteRegister(unsigned short IndexValue, unsigned short DataValue)
{
    outpw(VBE_DISPI_IOPORT_INDEX, IndexValue);
    outpw(VBE_DISPI_IOPORT_DATA, DataValue);
}

unsigned short BgaReadRegister(unsigned short IndexValue)
{
    outpw(VBE_DISPI_IOPORT_INDEX, IndexValue);
    return inpw(VBE_DISPI_IOPORT_DATA);
}

int BgaIsAvailable(void)
{
    // return (BgaReadRegister(VBE_DISPI_INDEX_ID) == VBE_DISPI_ID4);
    unsigned short reg = BgaReadRegister(VBE_DISPI_INDEX_ID);
    return (reg >= 0xB0C0 && reg <= 0xB0C4);
}

void BgaSetVideoMode(unsigned int Width, unsigned int Height, unsigned int BitDepth, int UseLinearFrameBuffer, int ClearVideoMemory)
{
    BgaWriteRegister(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
    BgaWriteRegister(VBE_DISPI_INDEX_XRES, Width);
    BgaWriteRegister(VBE_DISPI_INDEX_YRES, Height);
    BgaWriteRegister(VBE_DISPI_INDEX_BPP, BitDepth);
    BgaWriteRegister(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED |
        (UseLinearFrameBuffer ? VBE_DISPI_LFB_ENABLED : 0) |
        (ClearVideoMemory ? 0 : VBE_DISPI_NOCLEARMEM));
}

void BgaSetBank(unsigned short BankNumber)
{
    BgaWriteRegister(VBE_DISPI_INDEX_BANK, BankNumber);
}

uintptr_t BgaGetFramebufferAddress(uint8_t slot)
{
    uint32_t bar0 = pci_read_dword(0, slot, 0, 0x10); // 0x10 = BAR0
    // The lowest 4 bits are flags, mask them off
    return (uintptr_t)(bar0 & 0xFFFFFFF0);
}

uint32_t BgaFindDevice(void)
{
    for (uint8_t slot = 0; slot < 32; slot++) {
        uint32_t vendor_device = pci_read_dword(0, slot, 0, 0);
        uint16_t vendor = vendor_device & 0xFFFF;
        uint16_t device = (vendor_device >> 16) & 0xFFFF;

        if (vendor == BGA_VENDOR_ID && device == BGA_DEVICE_ID) {
            return slot; // Found on bus 0, return slot number
        }
    }
    return 0xFFFF; // Not found
}
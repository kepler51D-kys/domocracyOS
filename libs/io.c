#include "io.h"

/* Write a byte to an I/O port */
void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

/* Read a byte from an I/O port */
uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* Write a word (16 bits) to an I/O port */
void outpw(uint16_t port, uint16_t value)
{
    asm volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

/* Read a word (16 bits) from an I/O port */
uint16_t inpw(uint16_t port)
{
    uint16_t ret;
    asm volatile ("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* Write a doubleword (32 bits) to an I/O port */
void outl(uint16_t port, uint32_t value)
{
    asm volatile ("outl %0, %1" : : "a"(value), "Nd"(port));
}

/* Read a doubleword (32 bits) from an I/O port */
uint32_t inl(uint16_t port)
{
    uint32_t ret;
    asm volatile ("inl %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

uint32_t pci_read_dword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
{
    uint32_t address = (uint32_t)((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC) | 0x80000000);
    outl(PCI_CONFIG_ADDRESS, address);
    return inl(PCI_CONFIG_DATA);
}
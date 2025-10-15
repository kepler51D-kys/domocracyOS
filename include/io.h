#include <stdint.h>
#ifndef IO_H
#define IO_H 1

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA    0xCFC

/* Write a byte to an I/O port */
void outb(uint16_t port, uint8_t value);

/* Read a byte from an I/O port */
uint8_t inb(uint16_t port);

/* Write a word (16 bits) to an I/O port */
void outpw(uint16_t port, uint16_t value);

/* Read a word (16 bits) from an I/O port */
uint16_t inpw(uint16_t port);

/* Write a doubleword (32 bits) to an I/O port */
void outl(uint16_t port, uint32_t value);

/* Read a doubleword (32 bits) from an I/O port */
uint32_t inl(uint16_t port);

uint32_t pci_read_dword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);

#endif // IO_H
[bits 32]

; Declare constants for the multiboot header.
MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
MBFLAGS  equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + MBFLAGS) ; checksum of above, to prove we are multiboot
                                ; CHECKSUM + MAGIC + MBFLAGS should be Zero (0)

global start

section .multiboot
align 4
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM

section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB is reserved for stack
stack_top:

section .text
start:
    mov esp, stack_top
    extern main
    call main
	cli
.hang:	hlt
	jmp .hang
.end:
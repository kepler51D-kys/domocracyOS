bits 32

section .multiboot
align 4
    dd 0x1BADB002              ; magic
    dd 0x00000003              ; flags
    dd -(0x1BADB002 + 0x00000003) ; checksum

section .bss
align 16
stack_bottom:
resb 16384
stack_top:

section .text
global _start
mainASM:
    mov esp, stack_top
    push ebx
    push eax
    
    extern kernel_main
    call kernel_main
    
    cli
.hang:
    hlt
    jmp .hang
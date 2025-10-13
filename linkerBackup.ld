ENTRY(main)

SECTIONS
{
    . = 1M;

    .text: {
        /* link the multiboot struct here */
        . = ALIGN(8);
        KEEP(*(.multiboot))
        /* place all of your code afterwards */
        *(.text)
    }

    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}
// kernel.c
// #include <stdint.h>
void kernel_main(unsigned int magic, void* mb_info) {
    // Check multiboot magic
    if (magic != 0x2BADB002) {
        // Error handling
        return;
    }
    
    // Your kernel code here
}
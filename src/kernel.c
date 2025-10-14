#include "print.h"
#include "segTable.h"

int main() {
    mem_init();
    printf("pointer location : %d",malloc(50));
    while(1);
}
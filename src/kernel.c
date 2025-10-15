#include "print.h"
#include "segTable.h"

int main() {
    // mem_init();
    float temp = 4.6;
    temp *= 2;
    int x = (int)temp;
    // printf("pointer location : %p\n",malloc(50));
    printf("float test : %d\n",x);
    while(1);
}
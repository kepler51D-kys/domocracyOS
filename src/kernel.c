#include "print.h"

extern int detect_v86();

int main() {
    volatile int x = detect_v86();
    volatile int n;
    if(x == 1) {
        n = 0x555555;
    }
    printf("%d", n);
    // printf("hello world: %s : goodbye","hello");
    // printf("   v86?: %d", detect_v86());
    while(1);
}
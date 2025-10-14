#include "print.h"

extern int detect_v86();

int main() {
    printf("hello world: %s : goodbye","hello");
    printf("   v86?: %s", detect_v86() ? "true" : "false");
    while(1);
}
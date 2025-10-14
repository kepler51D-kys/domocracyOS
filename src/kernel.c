#include "print.h"

extern int detect_v86();

int main() {
    printf("   v86?: %d", detect_v86());
    while(1);
}
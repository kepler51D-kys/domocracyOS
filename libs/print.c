#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

uint32_t charCount = 0;

void printDec(int message) {
    volatile char* video_memory = (volatile char*)0xB8000;
    if (message == 0) {
        video_memory[charCount*2] = '0';
        video_memory[charCount++*2+1] = 0x07;
        return;
    }
    bool negative = message < 0;
    if (negative) {
        message = -message;
        video_memory[charCount * 2] = '-';
        video_memory[charCount * 2 + 1] = 0x07;
        charCount++;
    }
    char buffer[5];
    for (int i = 0; i < 5; i++) {
        buffer[4-i] = message % 10;
        message /= 10;
    }
    bool numReached = false;
    for (int i = 0; i < 5; i++) {
        numReached |= buffer[i] != 0;
        if (numReached) {
            video_memory[charCount * 2] = buffer[i] + '0';
            video_memory[charCount * 2 + 1] = 0x07;
            charCount++;
        }
    }
}
int printf(const char* message, ...) {
    va_list args;
    va_start(args,message);
    volatile char* video_memory = (volatile char*)0xB8000;
    bool getParam = false;
    for (int i = 0; message[i] != '\0'; i++) {
        if (getParam) {
            if (message[i] == 'c') {
                video_memory[charCount * 2] = va_arg(args,int);
                video_memory[charCount++ * 2 + 1] = 0x07;
            }
            else if (message[i] == 'd') {
                printDec(va_arg(args,int));
            }
            else if (message[i] == 'p') {
                // do nothing for now
            }
            else if (message[i] == 's') {
                char* str = va_arg(args,char*);
                for (int i = 0; str[i] != '\0'; i++) {
                    video_memory[charCount * 2] = str[i];
                    video_memory[charCount++ * 2 + 1] = 0x07;
                }
            }
            else {
                return -1;
            }
            getParam = false;
        }
        else if (message[i] == '%') {
            getParam = true;
        }
        else {
            video_memory[charCount * 2] = message[i];
            video_memory[charCount++ * 2 + 1] = 0x07;
        }
    }
    return 0;
}

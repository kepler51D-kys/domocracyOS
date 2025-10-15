#include "error.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

uint32_t charCount = 0;
volatile char* video_memory = (volatile char*)0xB8000;

void printDec(int message) {
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
void printPointer(void* pointer) {
    uint8_t buffer[8];
    uint8_t translationTable[16] = {
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
        'A',
        'B',
        'C',
        'D',
        'E',
        'F',
    };
    uint32_t message = (uint32_t)pointer;
    for (int i = 0; message > 0; i+=2) {
        uint8_t bytemsglower = message & 0x0F;
        uint8_t bytemsgupper = (message & 0xF0) >> 4;
        buffer[i] = translationTable[bytemsglower];
        buffer[i+1] = translationTable[bytemsgupper];
        message >>= 8;
    }
    for (int i = 7; i >= 0; i--) {
        video_memory[charCount*2] = buffer[i];
        video_memory[charCount*2+1] = 0x07;
        charCount++;
    }
}

int printf(const char* format, ...) {
    va_list args;
    va_start(args,format);
    bool getParam = false;
    for (int i = 0; format[i] != '\0'; i++) {
        if (getParam) {
            if (format[i] == 'c') {
                video_memory[charCount * 2] = va_arg(args,int);
                video_memory[charCount++ * 2 + 1] = 0x07;
            }
            else if (format[i] == 'd') {
                printDec(va_arg(args,int));
            }
            else if (format[i] == 'p') {
                printPointer(va_arg(args,void*));
            }
            else if (format[i] == 's') {
                char* str = va_arg(args,char*);
                for (int i = 0; str[i] != '\0'; i++) {
                    video_memory[charCount * 2] = str[i];
                    video_memory[charCount++ * 2 + 1] = 0x07;
                }
            }
            else {
                return FAILURE;
            }
            getParam = false;
        }
        else if (format[i] == '%') {
            getParam = true;
        }
        else {
            video_memory[charCount * 2] = format[i];
            video_memory[charCount++ * 2 + 1] = 0x07;
        }
    }
    return SUCCESS;
}

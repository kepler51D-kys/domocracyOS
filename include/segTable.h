#ifndef SEGTABLE_H
#define SEGTABLE_H
#include <stdint.h>

typedef struct {
    void* start;
    uint32_t length;
} segment;

#endif
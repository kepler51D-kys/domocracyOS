#ifndef SEGTABLE_H
#define SEGTABLE_H
#include <stdint.h>

#define NULL 0

typedef struct {
    void* start;
    uint32_t length;
} segment;

typedef struct {
    segment* segments;
    int len;
    int maxLen;
} segmentList;

typedef struct {
    void* start;
    void* end;
    segmentList list;
} heap;

extern heap heaps[64];

void mem_init();
void* malloc(uint32_t size);
void free(void* ptr);
#endif
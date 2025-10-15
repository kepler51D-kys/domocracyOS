#include "segTable.h"
#include <stdint.h>

#define heapCount 64
#define segCountPerHeap 128

heap heaps[heapCount];
int heapAmount = 0;

segment segment_init(void* start, uint32_t length) {
    return (segment){start,length};
}

void heapInit(void* start, void* end) {
    heaps[heapAmount].start = start;
    heaps[heapAmount].end = end;
    heaps[heapAmount].list.len = 1;
    heaps[heapAmount].list.maxLen = segCountPerHeap;
    heaps[heapAmount].list.segments[0].start = start;
    heaps[heapAmount].list.segments[0].length = segCountPerHeap;
    heapAmount++;
}
void mem_init() {
    heapInit((void*)10, (void*)10000);
}

int insertSegment(int index, heap heapInsert, segment segToInsert) {
    if (heapInsert.list.len >= heapInsert.list.maxLen+1) {
        return -1;
    }
    for (int i = heapInsert.list.len; i > index; i--) {
        heapInsert.list.segments[i] = heapInsert.list.segments[i-1];
    }
    heapInsert.list.segments[index] = segToInsert;
    heapInsert.list.len++;
    return 0;
}
int deleteSegment(int index, heap heapDelete) {
    heapDelete.list.len--;
    for (int i = index; i < heapDelete.list.len; i++) {
        heapDelete.list.segments[i] = heapDelete.list.segments[i+1];
    }
    return 0;
}
void* findGap(uint32_t size) {
    for (int i = 0 ; i < heapAmount; i++) {
        heap currentHeap = heaps[i];
        if (currentHeap.list.len == 1) {
            if ((currentHeap.list.segments[0].start - currentHeap.start) >= size) {
                
            }
        }
        for (int j = 0; j < currentHeap.list.len-1; j++) {
            segment currentSeg = currentHeap.list.segments[j];
            segment nextSeg = currentHeap.list.segments[j+1];
            uint32_t gap = nextSeg.start - (currentSeg.start + currentSeg.length);
            if (gap >= size) {
                segment newSeg;
                newSeg.start = (void*)((uint32_t)(nextSeg.start + (uint32_t)(nextSeg.length + 7)) & (uint32_t)~7);
                newSeg.length = size;
                insertSegment(j+1, currentHeap, newSeg);
                return newSeg.start;
            }
        }
    }
    return NULL;
}
void* malloc(uint32_t size) {
    return findGap(size);
}
void free(void* ptr) {
    for (int i = 0; i < heapAmount; i++) {
        for (int j = 0; j < heaps[i].list.len; j++) {
            if (heaps[i].list.segments[j].start == ptr) {
                deleteSegment(j, heaps[i]);
                return;
            }
        }
    }
    return;
}
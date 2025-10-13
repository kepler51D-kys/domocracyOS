#include "segTable.h"

segment segment_init(void* start, uint32_t length) {
    return (segment){start,length};
}

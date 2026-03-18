#include "MemoryMonitor.h"

MemoryMonitor::MemoryMonitor() {
    updateHeapStats();
}

void MemoryMonitor::updateHeapStats() {
    _freeDefault = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);
    _freeInternal = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
    _freeSPIRAM = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
    _largestBlock = heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT);
    _minFree = _freeDefault;
}

void MemoryMonitor::printHeapState() const {
    printf("Heap stats:\n");
    printf("  Free default: %zu bytes\n", _freeDefault);
    printf("  Free internal: %zu bytes\n", _freeInternal);
    printf("  Free SPIRAM: %zu bytes\n", _freeSPIRAM);
    printf("  Largest free block: %zu bytes\n", _largestBlock);
    printf("  Min ever free heap: %zu bytes\n", _minFree);
}
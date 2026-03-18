#pragma once
#include "esp_heap_caps.h"
#include "esp_system.h"
#include <cstdio>
#include <functional>

class MemoryMonitor {
private:
    size_t _freeDefault;
    size_t _freeInternal;
    size_t _freeSPIRAM;
    size_t _largestBlock;
    size_t _minFree;

    void updateHeapStats();

public:
    MemoryMonitor();
    void printHeapState() const;
};
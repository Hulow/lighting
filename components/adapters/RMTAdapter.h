#pragma once

#include "../application/ports/IPixelsSender.h"

class RMTAdapter : public IPixelsSender {
public:
    void init();  
};
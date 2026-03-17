#pragma once

#include <vector>
#include "Led.h"
// #include "Symbolizer.h"

class Strip {
private:
    uint8_t _green;
    uint8_t _red;
    uint8_t _blue;
    int _ledsCount;
    std::vector<Led> _leds;

    void setupLeds();

public:
    Strip(const uint8_t& green, const uint8_t& red, const uint8_t& blue, const int& ledsCount);
    const std::vector<Led>& getLeds() const;
};
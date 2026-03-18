#pragma once

#include <vector>
#include "Led.h"

class Strip {
private:
    uint8_t _green = 0;
    uint8_t _red = 0;
    uint8_t _blue = 0;
    int _ledsCount;
    std::vector<Led> _leds;
    Strip(const int& ledsCount);
    void create();

public:
    static Strip init(const int& ledsCount);
    void set(const uint8_t& green, const uint8_t& red, const uint8_t& blue);
    const std::vector<Led>& getLeds() const;
};
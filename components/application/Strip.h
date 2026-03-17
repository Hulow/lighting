#pragma once

#include <vector>
#include "Led.h"
// #include "Symbolizer.h"

class Strip {
private:
    std::vector<Led> _leds;
    uint8_t _green;
    uint8_t _red;
    uint8_t _blue;

    Strip(std::vector<Led> leds);

public:
    static Strip generate(uint8_t ledsCount, uint8_t green, uint8_t red, uint8_t blue);
    const std::vector<Led>& getLeds() const;
};
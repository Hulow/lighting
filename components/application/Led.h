#pragma once

#include <cstdint>

#include "Color.h"

class Led {
    private:
        Color _color;
    public:
        Led(uint8_t green, uint8_t red, uint8_t blue) : _color(green, red, blue){}

        Led getLed() {
            return *this;
        }

        Color getColor() {
            return _color;
        }
};
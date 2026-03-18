#pragma once

#include <cstdint>

#include "Color.h"

class Led {
    private:
        Color _color;
    public:
        Led(const uint8_t& green, const uint8_t& red, const uint8_t& blue) : _color(green, red, blue) {}

        Color getColor() const {
            return _color;
        }

        void setColor(const uint8_t& green, const uint8_t& red, const uint8_t& blue) {
            _color.setGreen(green);
            _color.setRed(red);
            _color.setBlue(blue);
        }
};
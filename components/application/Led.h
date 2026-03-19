#pragma once

#include <cstdint>

#include "Color.h"

class Led {
    private:
        Color _color;
         Led(const Color& color) : _color(color) {}
    public:
        Led static from(const Color& color) {
            return Led(color);
        }

        Color getColor() const {
            return _color;
        }

        void setColor(const Color& color) {
            _color = color;
        }
};
#pragma once

#include <cstdint>

#include "Color.h"
#include "Timing.h"

class Led {
    private:
        Color _color;
        Timing _timing;
         Led(const Color& color, const Timing& timing = Timing()) : _color(color), _timing(timing) {}
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

        std::vector<uint8_t> serializeColor() const {
            return _color.serialize();
        }
};
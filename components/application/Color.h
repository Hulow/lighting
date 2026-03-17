#pragma once

#include <cstdint>

class Color {
    private:
        uint8_t _green;
        uint8_t _red;
        uint8_t _blue;
        
    
    public:

        Color(
            uint8_t green, 
            uint8_t red, 
            uint8_t blue
        ) 
            : 
            _green(green), 
            _red(red), 
            _blue(blue) 
        {}

        uint8_t getGreen() const {
            return _green;
        }

        uint8_t getRed() const {
            return _red;
        }

        uint8_t getBlue() const {
            return _blue;
        }
};
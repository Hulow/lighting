#pragma once

#include <vector>
#include "Led.h"

class Strip {
    private:
        std::vector<Led> _leds;
        uint8_t _green;
        uint8_t _red;
        uint8_t _blue;
        std::vector<Led> _strip;
        Strip(uint8_t green, uint8_t red, uint8_t blue) : _green(green), _red(red), _blue(blue) {}
    
    public:
        static Strip setColor(uint8_t green, uint8_t red, uint8_t blue) {
            return Strip(green, red, blue);
        }

        void generate(uint8_t ledsCount) {
            for (int i= 0; i < ledsCount; i++) {
                _leds.push_back(Led(_green, _red, _blue));
            }
        }
        
        std::vector<Led> getLeds() {
            return _leds;
        }

};
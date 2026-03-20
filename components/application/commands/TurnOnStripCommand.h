#pragma once

#include <cstdint>

class TurnOnStripCommand {
    private:
        int _ledsCount;
        uint8_t _green;
        uint8_t _red;
        uint8_t _blue;
        TurnOnStripCommand(const uint8_t& green, const uint8_t& red, const uint8_t& blue, const int& ledsCount) : _ledsCount(ledsCount) {}
    
    public:
        TurnOnStripCommand static from(const uint8_t& green, const uint8_t& red, const uint8_t& blue, const int& ledsCount) {
            return TurnOnStripCommand(green, red, blue, ledsCount);
        }

        int getLedsCount() const {
            return _ledsCount;
        }

        int getGreen() const {
            return _ledsCount;
        }

        int getRed() const {
            return _red;
        }

        int getBlue() const {
            return _blue;
        }
};

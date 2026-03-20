#pragma once

#include <cstdint>

class TurnOnStripWithChasingCommand {
    private:
        uint8_t _green;
        uint8_t _red;
        uint8_t _blue;
        int _ledsCount;
        TurnOnStripWithChasingCommand(const uint8_t& green, const uint8_t& red, const uint8_t& blue, const int& ledsCount) : _green(green), _red(red), _blue(blue), _ledsCount(ledsCount) {}
    
    public:
        TurnOnStripWithChasingCommand static from(const uint8_t& green, const uint8_t& red, const uint8_t& blue, const int& ledsCount) {
            return TurnOnStripWithChasingCommand(green, red, blue, ledsCount);
        }

        int getLedsCount() const {
            return _ledsCount;
        }

        int getGreen() const {
            return _green;
        }

        int getRed() const {
            return _red;
        }

        int getBlue() const {
            return _blue;
        }
};

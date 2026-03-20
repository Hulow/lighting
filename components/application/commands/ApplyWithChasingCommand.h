#pragma once

#include <cstdint>

class ApplyWithChasingCommand {
    private:
        uint8_t _green;
        uint8_t _red;
        uint8_t _blue;
        int _ledsCount;
        ApplyWithChasingCommand(const uint8_t& green, const uint8_t& red, const uint8_t& blue, const int& ledsCount) : _green(green), _red(red), _blue(blue), _ledsCount(ledsCount) {}
    
    public:
        ApplyWithChasingCommand static from(const uint8_t& green, const uint8_t& red, const uint8_t& blue, const int& ledsCount) {
            return ApplyWithChasingCommand(green, red, blue, ledsCount);
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

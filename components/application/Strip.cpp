#include "Strip.h"

Strip::Strip(const uint8_t& green, const uint8_t& red, const uint8_t& blue, const int& ledsCount) : _green(green), _red(red), _blue(blue), _ledsCount(ledsCount) {
    setupLeds();
}

void Strip::setupLeds() {
    for (int i = 0; i < _ledsCount; i++) {
        _leds.push_back(Led(_green, _red, _blue));
    }
}

const std::vector<Led>& Strip::getLeds() const {
    return _leds;
}

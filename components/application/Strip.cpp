#include "Strip.h"
#include "Color.h"

Strip::Strip(const int& ledsCount) : _ledsCount(ledsCount) {
    create();
}

Strip Strip::init(const int& ledsCount) {
    Strip strip(ledsCount);
    return strip;
}

void Strip::create() {
    for (int i = 0; i < _ledsCount; i++) {
        _leds.push_back(Led::from(Color::fromGRB(_green, _red, _blue)));
    }
}

void Strip::setColor(const uint8_t& green, const uint8_t& red, const uint8_t& blue) {
    for (int led = 0; led < _leds.size(); led++) {
        _leds[led].setColor(Color::fromGRB(green, red, blue));
    }
}

const std::vector<Led>& Strip::getLeds() const {
    return _leds;
}
#include "Strip.h"

Strip::Strip(std::vector<Led> leds) : _leds(leds) { }

Strip Strip::generate(uint8_t ledsCount, uint8_t green, uint8_t red, uint8_t blue) {
    std::vector<Led> leds;
    for (int i = 0; i < ledsCount; i++) {
        leds.push_back(Led(green, red, blue));
    }

    return Strip(leds);
}

const std::vector<Led>& Strip::getLeds() const {
    return _leds;
}

// void Strip::symbolizeStrip() {
//     _symbolizer.symbolizeStrip(*this); // pass the whole strip
// }
#include "ChasingPattern.h"

std::vector<std::vector<Led>> ChasingPattern::generate(const std::vector<Led>& leds) {
    std::vector<std::vector<Led>> frames;
    std::vector<Led> frame;
    for (auto& led : leds) {
        frame.push_back(led);
        frames.push_back(frame);
    }

    return frames;
}
#pragma once
#include "../Led.h"

class ChasingPattern {
public:
    static std::vector<std::vector<Led>> generate(const std::vector<Led>& leds);
};
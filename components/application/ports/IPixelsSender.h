#pragma once

#include <vector>
#include "../domain/Symbol.h"

class IPixelsSender {
    public:
        virtual ~IPixelsSender() = default;
        virtual void setupConfigs() = 0;
        virtual void turnOnTransmitter() = 0;
        virtual void transmit(const std::vector<Symbol>& symbols) = 0;
};
#pragma once
#include <cstdint>

class ITimer {
    public:
        ~ITimer() = default;
        virtual void wait(const uint32_t& ms) = 0;
};
#pragma once

#include <array>

#include "BitToRMTMapper.h"


struct LED {
    uint8_t g;
    uint8_t r;
    uint8_t b;
};

template <size_t N>

class WS2815Encoder {
    private: 
        BitToRMTMapper _mapper;
        std::array<LED, N> _strip;
    public:
        WS2815Encoder(BitToRMTMapper& mapper, std::array<LED, N>& strip);
        void encode();
};
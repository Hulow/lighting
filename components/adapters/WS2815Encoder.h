#pragma once

#include <array> 
#include <vector>
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
        std::vector<rmt_symbol_word_t> _symbols;
        void encodeLED(const LED& led);
        void encodeColor(const uint8_t& color);
        void encodeSingleBit(const uint8_t& bit);
    public:
        WS2815Encoder(const BitToRMTMapper& mapper, const std::array<LED, N>& strip);
        void encodeStrip();
        std::vector<rmt_symbol_word_t> getSymbols();
};
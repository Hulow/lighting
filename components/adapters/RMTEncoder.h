#pragma once

#include <array> 
#include <vector>
#include "RMTMapper.h"

struct tempLED {
    uint8_t g;
    uint8_t r;
    uint8_t b;
};

template <size_t N>

class RMTEncoder {
    private: 
        RMTMapper _mapper;
        std::array<tempLED, N> _strip;
        std::vector<rmt_symbol_word_t> _symbols;
        void encodeLED(const tempLED& led);
        void encodeColor(const uint8_t& color);
        void encodeSingleBit(const uint8_t& bit);
    public:
        RMTEncoder(const int& resolution, const std::array<tempLED, N>& strip);
        void encodeStrip();
        const std::vector<rmt_symbol_word_t> getSymbols() const;
};
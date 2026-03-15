#include "driver/rmt_tx.h"

#include <iostream>
#include <vector>

#include "WS2815Encoder.h"

template <size_t N>
WS2815Encoder<N>::WS2815Encoder(const BitToRMTMapper& mapper, const std::array<LED, N>& strip) : _mapper(mapper), _strip(strip) {}

template <size_t N>
std::vector<rmt_symbol_word_t> WS2815Encoder<N>::encodeStripToSymbols() {
   
    std::vector<rmt_symbol_word_t> symbols;
    for (int color = 0; color < _strip.size(); color++) { //each led of the strip

        const uint8_t& redBits = _strip[color].r;
        const uint8_t& greenBits = _strip[color].g;
        const uint8_t& blueBits = _strip[color].b;

        for (int bit = 7; bit >= 0; bit --) { //each bit of the strip
            uint8_t redBit = (redBits >> bit) & 0x01;
            uint8_t greenBit = (greenBits >> bit) & 0x01;
            uint8_t blueBit = (blueBits >> bit) & 0x01;

            rmt_symbol_word_t redSymbol = _mapper.map(redBit); //convert each bit to symbol
            rmt_symbol_word_t greenSymbol = _mapper.map(greenBit);
            rmt_symbol_word_t blueSymbol = _mapper.map(blueBit);

            symbols.push_back(redSymbol);
            symbols.push_back(greenSymbol);
            symbols.push_back(blueSymbol);
        }
    }

    return symbols; //return symbols from one strip
}

template class WS2815Encoder<1>;
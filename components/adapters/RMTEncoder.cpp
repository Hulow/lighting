#include "driver/rmt_tx.h"
#include <vector>
#include "RMTEncoder.h"
#include <iostream>

template <size_t N>
RMTEncoder<N>::RMTEncoder(
    const int& resolution, 
    const std::array<LED, N>& strip
) : 
_mapper(resolution), 
_strip(strip) 
{
    _symbols.clear();
}

template <size_t N>
void RMTEncoder<N>::encodeStrip() {
    _symbols.clear();
    for (size_t led = 0; led < _strip.size(); led++) {
        printf("starting to encode %d \n", led);
        encodeLED(_strip[led]);
    }
    
    rmt_symbol_word_t reset = {
        .duration0 = 12000,
        .level0 = 0,
        .duration1 = 12000,
        .level1 = 0
    };

    _symbols.push_back(reset);
}

template <size_t N>
void RMTEncoder<N>::encodeLED(const LED& led) {
    for (const uint8_t color : {led.g, led.r, led.b}) {
        encodeColor(color);
    }
}

template <size_t N>
void RMTEncoder<N>::encodeColor(const uint8_t& color) {
    for (int i = 7; i >= 0; i --) { 
            encodeSingleBit((color >> i) & 0x01);
        }
}

template <size_t N>
void RMTEncoder<N>::encodeSingleBit(const uint8_t& bit) {
    _symbols.push_back(_mapper.map(bit)); /* could be improved */
}

template <size_t N>
const std::vector<rmt_symbol_word_t> RMTEncoder<N>::getSymbols() const {
    return _symbols;
}

template class RMTEncoder<1>;
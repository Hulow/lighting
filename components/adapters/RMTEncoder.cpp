#include "driver/rmt_tx.h"
#include <vector>
#include "RMTEncoder.h"
#include <iostream>

template <size_t N>
RMTEncoder<N>::RMTEncoder(const int& resolution, const std::array<LED, N>& strip) : _mapper(resolution), _strip(strip) {
    _symbols.clear();
}

template <size_t N>
void RMTEncoder<N>::encodeStrip() {
    for (size_t led = 0; led < _strip.size(); led++) {
        encodeLED(_strip[led]);
    }
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
std::vector<rmt_symbol_word_t> RMTEncoder<N>::getSymbols() {
    return _symbols;
}

template class RMTEncoder<1>;
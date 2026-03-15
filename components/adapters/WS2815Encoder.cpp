#include "driver/rmt_tx.h"
#include <vector>
#include "WS2815Encoder.h"

template <size_t N>
WS2815Encoder<N>::WS2815Encoder(const BitToRMTMapper& mapper, const std::array<LED, N>& strip) : _mapper(mapper), _strip(strip) {
    _symbols.clear();
}

template <size_t N>
void WS2815Encoder<N>::encodeStrip() {
    for (size_t led = 0; led < _strip.size(); led++) {
        encodeLED(_strip[led]);
    }
}

template <size_t N>
void WS2815Encoder<N>::encodeLED(const LED& led) {
    for (const uint8_t color : {led.g, led.r, led.b}) {
        encodeColor(color);
    }
}

template <size_t N>
void WS2815Encoder<N>::encodeColor(const uint8_t& color) {
    for (int i = 7; i >= 0; i --) { 
            encodeSingleBit((color >> i) & 0x01);
        }
}

template <size_t N>
void WS2815Encoder<N>::encodeSingleBit(const uint8_t& bit) {
    _symbols.push_back(_mapper.map(bit)); /* could be improved */
}

template <size_t N>
std::vector<rmt_symbol_word_t> WS2815Encoder<N>::getSymbols() {
    return _symbols;
}

template class WS2815Encoder<1>;
#include "Encoder.h"
#include <cmath>

Encoder::Encoder(const std::vector<Symbol>& symbols, const int& resolution) : _symbols(symbols), _resolution(resolution) {}

void Encoder::toRmtSymbols() {
    for (int i = 0; i < _symbols.size(); i++) {
        toRmtSymbol(_symbols[i]);
    }
}

void Encoder::toRmtSymbol(const Symbol& symbol) {
    _rmtSymbols.push_back({
        .duration0 = toRmtTick(symbol.highDuration),
        .level0 = 1,
        .duration1 = toRmtTick(symbol.lowDuration),
        .level1 = 0
   });
}

uint16_t Encoder::toRmtTick(const uint16_t& timing) {
    double ticks = static_cast<double>(timing) * _resolution / 1e9;
    return static_cast<uint16_t>(std::round(ticks));
}

const std::vector<rmt_symbol_word_t> Encoder::getRmtSymbols() {
    return _rmtSymbols;
}

void Encoder::updateSymbols(const std::vector<Symbol>& symbols) {
    _symbols = symbols;
}
#include "Encoder.h"
#include <cmath>

Encoder::Encoder(const std::vector<Symbol>& symbols, const int& resolution) : _symbols(symbols), _resolution(resolution) {}

void Encoder::toRmtSymbols() {
    _rmtSymbols.clear();
    _rmtSymbols.reserve(_symbols.size());
    for (const auto& symbol : _symbols) {
        toRmtSymbol(symbol);
    }
}

void Encoder::toRmtSymbol(const Symbol& symbol) {
    _rmtSymbols.push_back({
        .duration0 = toRmtTick(symbol.getHighDuration()),
        .level0 = 1,
        .duration1 = toRmtTick(symbol.getLowDuration()),
        .level1 = 0
   });
}

/* unsafe */
uint16_t Encoder::toRmtTick(const uint16_t& timing) {
    double ticks = static_cast<double>(timing) * _resolution / 1e9;
    return static_cast<uint16_t>(std::round(ticks));
}

const std::vector<rmt_symbol_word_t>& Encoder::getRmtSymbols() const {
    return _rmtSymbols;
}

void Encoder::updateSymbols(const std::vector<Symbol>& symbols) {
    _symbols = symbols;
}
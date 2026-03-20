#include "Encoder.h"
#include <cmath>

Encoder::Encoder(const std::vector<Symbol>& symbols, const int& resolution) : _symbols(symbols), _resolution(resolution) {}

Encoder Encoder::fromSymbol(const std::vector<Symbol>& symbols, const int& resolution) {
    return Encoder(symbols, resolution);
}

const std::vector<rmt_symbol_word_t> Encoder::toRmtSymbols() {
    std::vector<rmt_symbol_word_t> rmtSymbols;
    for (const auto& symbol : _symbols) {
        rmtSymbols.push_back(toRmtSymbol(symbol));
    }

    return rmtSymbols;
}

rmt_symbol_word_t Encoder::toRmtSymbol(const Symbol& symbol) {
    return rmt_symbol_word_t({
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

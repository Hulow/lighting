#include "SymbolsConverter.h"
#include <vector>

SymbolsConverter::SymbolsConverter() : _timing() {};

void SymbolsConverter::toSymbols(const std::vector<Led>& leds) {
    _symbols.clear();
    for (auto& led : leds) {
        generateSymbols(led.serializeColor());
    }
    addResetSymbol(); 
}

void SymbolsConverter::generateSymbols(const std::vector<uint8_t>& bits) {
    for (const uint8_t& bit : bits ) {
        _symbols.push_back(toSymbol(bit));
    }
}

Symbol SymbolsConverter::toSymbol(const uint8_t& bit) {
    return bit == 1
        ? Symbol::from(_timing.getLowTimeLineSignal(), _timing.getHighTimeLineSignal())
        : Symbol::from(_timing.getLowTimeLineNoSignal(), _timing.getHighTimeLineNoSignal());
}

void SymbolsConverter::addResetSymbol() {
    _symbols.push_back(Symbol::from(_timing.getLowResetDuration(), 0));
}

std::vector<Symbol> SymbolsConverter::getSymbols() {
    return _symbols;
}
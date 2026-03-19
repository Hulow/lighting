#include "SequenceConverter.h"
#include "../domain/Symbol.h"
#include <vector>

SequenceConverter::SequenceConverter() : _timing() {};

void SequenceConverter::toSymbols(const Strip& strip) {
    _symbols.clear();
    for (auto& led : strip.getLeds()) {
        generateSymbols(led.serializeColor());
    }
    addResetSymbol(); 
}

void SequenceConverter::generateSymbols(const std::vector<uint8_t>& bits) {
    for (const uint8_t& bit : bits ) {
        _symbols.push_back(toSymbol(bit));
    }
}

Symbol SequenceConverter::toSymbol(const uint8_t& bit) {
    return bit == 1
        ? Symbol::from(_timing.getLowTimeLineSignal(), _timing.getHighTimeLineSignal())
        : Symbol::from(_timing.getLowTimeLineNoSignal(), _timing.getHighTimeLineNoSignal());
}

void SequenceConverter::addResetSymbol() {
    _symbols.push_back(Symbol::from(_timing.getLowResetDuration(), 0));
}

std::vector<Symbol> SequenceConverter::getSymbols() {
    return _symbols;
}
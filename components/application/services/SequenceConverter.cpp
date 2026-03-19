#include "SequenceConverter.h"
#include "../Symbol.h"
#include <vector>

SequenceConverter::SequenceConverter() : _timing() {};

void SequenceConverter::convert(const Strip& strip) {
    _symbols.clear();
    for (auto& led : strip.getLeds()) {
        toSymbols(led.serializeColor());
    }
    addResetDuration(); 
}

void SequenceConverter::toSymbols(const std::vector<uint8_t>& bits) {
    for (const bit : bits ) {
        _symbols.push_back(toSymbol(bit));
    }
}

Symbol SequenceConverter::toSymbol(const uint8_t& bit) {
    return bit == 1
        ? Symbol::from(_timing.getLowTimeLineSignal(), _timing.getHighTimeLineSignal())
        : Symbol::from(_timing.getLowTimeLineNoSignal(), _timing.getHighTimeLineNoSignal());
}

void SequenceConverter::addResetDuration() {
    _symbols.push_back(Symbol::from(_timing.getLowResetDuration(), 0));
}
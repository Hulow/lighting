#include "Symbolizer.h"
#include "Symbol.h"

Symbolizer::Symbolizer(const Strip& strip) : _strip(strip) {};
 
const std::vector<Symbol>& Symbolizer::getSymbols() {
    return _symbols;
}

void Symbolizer::symbolize() {
    for(int led = 0; led < _strip.getLeds().size(); led++) {
        symbolizeLed(_strip.getLeds()[led]);
    }
    symbolizeResetSymbol();
}

void Symbolizer::updateStrip(const Strip& strip) {
    _strip = strip;
     _symbols.clear();
}

void Symbolizer::symbolizeLed(const Led& led) {
    for (uint8_t color : {led.getColor().getGreen(), led.getColor().getRed(), led.getColor().getBlue()}) {
        symbolizeColor(color);
    }
}

void Symbolizer::symbolizeColor(const uint8_t& color) {
    for (int i = 7; i >= 0; i --) { 
        SymbolizeBit((color >> i) & 0x01);
    }
}

void Symbolizer::SymbolizeBit(const uint8_t& bit) {
    _symbols.push_back(mapSymbol(bit));
}

void Symbolizer::symbolizeResetSymbol() {
     _symbols.push_back(mapResetSymbol());
}

Symbol Symbolizer::mapSymbol(const uint8_t& bit) {
     return bit == 1
        ? Symbol::from(_lowTimeLineSignal, _highTimeLineSignal)
        : Symbol::from(_lowTimeLineNoSignal, _highTimeLineNoSignal);
}

Symbol Symbolizer::mapResetSymbol() {
    return Symbol::from(_lowResetDuration, 0);

}

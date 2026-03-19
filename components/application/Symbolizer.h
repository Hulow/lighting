#pragma once

#include "Strip.h"
#include "Led.h"
#include "Symbol.h"

class Symbolizer {
    private:
        Strip _strip;
        std::vector<Symbol> _symbols;
        uint16_t _highTimeLineNoSignal  = 300;
        uint16_t _lowTimeLineNoSignal = 1090;
        uint16_t _highTimeLineSignal = 1090;
        uint16_t _lowTimeLineSignal = 320;
        uint16_t _lowResetDuration = 30000;
        void symbolizeLed(const Led& led);
        void symbolizeColor(const uint8_t& color);
        void SymbolizeBit(const uint8_t& bit);
        Symbol mapSymbol(const uint8_t& bit);
        Symbol mapResetSymbol();
        void symbolizeResetSymbol();

    public:
        Symbolizer(const Strip& strip);
        void symbolize();
        const std::vector<Symbol>& getSymbols();
        void updateStrip(const Strip& strip);
};
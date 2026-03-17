#pragma once

#include "Strip.h"
#include "Led.h"

struct Symbol {
    uint16_t lowDuration;
    uint16_t highDuration; 
};

class Symbolizer {
    private:
        Strip _strip;
        std::vector<Symbol> _symbols;
        uint16_t _highTimeLineNoSignal  = 300;
        uint16_t _lowTimeLineNoSignal = 1090;
        uint16_t _highTimeLineSignal = 1090;
        uint16_t _lowTimeLineSignal = 320;
        void symbolizeLed(const Led& led);
        void symbolizeColor(const uint8_t& color);
        void SymbolizeBit(const uint8_t& bit);
        Symbol mapSymbol(const uint8_t& bit);

    public:
        Symbolizer(Strip& strip);
        void symbolize();
        const std::vector<Symbol>& getSymbols();
};
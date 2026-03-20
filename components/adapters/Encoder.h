#include <vector>
#include "driver/rmt_tx.h"

#include "../application/domain/Symbol.h"

class Encoder {
    private:
        std::vector<Symbol> _symbols;
        int _resolution;
        uint16_t toRmtTick(const uint16_t& timing);
        rmt_symbol_word_t toRmtSymbol(const Symbol& symbol);
        Encoder(const std::vector<Symbol>& symbols, const int& resolution);

    public:
        Encoder static fromSymbol(const std::vector<Symbol>& symbols, const int& resolution);
        const std::vector<rmt_symbol_word_t> toRmtSymbols();
};     
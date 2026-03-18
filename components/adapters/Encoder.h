#include <vector>
#include "driver/rmt_tx.h"

#include "../application/Symbolizer.h"

class Encoder {
    private:
        std::vector<Symbol> _symbols;
        std::vector<rmt_symbol_word_t> _rmtSymbols;
        int _resolution;
        uint16_t toRmtTick(uint16_t& timing);
        void toRmtSymbol(Symbol& symbol);

    public:
        Encoder(const std::vector<Symbol>& symbols, const int& resolution);
        void toRmtSymbols();
        const std::vector<rmt_symbol_word_t> getRmtSymbols();
};     
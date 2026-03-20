#include "../Led.h"
#include "../Symbol.h"
#include "../Timing.h"
#include <vector>

class SymbolsConverter {
    private:
        Timing _timing;
        std::vector<Symbol> _symbols;

        void generateSymbols(const std::vector<uint8_t>& bits);
        Symbol toSymbol(const uint8_t& bit);
        void addResetSymbol();
    
    public: 
        SymbolsConverter();
        void toSymbols(const std::vector<Led>& leds);
        std::vector<Symbol> getSymbols();
};
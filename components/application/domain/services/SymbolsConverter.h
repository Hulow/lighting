#include "../domain/Strip.h"
#include "../domain/Symbol.h"
#include "../domain/Timing.h"
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
        void toSymbols(const Strip& strip);
        std::vector<Symbol> getSymbols();
};
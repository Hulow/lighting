#include "../domain/Strip.h"
#include "../domain/Symbol.h"
#include "../domain/Timing.h"
#include <vector>

class SequenceConverter {
    private:
        Timing _timing;
        std::vector<Symbol> _symbols;

        void generateSymbols(const std::vector<uint8_t>& bits);
        Symbol toSymbol(const uint8_t& bit);
        void addResetSymbol();
    
    public: 
        SequenceConverter();
        void toSymbols(const Strip& strip);
        std::vector<Symbol> getSymbols();
};
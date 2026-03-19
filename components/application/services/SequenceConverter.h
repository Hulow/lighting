#include "../Strip.h"
#include "../Symbol.h"
#include "../Timing.h"
#include <vector>

class SequenceConverter {
    private:
        Timing _timing;
        std::vector<Symbol> _symbols;

        void toSymbols(const std::vector<uint8_t>& bits);
        Symbol toSymbol(const uint8_t& bit);
        void addResetDuration();
    
    public: 
        SequenceConverter();
        void convert(const Strip& strip);
};
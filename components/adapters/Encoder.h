#include <vector>

#include "../application/Symbolizer.h"

class Encoder {
    private:
        std::vector<Symbol> _symbols;
        int _resolution;
    
    public:
        Encoder(const std::vector<Symbol> symbols, const int& resolution);
};
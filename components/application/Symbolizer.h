#include <vector>
#include "Led.h"
#include "Color.h"

struct Symbol {
        uint16_t lowDuration;
        uint16_t highDuration; 
};

class Symbolizer {

    public:
        std::vector<Symbol> getSymbols() {
            return _symbols;
        }

        void symbolizeStrip(const Strip& strip) {
            for(int led = 0; led < strip.getLeds().size(); led++) {
                symbolizeLed(strip.getLeds()[led]);
            }
        }
    
    private:
        std::vector<Symbol> _symbols;
        uint16_t _highTimeLineNoSignal  = 300;
        uint16_t _lowTimeLineNoSignal = 1090;
        uint16_t _highTimeLineSignal = 1090;
        uint16_t _lowTimeLineSignal = 320;

        void symbolizeLed(Led& led) {
            for (uint8_t color : {led.getColor().getGreen(), led.getColor().getRed(), led.getColor().getBlue()}) {
                symbolizeColor(color);
            }
        }

        void symbolizeColor(uint8_t& color) {
            for (int i = 7; i >= 0; i --) { 
                SymbolizeBit((color >> i) & 0x01);
        }
        }

        void SymbolizeBit(const uint8_t& bit) {
            _symbols.push_back(mapSymbol(bit));
        }

        Symbol mapSymbol(const uint8_t& bit) {
            return bit == 1
                ? Symbol{ .lowDuration = _lowTimeLineSignal, .highDuration = _highTimeLineSignal }
                : Symbol{ .lowDuration = _lowTimeLineNoSignal, .highDuration = _highTimeLineNoSignal };
        }
};
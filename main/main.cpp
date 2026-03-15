#include <iostream>

#include "../components/adapters/RMTAdapter.h"
#include "../components/adapters/WS2815Encoder.h"
#include "../components/adapters/BitToRMTMapper.h"

extern "C" int app_main() {
    // RMTAdapter adapterPin18(18); 
    // // adapterPin18.sendRMTItems(
    // //     ws2815_encoder,
    // //     led_colors,
    // //     sizeof(led_colors)
    // // );

    std::array<LED, 1> strip{{200, 20, 30}};
    const std::array<LED, 1>&  refStrip = strip;

    BitToRMTMapper mapper(10000000);
    const BitToRMTMapper&  refMapper = mapper;

    WS2815Encoder<1> encoder(refMapper, refStrip);

    std::vector<rmt_symbol_word_t> symbols = encoder.encodeStripToSymbols();

    for (int i=0; i<symbols.size(); i++) {
        std::cout << symbols[i].duration0 << std::endl;
        std::cout << symbols[i].level0 << std::endl;
        std::cout << symbols[i].duration1 << std::endl;
        std::cout << symbols[i].level1 << std::endl;
    }


    return 0;
}
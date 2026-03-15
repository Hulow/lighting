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
    BitToRMTMapper mapper(10000000);
    WS2815Encoder<1> encoder(mapper, strip);

    encoder.encodeStrip();

    std::cout << encoder.getSymbols().size() << std::endl;
    return 0;
}
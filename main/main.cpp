#include "../components/adapters/RMTAdapter.h"
#include "../components/adapters/WS2815Encoder.h"
#include "../components/adapters/RMTMapper.h"

extern "C" int app_main() {

    std::array<LED, 1> stripOne{{200, 20, 30}};
    WS2815Encoder<1> encoder(10000000, stripOne);
    RMTAdapter adapterPin18(18); 

    encoder.encodeStrip();
    // adapterPin18.sendRMTItems(
    //     ws2815_encoder,
    //     led_colors,
    //     sizeof(led_colors)
    // );
    return 0;
}
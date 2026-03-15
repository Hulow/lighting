#include <array>
#include "driver/rmt_tx.h"

#include "../components/adapters/RMTAdapter.h"
#include "../components/adapters/WS2815Encoder.h"

extern "C" int app_main() {
    RMTAdapter adapterPin18(18); 
    // adapterPin18.sendRMTItems(
    //     ws2815_encoder,
    //     led_colors,
    //     sizeof(led_colors)
    // );

    std::array<LED, 25> strip{};



    return 0;
}
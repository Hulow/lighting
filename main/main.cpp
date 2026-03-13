#include "driver/rmt_tx.h"

#include "../components/adapters/RMTAdapter.h"

extern "C" int app_main() {
    RMTAdapter adapterPin18(18); 
    adapterPin18.sendRMTItems(
        ws2815_encoder,
        led_colors,
        sizeof(led_colors)
    );

    return 0;
}
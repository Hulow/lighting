#include "../components/adapters/RMTAdapter.h"
#include "../components/adapters/RMTEncoder.h"
#include "../components/adapters/RMTMapper.h"
#include "../components/adapters/RMTConfigBuilder.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" int app_main() {
    std::array<LED, 1> strip = {
    LED{0, 250, 0},
};

    RMTAdapter<1> adapterPin18(
            RMTConfigBuilder()
            .gpioNum(GPIO_NUM_4)
            .clock(static_cast<rmt_clock_source_t>(RMT_CLK_SRC_DEFAULT))
            .memBlocks(64) //must be symbol.size()
            .queueDepth(1)
            .resolutionHz(10'000'000)
            .build(),
            strip
        );
        adapterPin18.transmitConfigs();
        adapterPin18.turnOnTransmitter();
        
    while(true) {
        adapterPin18.encodeStrip();
        adapterPin18.sendRMTItems();
    }
    return 0;
}
#include "../components/adapters/RMTAdapter.h"
#include "../components/adapters/RMTEncoder.h"
#include "../components/adapters/RMTMapper.h"
#include "../components/adapters/RMTConfigBuilder.h"
#include "../components/application/Strip.h"
#include "../components/application/Symbolizer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <iostream>

extern "C" int app_main() {
    Strip StripOne(1, 250, 1, 10);
    Symbolizer symbolizer(StripOne);
    symbolizer.symbolize();

    std::array<tempLED, 26> ledsArray;
    for (size_t i = 0; i < 26; i++) {
        const Color& c = StripOne.getLeds()[i].getColor(); // access color
        ledsArray[i] = tempLED{ c.getGreen(), c.getRed(), c.getBlue() }; 
    }

    RMTAdapter<26> adapterPin18(
            RMTConfigBuilder()
            .gpioNum(GPIO_NUM_4)
            .clock(static_cast<rmt_clock_source_t>(RMT_CLK_SRC_DEFAULT))
            .memBlocks(64) //must be symbol.size()
            .queueDepth(1)
            .resolutionHz(10'000'000)
            .build(),
            ledsArray
        );
        adapterPin18.transmitConfigs();
        adapterPin18.turnOnTransmitter();
        adapterPin18.encodeStrip();
        
    while(true) {
        adapterPin18.sendRMTItems();
    }
    return 0;
}
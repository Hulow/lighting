#include "../components/adapters/RMTAdapter.h"
#include "../components/adapters/RMTEncoder.h"
#include "../components/adapters/RMTMapper.h"
#include "../components/adapters/RMTConfigBuilder.h"
#include "../components/adapters/Encoder.h"
#include "../components/adapters/Transceiver.h"

#include "../components/application/Strip.h"
#include "../components/application/Symbolizer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <iostream>

extern "C" int app_main() {

    Strip StripOne(1, 250, 1, 26);
    Symbolizer symbolizer(StripOne);
    symbolizer.symbolize();

    rmt_tx_channel_config_t configsOne = RMTConfigBuilder()
        .gpioNum(GPIO_NUM_4)
        .clock(static_cast<rmt_clock_source_t>(RMT_CLK_SRC_DEFAULT))
        .memBlocks(64) //must be symbol.size()
        .queueDepth(1)
        .resolutionHz(10'000'000)
        .build();

    Encoder encoder(symbolizer.getSymbols(), configsOne.resolution_hz);
    encoder.toRmtSymbols();

    Transceiver transceiver(configsOne, encoder.getRmtSymbols());
    transceiver.setupConfigs();
    transceiver.turnOnTransmitter();

    while(true) {
        transceiver.transmit();
    }

    return 0;
}
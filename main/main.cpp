#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../components/adapters/ConfigsBuilder.h"
#include "../components/adapters/Encoder.h"
#include "../components/adapters/Transceiver.h"
#include "../components/adapters/MemoryMonitor.h"

#include "../components/application/Strip.h"
#include "../components/application/Symbolizer.h"

extern "C" int app_main() {
    MemoryMonitor memoryMonitor;
    memoryMonitor.printHeapState();
    Strip StripOne(0, 255, 0, 26);
    Symbolizer symbolizer(StripOne);
    symbolizer.symbolize();

    rmt_tx_channel_config_t configsOne = ConfigsBuilder()
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
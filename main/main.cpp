#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../components/adapters/ConfigsBuilder.h"
#include "../components/adapters/Encoder.h"
#include "../components/adapters/Transceiver.h"

#include "../components/application/Strip.h"
#include "../components/application/Symbolizer.h"

extern "C" int app_main() {
    Strip stripOne = Strip::init(26);
    Symbolizer symbolizer(stripOne);
    symbolizer.symbolize();

    rmt_tx_channel_config_t configsOne = ConfigsBuilder()
        .gpioNum(GPIO_NUM_4)
        .clock(static_cast<rmt_clock_source_t>(RMT_CLK_SRC_DEFAULT))
        .memBlocks(64) //symbolizer.getSymbols().size()
        .queueDepth(1)
        .resolutionHz(10'000'000)
        .build();

    Encoder encoder(symbolizer.getSymbols(), configsOne.resolution_hz);
    encoder.toRmtSymbols();

    Transceiver transceiver(configsOne);
    transceiver.setupConfigs();
    transceiver.turnOnTransmitter();
    transceiver.transmit(encoder.getRmtSymbols());


    // ################### ########################## #####################

    stripOne.setColor(0, 0, 255);
    symbolizer.updateStrip(stripOne);
    symbolizer.symbolize();

    encoder.updateSymbols(symbolizer.getSymbols());
    encoder.toRmtSymbols();

    while(true) {
        transceiver.transmit(encoder.getRmtSymbols());
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    return 0;
}

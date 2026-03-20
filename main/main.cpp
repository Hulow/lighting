#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../components/adapters/ConfigsBuilder.h"
#include "../components/adapters/Transceiver.h"

#include "../components/application/domain/Strip.h"
#include "../components/application/domain/services/SymbolsConverter.h"

extern "C" int app_main() {
    Strip stripOne = Strip::init(26);
    SymbolsConverter converter;
    converter.toSymbols(stripOne);

    rmt_tx_channel_config_t configsOne = ConfigsBuilder()
        .gpioNum(GPIO_NUM_4)
        .clock(static_cast<rmt_clock_source_t>(RMT_CLK_SRC_DEFAULT))
        .memBlocks(64) //symbolizer.getSymbols().size()
        .queueDepth(1)
        .resolutionHz(10'000'000)
        .build();

    Transceiver transceiver(configsOne);
    transceiver.setupConfigs();
    transceiver.turnOnTransmitter();
    transceiver.transmit(converter.getSymbols());

    while(true) {
        stripOne.setColor(0, 255, 0);
        converter.toSymbols(stripOne);
        transceiver.transmit(converter.getSymbols());
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    return 0;
}

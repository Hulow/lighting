#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../components/adapters/ConfigsBuilder.h"
#include "../components/adapters/Encoder.h"
#include "../components/adapters/Transceiver.h"

#include "../components/application/domain/Strip.h"
#include "../components/application/services/SequenceConverter.h"

extern "C" int app_main() {
    Strip stripOne = Strip::init(26);
    SequenceConverter converter;
    converter.toSymbols(stripOne);

    rmt_tx_channel_config_t configsOne = ConfigsBuilder()
        .gpioNum(GPIO_NUM_4)
        .clock(static_cast<rmt_clock_source_t>(RMT_CLK_SRC_DEFAULT))
        .memBlocks(64) //symbolizer.getSymbols().size()
        .queueDepth(1)
        .resolutionHz(10'000'000)
        .build();

    Encoder encoder(converter.getSymbols(), configsOne.resolution_hz);
    encoder.toRmtSymbols();

    Transceiver transceiver(configsOne);
    transceiver.setupConfigs();
    transceiver.turnOnTransmitter();
    transceiver.transmit(encoder.getRmtSymbols());

    while(true) {
        stripOne.setColor(0, 255, 0);
        converter.toSymbols(stripOne);
        encoder.updateSymbols(converter.getSymbols());
        encoder.toRmtSymbols();
        transceiver.transmit(encoder.getRmtSymbols());
        vTaskDelay(pdMS_TO_TICKS(10));

        stripOne.setColor(0, 0, 0);
        converter.toSymbols(stripOne);
        encoder.updateSymbols(converter.getSymbols());
        encoder.toRmtSymbols();
        transceiver.transmit(encoder.getRmtSymbols());
        vTaskDelay(pdMS_TO_TICKS(10000));

        stripOne.setColor(0, 255, 0);
        converter.toSymbols(stripOne);
        encoder.updateSymbols(converter.getSymbols());
        encoder.toRmtSymbols();
        transceiver.transmit(encoder.getRmtSymbols());
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    return 0;
}

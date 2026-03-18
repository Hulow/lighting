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
    //    .memBlocks(symbolizer.getSymbols().size())  //must be symbol.size()
        .memBlocks(64)  //must be symbol.size()
        .queueDepth(1)
        .resolutionHz(10'000'000)
        .build();

    Encoder encoder(symbolizer.getSymbols(), configsOne.resolution_hz);
    encoder.toRmtSymbols();

    Transceiver transceiver(configsOne);
    transceiver.setupConfigs();
    transceiver.turnOnTransmitter();
    transceiver.transmit(encoder.getRmtSymbols());

    stripOne.set(0, 255, 0);
    symbolizer.updateSymbols(stripOne);
    symbolizer.symbolize();

    encoder.updateSymbols(symbolizer.getSymbols());
    encoder.toRmtSymbols();

    rmt_tx_channel_config_t configsTwo = ConfigsBuilder()
        .gpioNum(GPIO_NUM_4)
        .clock(static_cast<rmt_clock_source_t>(RMT_CLK_SRC_DEFAULT))
        .memBlocks(symbolizer.getSymbols().size())  //must be symbol.size()
        .queueDepth(1)
        .resolutionHz(10'000'000)
        .build();

    Transceiver transceiverTwo (configsTwo);
    transceiverTwo.setupConfigs();
    transceiverTwo.turnOnTransmitter();


    const auto& rmtSymbols = encoder.getRmtSymbols();

    for (int i = 0; i < rmtSymbols.size(); i++) {
        const auto& sym = rmtSymbols[i]; 
        printf("symbol %d: duration0=%u, level0=%d, duration1=%u, level1=%d\n",
            i, sym.duration0, sym.level0, sym.duration1, sym.level1);
    }
     
    while(true) {
        transceiverTwo.transmit(encoder.getRmtSymbols());
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    return 0;
}



    // printf("Number of symbols to transmit: %d\n", encoder.getRmtSymbols().size());

//     for (int i = 0; i < rmtSymbols.size(); i++) {
//     const auto& sym = rmtSymbols[i]; 
//     printf("symbol %d: duration0=%u, level0=%d, duration1=%u, level1=%d\n",
//            i, sym.duration0, sym.level0, sym.duration1, sym.level1);
// }
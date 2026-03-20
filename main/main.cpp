#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../components/adapters/ConfigsBuilder.h"
#include "../components/adapters/Transceiver.h"

#include "../components/application/domain/Strip.h"
#include "../components/application/domain/services/SymbolsConverter.h"
#include "../components/application/commands/InitializeStripCommand.h"
#include "../components/application/commands/InitializeStripCommandHandler.h"
#include "../components/application/commands/TurnOnStripCommand.h"
#include "../components/application/commands/TurnOnStripCommandHandler.h"



extern "C" int app_main() {
    rmt_tx_channel_config_t configs = ConfigsBuilder()
        .gpioNum(GPIO_NUM_4)
        .clock(static_cast<rmt_clock_source_t>(RMT_CLK_SRC_DEFAULT))
        .memBlocks(64) //symbolizer.getSymbols().size()
        .queueDepth(1)
        .resolutionHz(10'000'000)
        .build();

    Transceiver transceiver(configs);
    transceiver.setupConfigs();
    transceiver.turnOnTransmitter();
    
    InitializeStripCommandHandler initializationHandlerOne(transceiver);
    initializationHandlerOne.execute(InitializeStripCommand::from(26));

    TurnOnStripCommandHandler handlerOne(transceiver);

    while(true) {
        handlerOne.execute(TurnOnStripCommand::from(0, 255, 0, 26));
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    return 0;
}

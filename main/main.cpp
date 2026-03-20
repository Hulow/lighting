#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../components/adapters/ConfigsBuilder.h"
#include "../components/adapters/Transceiver.h"
#include "../components/application/domain/Strip.h"
#include "../components/application/commands/InitializeStripCommand.h"
#include "../components/application/commands/InitializeStripCommandHandler.h"
#include "../components/application/commands/TurnOnStripCommand.h"
#include "../components/application/commands/TurnOnStripCommandHandler.h"



extern "C" int app_main() {
    ConfigsBuilder baseConfigs = ConfigsBuilder()
        .clock(static_cast<rmt_clock_source_t>(RMT_CLK_SRC_DEFAULT))
        .memBlocks(64) //symbolizer.getSymbols().size()
        .queueDepth(1)
        .resolutionHz(10'000'000);

    ConfigsBuilder configsOne = baseConfigs.gpioNum(GPIO_NUM_4);
    Transceiver transceiverOne(configsOne.build());
    transceiverOne.setupConfigs();
    transceiverOne.turnOnTransmitter();
    InitializeStripCommandHandler initializationHandlerOne(transceiverOne);
    initializationHandlerOne.execute(InitializeStripCommand::from(13));
    TurnOnStripCommandHandler handlerOne(transceiverOne);

    ConfigsBuilder configsTwo = baseConfigs.gpioNum(GPIO_NUM_5);
    Transceiver transceiverTwo(configsTwo.build());
    transceiverTwo.setupConfigs();
    transceiverTwo.turnOnTransmitter();
    InitializeStripCommandHandler initializationHandlerTwo(transceiverTwo);
    initializationHandlerTwo.execute(InitializeStripCommand::from(13));
    TurnOnStripCommandHandler handlerTwo(transceiverTwo);

    while(true) {
        handlerOne.execute(TurnOnStripCommand::from(0, 255, 0, 26));
        handlerTwo.execute(TurnOnStripCommand::from(0, 255, 0, 26));
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    return 0;
}

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../components/adapters/ConfigsBuilder.h"
#include "../components/adapters/Transceiver.h"
#include "../components/adapters/FreeRTOSTimer.h"

#include "../components/application/commands/InitializeStripCommand.h"
#include "../components/application/commands/InitializeStripCommandHandler.h"
#include "../components/application/commands/TurnOnStripCommand.h"
#include "../components/application/commands/TurnOnStripCommandHandler.h"
#include "../components/application/commands/TurnOnStripWithChasingCommand.h"
#include "../components/application/commands/TurnOnStripWithChasingCommandHandler.h"



extern "C" int app_main() {
    ConfigsBuilder baseConfigs = ConfigsBuilder()
        .clock(static_cast<rmt_clock_source_t>(RMT_CLK_SRC_DEFAULT))
        .memBlocks(64)
        .queueDepth(1)
        .resolutionHz(10'000'000);

    /*
        # -------------------------
        # STRIP 1
        # -------------------------
    */

    ConfigsBuilder configsOne = baseConfigs.gpioNum(GPIO_NUM_4);
    Transceiver transceiverOne(configsOne.build());
    transceiverOne.setupConfigs();
    transceiverOne.turnOnTransmitter();
    InitializeStripCommandHandler initializationHandlerOne(transceiverOne);
    initializationHandlerOne.execute(InitializeStripCommand::from(13));

    FreeRTOSTimer timer;
    TurnOnStripWithChasingCommandHandler handlerOne(transceiverOne, timer);

    /*
        # -------------------------
        # STRIP 2
        # -------------------------
    */

    ConfigsBuilder configsTwo = baseConfigs.gpioNum(GPIO_NUM_5);
    Transceiver transceiverTwo(configsTwo.build());
    transceiverTwo.setupConfigs();
    transceiverTwo.turnOnTransmitter();
    InitializeStripCommandHandler initializationHandlerTwo(transceiverTwo);
    initializationHandlerTwo.execute(InitializeStripCommand::from(13));

    TurnOnStripCommandHandler handlerTwo(transceiverTwo);

    while(true) {
        initializationHandlerOne.execute(InitializeStripCommand::from(13));
        handlerTwo.execute(TurnOnStripCommand::from(0, 255, 0, 13));
        handlerOne.execute(TurnOnStripWithChasingCommand::from(0, 255, 0, 13));
        timer.wait(10);
    }

    return 0;
}

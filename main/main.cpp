#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../components/adapters/ConfigsBuilder.h"
#include "../components/adapters/Transceiver.h"
#include "../components/adapters/FreeRTOSTimer.h"

#include "../components/application/commands/InitializeCommand.h"
#include "../components/application/commands/InitializeCommandHandler.h"
#include "../components/application/commands/ApplyCommand.h"
#include "../components/application/commands/ApplyCommandHandler.h"
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
    InitializeCommandHandler initializationHandlerOne(transceiverOne);
    initializationHandlerOne.execute(InitializeCommand::from(13));

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
    InitializeCommandHandler initializationHandlerTwo(transceiverTwo);
    initializationHandlerTwo.execute(InitializeCommand::from(13));

    ApplyCommandHandler handlerTwo(transceiverTwo);

    while(true) {
        initializationHandlerOne.execute(InitializeCommand::from(13));
        handlerTwo.execute(ApplyCommand::from(0, 255, 0, 13));
        handlerOne.execute(TurnOnStripWithChasingCommand::from(0, 255, 0, 13));
        timer.wait(10);
    }

    return 0;
}

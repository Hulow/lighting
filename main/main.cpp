#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../components/adapters/ConfigsBuilder.h"
#include "../components/adapters/Transceiver.h"
#include "../components/adapters/FreeRTOSTimer.h"

#include "../components/application/commands/InitializeCommandHandler.h"
#include "../components/application/commands/ApplyCommandHandler.h"
#include "../components/application/commands/Command.h"
#include "../components/application/commands/ApplyWithChasingCommandHandler.h"



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
    FreeRTOSTimer timer;

    InitializeCommandHandler initializationHandlerOne(transceiverOne, timer);
    initializationHandlerOne.execute(Command::from(0, 0, 0, 13));

    ApplyWithChasingCommandHandler handlerOne(transceiverOne, timer);

    /*
        # -------------------------
        # STRIP 2
        # -------------------------
    */

    ConfigsBuilder configsTwo = baseConfigs.gpioNum(GPIO_NUM_5);
    Transceiver transceiverTwo(configsTwo.build());
    transceiverTwo.setupConfigs();
    transceiverTwo.turnOnTransmitter();
    InitializeCommandHandler initializationHandlerTwo(transceiverTwo, timer);
    initializationHandlerTwo.execute(Command::from(0, 0, 0, 13));

    ApplyCommandHandler handlerTwo(transceiverTwo, timer);

    while(true) {
        initializationHandlerOne.execute(Command::from(0, 0, 0, 13));
        handlerTwo.execute(Command::from(0, 255, 0, 13));
        handlerOne.execute(Command::from(0, 255, 0, 13));
        timer.wait(10);
    }

    return 0;
}

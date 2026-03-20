#pragma once

#include "../ports/IPixelsSender.h"
#include "../ports/ITimer.h"
#include "InitializeCommand.h"
#include "Command.h"
#include "CommandHandler.h"

class InitializeCommandHandler : public CommandHandler {
    public:
        InitializeCommandHandler(IPixelsSender& sender, ITimer& timer);
        void execute(const Command& command) override;
};
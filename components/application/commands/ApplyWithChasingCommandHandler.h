#pragma once

#include "../ports/IPixelsSender.h"
#include "../ports/ITimer.h"
#include "Command.h"
#include "CommandHandler.h"

class ApplyWithChasingCommandHandler : public CommandHandler {
    public:
        ApplyWithChasingCommandHandler(IPixelsSender& sender, ITimer& timer);
        void execute(const Command& command) override;
};
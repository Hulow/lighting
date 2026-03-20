#pragma once

#include "../ports/IPixelsSender.h"
#include "../ports/ITimer.h"
#include "Command.h"
#include "CommandHandler.h"

class ApplyCommandHandler : public CommandHandler {
    public:
        ApplyCommandHandler(IPixelsSender& sender, ITimer& timer);
        void execute(const Command& command) override;
};
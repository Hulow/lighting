#pragma once

#include "../ports/IPixelsSender.h"
#include "../ports/ITimer.h"
#include "Command.h"

class CommandHandler {
    private:
        IPixelsSender& _sender;
        ITimer& _timer;
    public:
        CommandHandler(IPixelsSender& sender, ITimer& timer);
        void execute(const Command& command);
};
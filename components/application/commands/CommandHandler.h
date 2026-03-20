#pragma once

#include "../ports/IPixelsSender.h"
#include "../ports/ITimer.h"
#include "Command.h"

class CommandHandler {
    protected:
        IPixelsSender& _sender;
        ITimer& _timer;
    public:
        CommandHandler(IPixelsSender& sender, ITimer& timer);
        virtual void execute(const Command& command) = 0;
};
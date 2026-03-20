#pragma once

#include "../ports/IPixelsSender.h"
#include "../ports/ITimer.h"
#include "TurnOnStripWithChasingCommand.h"

class TurnOnStripWithChasingCommandHandler {
    private:
        IPixelsSender& _sender;
        ITimer& _timer;
    public:
        TurnOnStripWithChasingCommandHandler(IPixelsSender& sender, ITimer& timer);
        void execute(const TurnOnStripWithChasingCommand& command);
};
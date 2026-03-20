#pragma once

#include "../ports/IPixelsSender.h"
#include "../ports/ITimer.h"
#include "ApplyWithChasingCommand.h"

class ApplyWithChasingCommandHandler {
    private:
        IPixelsSender& _sender;
        ITimer& _timer;
    public:
        ApplyWithChasingCommandHandler(IPixelsSender& sender, ITimer& timer);
        void execute(const ApplyWithChasingCommand& command);
};
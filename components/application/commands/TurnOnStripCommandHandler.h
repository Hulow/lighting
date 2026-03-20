#pragma once

#include "../ports/IPixelsSender.h"
#include "TurnOnStripCommand.h"

class TurnOnStripCommandHandler {
    private:
        IPixelsSender& _sender;
    public:
        TurnOnStripCommandHandler(IPixelsSender& sender);
        void execute(const TurnOnStripCommand& command);
};
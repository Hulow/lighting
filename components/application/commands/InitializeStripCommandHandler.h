#pragma once

#include "../ports/IPixelsSender.h"
#include "InitializeStripCommand.h"

class InitializeStripCommandHandler {
    private:
        IPixelsSender& _sender;
    public:
        InitializeStripCommandHandler(IPixelsSender& sender);
        void execute(const InitializeStripCommand& command);
};
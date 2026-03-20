#pragma once

#include "../ports/IPixelsSender.h"
#include "InitializeCommand.h"

class InitializeCommandHandler {
    private:
        IPixelsSender& _sender;
    public:
        InitializeCommandHandler(IPixelsSender& sender);
        void execute(const InitializeCommand& command);
};
#pragma once

#include "../ports/IPixelsSender.h"
#include "ApplyCommand.h"

class ApplyCommandHandler {
    private:
        IPixelsSender& _sender;
    public:
        ApplyCommandHandler(IPixelsSender& sender);
        void execute(const ApplyCommand& command);
};
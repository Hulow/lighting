#include "InitializeCommandHandler.h"
#include "../domain/Strip.h"
#include "../domain/services/SymbolsConverter.h"
#include "InitializeCommand.h"

InitializeCommandHandler::InitializeCommandHandler(IPixelsSender& sender) : _sender(sender) {};

void InitializeCommandHandler::execute(const InitializeCommand& command) {
    Strip strip = Strip::init(command.getLedsCount());
    SymbolsConverter converter;
    converter.toSymbols(strip.getLeds());
    _sender.transmit(converter.getSymbols());
}
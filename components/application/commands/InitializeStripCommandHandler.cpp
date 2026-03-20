#include "InitializeStripCommandHandler.h"
#include "../domain/Strip.h"
#include "../domain/services/SymbolsConverter.h"
#include "InitializeStripCommand.h"

InitializeStripCommandHandler::InitializeStripCommandHandler(IPixelsSender& sender) : _sender(sender) {};

void InitializeStripCommandHandler::execute(const InitializeStripCommand& command) {
    Strip strip = Strip::init(command.getLedsCount());
    SymbolsConverter converter;
    converter.toSymbols(strip);
    _sender.transmit(converter.getSymbols());
}
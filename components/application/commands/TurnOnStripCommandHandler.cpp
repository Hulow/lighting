#include "TurnOnStripCommandHandler.h"
#include "../domain/Strip.h"
#include "../domain/services/SymbolsConverter.h"
#include "TurnOnStripCommand.h"

TurnOnStripCommandHandler::TurnOnStripCommandHandler(IPixelsSender& sender) : _sender(sender) {};

void TurnOnStripCommandHandler::execute(const TurnOnStripCommand& command) {
    Strip stripOne = Strip::init(command.getLedsCount());
    SymbolsConverter converter;
    converter.toSymbols(stripOne);
    _sender.transmit(converter.getSymbols());
}
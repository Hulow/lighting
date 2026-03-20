#include "TurnOnStripCommandHandler.h"
#include "../domain/Strip.h"
#include "../domain/services/SymbolsConverter.h"
#include "TurnOnStripCommand.h"

TurnOnStripCommandHandler::TurnOnStripCommandHandler(IPixelsSender& sender) : _sender(sender) {};

void TurnOnStripCommandHandler::execute(const TurnOnStripCommand& command) {
    Strip strip = Strip::init(command.getLedsCount());
    strip.setColor(command.getGreen(), command.getRed(), command.getBlue());
    SymbolsConverter converter;
    converter.toSymbols(strip.getLeds());
    _sender.transmit(converter.getSymbols());
}

#include "ApplyCommandHandler.h"
#include "../domain/Strip.h"
#include "../domain/services/SymbolsConverter.h"
#include "ApplyCommand.h"

ApplyCommandHandler::ApplyCommandHandler(IPixelsSender& sender) : _sender(sender) {};

void ApplyCommandHandler::execute(const ApplyCommand& command) {
    Strip strip = Strip::init(command.getLedsCount());
    strip.setColor(command.getGreen(), command.getRed(), command.getBlue());
    SymbolsConverter converter;
    converter.toSymbols(strip.getLeds());
    _sender.transmit(converter.getSymbols());
}

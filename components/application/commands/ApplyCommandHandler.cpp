#include "ApplyCommandHandler.h"
#include "../domain/Strip.h"
#include "../domain/services/SymbolsConverter.h"
#include "Command.h"
#include "../ports/ITimer.h"

ApplyCommandHandler::ApplyCommandHandler(IPixelsSender& sender, ITimer& timer) : CommandHandler(sender, timer) {};

void ApplyCommandHandler::execute(const Command& command) {
    Strip strip = Strip::init(command.getLedsCount());
    strip.setColor(command.getGreen(), command.getRed(), command.getBlue());
    SymbolsConverter converter;
    converter.toSymbols(strip.getLeds());
    _sender.transmit(converter.getSymbols());
}

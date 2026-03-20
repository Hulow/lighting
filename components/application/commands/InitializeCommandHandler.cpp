#include "InitializeCommandHandler.h"
#include "ApplyCommandHandler.h"
#include "../domain/Strip.h"
#include "../domain/services/SymbolsConverter.h"
#include "Command.h"

InitializeCommandHandler::InitializeCommandHandler(IPixelsSender& sender, ITimer& timer) : CommandHandler(sender, timer) {};

void InitializeCommandHandler::execute(const Command& command) {
    Strip strip = Strip::init(command.getLedsCount());
    SymbolsConverter converter;
    converter.toSymbols(strip.getLeds());
    _sender.transmit(converter.getSymbols());
}
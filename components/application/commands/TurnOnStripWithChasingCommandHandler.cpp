#include "TurnOnStripWithChasingCommandHandler.h"
#include "../domain/Strip.h"
#include "../domain/Led.h"
#include "../domain/services/SymbolsConverter.h"
#include "TurnOnStripWithChasingCommand.h"

TurnOnStripWithChasingCommandHandler::TurnOnStripWithChasingCommandHandler(IPixelsSender& sender, ITimer& timer) : _sender(sender), _timer(timer) {};

void TurnOnStripWithChasingCommandHandler::execute(const TurnOnStripWithChasingCommand& command) {
    Strip strip = Strip::init(command.getLedsCount());
    strip.setColor(command.getGreen(), command.getRed(), command.getBlue());
    SymbolsConverter converter;
    std::vector<Led> leds;
    _timer.wait(100);
    for (const auto& led : strip.getLeds()) {
        leds.push_back(led);
        converter.toSymbols(leds);
        _sender.transmit(converter.getSymbols());
        _timer.wait(500);
    }
}

#include "TurnOnStripWithChasingCommandHandler.h"
#include "../domain/Strip.h"
#include "../domain/Led.h"
#include "../domain/services/SymbolsConverter.h"
#include "TurnOnStripWithChasingCommand.h"
#include "../domain/services/ChasingPattern.h"

TurnOnStripWithChasingCommandHandler::TurnOnStripWithChasingCommandHandler(IPixelsSender& sender, ITimer& timer) : _sender(sender), _timer(timer) {};

void TurnOnStripWithChasingCommandHandler::execute(const TurnOnStripWithChasingCommand& command) {
    Strip strip = Strip::init(command.getLedsCount());
    strip.setColor(command.getGreen(), command.getRed(), command.getBlue());
    SymbolsConverter converter;
    const std::vector<std::vector<Led>> frames = ChasingPattern::generate(strip.getLeds());
    _timer.wait(100);

    for (auto& frame : frames) {
        converter.toSymbols(frame);
        _sender.transmit(converter.getSymbols());
        _timer.wait(500);
    }
}

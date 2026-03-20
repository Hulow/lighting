#include "CommandHandler.h"
#include "Command.h"

CommandHandler::CommandHandler(IPixelsSender& sender, ITimer& timer) : _sender(sender), _timer(timer) {};

void CommandHandler::execute(const Command& command) {}

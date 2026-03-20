#pragma once

class TurnOnStripCommand {
    private:
        int _ledsCount;
        TurnOnStripCommand(const int& ledsCount) : _ledsCount(ledsCount) {}
    
    public:
        TurnOnStripCommand static from(const int& ledsCount) {
            return TurnOnStripCommand(ledsCount);
        }

        int getLedsCount() const {
            return _ledsCount;
        }
};

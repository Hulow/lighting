#pragma once

class InitializeStripCommand {
    private:
        int _ledsCount;
        InitializeStripCommand(const int& ledsCount) : _ledsCount(ledsCount) {}
    
    public:
        InitializeStripCommand static from(const int& ledsCount) {
            return InitializeStripCommand(ledsCount);
        }

        int getLedsCount() const {
            return _ledsCount;
        }
};

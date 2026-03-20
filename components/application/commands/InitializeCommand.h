#pragma once

class InitializeCommand {
    private:
        int _ledsCount;
        InitializeCommand(const int& ledsCount) : _ledsCount(ledsCount) {}
    
    public:
        InitializeCommand static from(const int& ledsCount) {
            return InitializeCommand(ledsCount);
        }

        int getLedsCount() const {
            return _ledsCount;
        }
};

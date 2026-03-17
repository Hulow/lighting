#include "driver/rmt_tx.h"
#include <cmath>

#include "RMTMapper.h"

RMTMapper::RMTMapper(const int& resolution) : _resolution(resolution) {}

rmt_symbol_word_t RMTMapper::map(const uint32_t& bit) {
    return bit == 1 
    ? rmt_symbol_word_t{ 
        .duration0 = static_cast<uint16_t>(nsToTick(WS2815Timing::T1H)), 
        .level0 = 1, 
        .duration1 = static_cast<uint16_t>(nsToTick(WS2815Timing::T1L)), 
        .level1 = 0 
    } 
    : rmt_symbol_word_t{ 
        .duration0 = static_cast<uint16_t>(nsToTick(WS2815Timing::T0H)), 
        .level0 = 1, 
        .duration1 = static_cast<uint16_t>(nsToTick(WS2815Timing::T0L)), 
        .level1 = 0 
    };
}
uint16_t RMTMapper::nsToTick(uint32_t timing) {
    double ticks = static_cast<double>(timing) * _resolution / 1e9;
    return static_cast<uint16_t>(std::round(ticks));
}

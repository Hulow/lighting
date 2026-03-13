#include "driver/rmt_tx.h"

#include "BitToRMTMapper.h"

BitToRMTMapper::BitToRMTMapper(const int& resolution) : _resolution(resolution) {}

rmt_item32_t BitToRMTMapper::map(const uint8_t& bit) {
    return bit == 1 
    ? rmt_item32_t{ 
        .duration0 = nsToTick(WS2815Timing::T1L), 
        .level0 = 1, 
        .duration1 = nsToTick(WS2815Timing::T1H), 
        .level1 = 0 
    } 
    : rmt_item32_t{ 
        .duration0 = nsToTick(WS2815Timing::T0L), 
        .level0 = 1, 
        .duration1 = nsToTick(WS2815Timing::T0H), 
        .level1 = 0 
    };
}

uint32_t BitToRMTMapper::nsToTick(uint8_t timing) {
    return timing * _resolution / 1000000000;
}

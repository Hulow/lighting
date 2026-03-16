#pragma once

#include "driver/rmt_tx.h"

class RMTConfigBuilder {
private:
    rmt_tx_channel_config_t _config;

public:
    RMTConfigBuilder() { 
        _config = {}; 
    }

    RMTConfigBuilder& gpioNum(gpio_num_t gpio_num) {
        _config.gpio_num = gpio_num;
        return *this;
    }

    RMTConfigBuilder& clock(rmt_clock_source_t clock) { //usually APB clock (80 MHz) This affects timing resolution
        _config.clk_src = clock;
        return *this;
    }

    /*
        The number of symbols per RMT memory block.
        Each RMT “symbol” encodes a high/low pulse. WS2815 requires 24 bits per LED (8 bits per color, RGB).
        Determines how many LEDs you can drive per RMT channel without needing to refill the RMT buffer.
        Typical value: 64 symbols per block is common.
    */

    RMTConfigBuilder& memBlocks(int blocks) { // The number of symbols per RMT memory block.
        _config.mem_block_symbols = blocks;
        return *this;
    }

    /*
        The depth of the transmission queue for the RMT channel.
        ESP32 RMT uses a queue to buffer multiple data blocks. A higher value means you can queue more LED data without waiting.
        4–8 is usually enough unless you have very long strips.
    */

    RMTConfigBuilder& queueDepth(int depth) {
        _config.trans_queue_depth = depth;
        return *this;
    }

    /*
       The time resolution of each RMT tick in Hz.
        WS2815 timing requires ~400–800 ns pulses. This parameter converts your tick count to actual time.
        resolution_hz = 10,000,000 → each tick = 1 / 10 MHz = 100 ns
        To create a 300 ns pulse → 3 ticks
    */

    RMTConfigBuilder& resolutionHz(int hz) {
        _config.resolution_hz = hz;
        return *this;
    }

    rmt_tx_channel_config_t build() const {
        return _config;
    }
};
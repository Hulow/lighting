#pragma once
#include "driver/rmt_tx.h"

class RMTConfigBuilder {
private:
    rmt_tx_channel_config_t _config;

public:
    RMTConfigBuilder() { _config = {}; }

    RMTConfigBuilder& gpio(int gpioNum) {
        _config.gpio_num = static_cast<gpio_num_t>(gpioNum);
        return *this;
    }

    RMTConfigBuilder& memBlocks(int blocks) {
        _config.mem_block_symbols = blocks;
        return *this;
    }

    RMTConfigBuilder& queueDepth(int depth) {
        _config.trans_queue_depth = depth;
        return *this;
    }

    RMTConfigBuilder& resolutionHz(int hz) {
        _config.resolution_hz = hz;
        return *this;
    }

    RMTConfigBuilder& intrPriority(int priority) {
        _config.intr_priority = priority;
        return *this;
    }

    rmt_tx_channel_config_t build() const {
        return _config;
    }
};
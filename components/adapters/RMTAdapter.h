#pragma once

#include "driver/rmt_tx.h"

#include "../application/ports/IPixelsSender.h"

class RMTAdapter : public IPixelsSender {
private:
    // -channel handle to the actual RMT transmitter hardware channel.
    rmt_channel_handle_t _channel;

    // _transmitConfigs is a structure that holds the configuration for your RMT transmitter.
    rmt_tx_channel_config_t _transmitConfigs;
    RMTAdapter();

    esp_err_t transmitConfigs();
    void turnOnTransmitter();

public:
    static RMTAdapter& init();
};
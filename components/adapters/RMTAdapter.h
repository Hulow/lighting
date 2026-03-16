#pragma once

#include "driver/rmt_tx.h"

#include "../application/ports/IPixelsSender.h"
#include "RMTConfigBuilder.h"

class RMTAdapter : public IPixelsSender {
private:
    rmt_tx_channel_config_t _configs;
    rmt_channel_handle_t _channel;
    rmt_tx_channel_config_t _initializationConfigs;
    rmt_transmit_config_t _transmitConfigs;
    int _gpioNum;
    
    esp_err_t transmitConfigs();
    void turnOnTransmitter();

public:
    RMTAdapter(const rmt_tx_channel_config_t& configs);
    void sendRMTItems(
        rmt_encoder_handle_t encoder,
        const void* payload,
        size_t payload_bytes
    );
};
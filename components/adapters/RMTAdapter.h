#pragma once

#include "driver/rmt_tx.h"

#include "../application/ports/IPixelsSender.h"
#include "RMTConfigBuilder.h"

class RMTAdapter : public IPixelsSender {
private:
    rmt_tx_channel_config_t _channelConfigs;
    rmt_channel_handle_t _channel;
    rmt_transmit_config_t _transmitConfigs;
    
    esp_err_t transmitConfigs();
    void turnOnTransmitter();

public:
    RMTAdapter(const rmt_tx_channel_config_t& channelConfigs);
    void sendRMTItems(
        rmt_encoder_handle_t encoder,
        const void* payload,
        size_t payload_bytes
    );
};
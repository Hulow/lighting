#pragma once

#include "driver/rmt_tx.h"

#include "../application/ports/IPixelsSender.h"
#include "RMTEncoder.h"

template <size_t N>
class RMTAdapter : public IPixelsSender {
private:
    rmt_tx_channel_config_t _channelConfigs;
    RMTEncoder<N> _encoder;
    rmt_channel_handle_t _channel;

    void encodeStrip();
    esp_err_t transmitConfigs();
    void turnOnTransmitter();

public:
    RMTAdapter(
        const rmt_tx_channel_config_t& channelConfigs, 
        const std::array<LED, N>& strip
    );
    void sendRMTItems(
        rmt_encoder_handle_t encoder,
        const void* payload,
        size_t payload_bytes
    );
};
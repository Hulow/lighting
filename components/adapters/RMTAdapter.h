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
    rmt_copy_encoder_config_t _encoderConfigs;
    rmt_encoder_handle_t _streamEncoder;
    rmt_transmit_config_t _streamConfigs;

    void setupRulesAndStreamPosition();
    void releaseEncoder();
    void waitForRMTIdle();

public:
    RMTAdapter(
        const rmt_tx_channel_config_t& channelConfigs, 
        const std::array<tempLED, N>& strip
    );
    void encodeStrip();
    esp_err_t transmitConfigs();
    void turnOnTransmitter();
    void sendRMTItems();
};
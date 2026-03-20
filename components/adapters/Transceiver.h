#pragma once

#include "driver/rmt_tx.h"
#include <vector>

#include "../application/ports/IPixelsSender.h"

class Transceiver : public IPixelsSender{
    private: 
        rmt_tx_channel_config_t _channelConfigs;
        rmt_channel_handle_t _channel;
        rmt_copy_encoder_config_t _encoderConfigs;
        rmt_encoder_handle_t _streamEncoder;
        rmt_transmit_config_t _streamConfigs;
        void setupRulesAndStreamPosition();
        void releaseEncoder();
        void waitForRMTIdle();
        void transmitToRMT(const std::vector<rmt_symbol_word_t>& symbols);

    public:
        Transceiver(const rmt_tx_channel_config_t& channelConfigs);
        void setupConfigs();
        void turnOnTransmitter();
        void transmit(const std::vector<Symbol>& symbols);
};
#pragma once

#include "driver/rmt_tx.h"
#include <vector>

class Transceiver {
    private: 
        rmt_tx_channel_config_t _channelConfigs;
        rmt_channel_handle_t _channel;
        rmt_copy_encoder_config_t _encoderConfigs;
        rmt_encoder_handle_t _streamEncoder;
        rmt_transmit_config_t _streamConfigs;
        std::vector<rmt_symbol_word_t> _symbols;
        void setupRulesAndStreamPosition();
        void releaseEncoder();
        void waitForRMTIdle();

    public:
        Transceiver(const rmt_tx_channel_config_t& channelConfigs, const std::vector<rmt_symbol_word_t>& symbols);
        void transmitConfigs();
        void turnOnTransmitter();
        void transmit();
};
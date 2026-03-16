#include "driver/rmt_tx.h"
#include "esp_err.h"
#include <stdio.h>
#include <inttypes.h>

#include "RMTAdapter.h"
#include "RMTConfigBuilder.h"


RMTAdapter::RMTAdapter(const rmt_tx_channel_config_t& configs) : _configs(configs) {
    transmitConfigs();
    turnOnTransmitter();
}

esp_err_t RMTAdapter::transmitConfigs() {
    return rmt_new_tx_channel(&_configs, &_channel);
}

void RMTAdapter::turnOnTransmitter() {
    rmt_enable(_channel);
}

void RMTAdapter::sendRMTItems(
    rmt_encoder_handle_t encoder,
    const void* payload,
    size_t payload_bytes
) {
    _transmitConfigs = {
        .loop_count = 0,
        .flags = {}
    };
    rmt_transmit(
        _channel, 
        encoder, 
        payload, 
        payload_bytes, 
        &_transmitConfigs
    );
}
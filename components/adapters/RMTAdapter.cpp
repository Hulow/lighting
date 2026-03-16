#include "driver/rmt_tx.h"
#include "esp_err.h"
#include <stdio.h>
#include <inttypes.h>

#include "RMTAdapter.h"
#include "RMTConfigBuilder.h"

template <size_t N>
RMTAdapter<N>::RMTAdapter(const rmt_tx_channel_config_t& channelConfigs, const std::array<LED, N>& strip) : _channelConfigs(channelConfigs), _encoder(channelConfigs.resolution_hz, strip) {
    encodeStrip();
    transmitConfigs();
    turnOnTransmitter();
}

template <size_t N>
void RMTAdapter<N>::encodeStrip() {
      _encoder.encodeStrip();
}

template <size_t N>
esp_err_t RMTAdapter<N>::transmitConfigs() {
    return rmt_new_tx_channel(&_channelConfigs, &_channel);
}

template <size_t N>
void RMTAdapter<N>::turnOnTransmitter() {
    rmt_enable(_channel);
}

template <size_t N>
void RMTAdapter<N>::sendRMTItems(
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

template class RMTAdapter<1>;
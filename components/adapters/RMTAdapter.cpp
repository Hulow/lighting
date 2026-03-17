#include "driver/rmt_tx.h"
#include "esp_err.h"
#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "RMTAdapter.h"
#include "RMTConfigBuilder.h"

template <size_t N>
RMTAdapter<N>::RMTAdapter(
    const rmt_tx_channel_config_t& channelConfigs, 
    const std::array<LED, N>& strip
) : 
_channelConfigs(channelConfigs), 
_encoder(channelConfigs.resolution_hz, strip)
{
    _encoderConfigs = {};
    _streamEncoder = nullptr;
    _streamConfigs = {};
    _streamConfigs.loop_count = 0;
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
) {
     auto symbols = _encoder.getSymbols();
    setupRulesAndStreamPosition();

    esp_err_t err = rmt_transmit(
        _channel,
        _streamEncoder,
        symbols.data(),
        symbols.size() * sizeof(rmt_symbol_word_t),
        &_streamConfigs
    );

    if (err != ESP_OK) {
        printf("rmt_transmit failed: %d\n", err);
    }

    waitForRMTIdle();
    releaseEncoder();
}

template <size_t N> 
void RMTAdapter<N>::setupRulesAndStreamPosition() {
    rmt_new_copy_encoder(&_encoderConfigs, &_streamEncoder);

}

template <size_t N> 
void RMTAdapter<N>::releaseEncoder() {
     rmt_del_encoder(_streamEncoder);
}

template <size_t N> 
void RMTAdapter<N>::waitForRMTIdle() {
    rmt_tx_wait_all_done(_channel, portMAX_DELAY);
}

template class RMTAdapter<1>;
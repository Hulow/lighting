#include "driver/rmt_tx.h"
#include "esp_err.h"
#include <stdio.h>
#include <inttypes.h>

#include "RMTAdapter.h"
#include "RMTConfigBuilder.h"

template <size_t N>
RMTAdapter<N>::RMTAdapter(
    const rmt_tx_channel_config_t& channelConfigs, 
    const std::array<LED, N>& strip
) : 
_channelConfigs(channelConfigs), 
_encoder(channelConfigs.resolution_hz, strip)
{}

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
    rmt_copy_encoder_config_t config = {};
    rmt_encoder_handle_t encoder = nullptr;
    rmt_new_copy_encoder(&config, &encoder);

     // Transmit config
    rmt_transmit_config_t transmit_config = {};
    transmit_config.loop_count = 0; // no loop

    // Transmit
    esp_err_t err = rmt_transmit(
        _channel,
        encoder,
        symbols.data(),
        symbols.size() * sizeof(rmt_symbol_word_t), //sizeof(symbols)
        &transmit_config
    );

    if (err != ESP_OK) {
        printf("rmt_transmit failed: %d\n", err);
    }

    rmt_del_encoder(encoder); // cleanup

}

template class RMTAdapter<1>;
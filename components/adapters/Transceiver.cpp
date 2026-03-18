#include "driver/rmt_tx.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"

#include "Transceiver.h"

/* TODO: remove properties from constructor */
Transceiver::Transceiver(const rmt_tx_channel_config_t& channelConfigs) : _channelConfigs(channelConfigs) {
     _encoderConfigs = {};
    _streamEncoder = nullptr;
    _streamConfigs = {};
    _streamConfigs.loop_count = 0;
}

void Transceiver::setupConfigs() {
    rmt_new_tx_channel(&_channelConfigs, &_channel);
}

void Transceiver::turnOnTransmitter() {
    rmt_enable(_channel);
}

/* TODO: Handle errors */
void Transceiver::transmit(const std::vector<rmt_symbol_word_t>& symbols) {
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

void Transceiver::setupRulesAndStreamPosition() {
    rmt_new_copy_encoder(&_encoderConfigs, &_streamEncoder);
}

void Transceiver::releaseEncoder() {
     rmt_del_encoder(_streamEncoder);
}

void Transceiver::waitForRMTIdle() {
    rmt_tx_wait_all_done(_channel, portMAX_DELAY);
}


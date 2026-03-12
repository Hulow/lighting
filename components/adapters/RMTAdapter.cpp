#include "driver/rmt_tx.h"
#include "esp_err.h"

#include "RMTAdapter.h"
#include "RMTConfigBuilder.h"

RMTAdapter::RMTAdapter() {
    _transmitConfigs = RMTConfigBuilder()
                       .gpio(18)
                       .memBlocks(64)
                       .queueDepth(1)
                       .resolutionHz(1'000'000)
                       .intrPriority(0)
                       .build();

    esp_err_t responseCode = transmitConfigs();
    if (responseCode != ESP_OK) {
        //TODO Handle response from driver
    }

   turnOnTransmitter();
}

RMTAdapter& RMTAdapter::init() {
    static RMTAdapter instance;
    return instance;
}

esp_err_t RMTAdapter::transmitConfigs() {
    return rmt_new_tx_channel(&_transmitConfigs, &_channel);
}

void RMTAdapter::turnOnTransmitter() {
    rmt_enable(_channel);
}
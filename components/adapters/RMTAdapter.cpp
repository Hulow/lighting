#include "driver/rmt_tx.h"
#include "esp_err.h"

#include "RMTAdapter.h"

RMTAdapter::RMTAdapter() {
    _transmitConfigs.gpio_num = GPIO_NUM_18;
    _transmitConfigs.mem_block_symbols = 64;
    _transmitConfigs.trans_queue_depth = 1;
    _transmitConfigs.resolution_hz = 1000000;
    _transmitConfigs.intr_priority = 0;

    //check the error code hier
    esp_err_t responseCode = transmitConfigs();
    if (responseCode != ESP_OK) {
        //TODO handle error
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
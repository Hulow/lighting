#include "driver/rmt_tx.h"
#include "esp_err.h"
#include <stdio.h>
#include <inttypes.h>

#include "RMTAdapter.h"
#include "RMTConfigBuilder.h"


RMTAdapter::RMTAdapter(const int& gpioNum) : _gpioNum(gpioNum) {
    _transmitConfigs = RMTConfigBuilder(_gpioNum)
                       .clock(static_cast<rmt_clock_source_t>(RMT_CLK_SRC_APB))
                       .memBlocks(64)
                       .queueDepth(1)
                       .resolutionHz(10'000'000)
                       .build();

    esp_err_t responseCode = transmitConfigs();
    printf("Response code: %d\n", responseCode);

    turnOnTransmitter();
}

esp_err_t RMTAdapter::transmitConfigs() {
    return rmt_new_tx_channel(&_transmitConfigs, &_channel);
}

void RMTAdapter::turnOnTransmitter() {
    rmt_enable(_channel);
}

// verschlussen



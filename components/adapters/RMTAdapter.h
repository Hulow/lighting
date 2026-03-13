#pragma once

#include "driver/rmt_tx.h"

#include "../application/ports/IPixelsSender.h"

class RMTAdapter : public IPixelsSender {
private:
    rmt_channel_handle_t _channel;
    rmt_tx_channel_config_t _transmitConfigs;
    int _gpioNum;
    
    
    esp_err_t transmitConfigs();
    void turnOnTransmitter();

public:
    RMTAdapter(const int& gpioNum);
};
#include "FreeRTOSTimer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void FreeRTOSTimer::wait(const uint32_t& ms) {
    vTaskDelay(pdMS_TO_TICKS(ms));
}
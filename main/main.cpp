#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "../components/adapters/RMTAdapter.h"

constexpr gpio_num_t BLINK_GPIO = GPIO_NUM_2;

extern "C" void app_main() {
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while (true) {
        gpio_set_level(BLINK_GPIO, 1);  // LED ON
        vTaskDelay(500 / portTICK_PERIOD_MS);

        gpio_set_level(BLINK_GPIO, 0);  // LED OFF
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }

    RMTAdapter adapter;
    adapter.init();
}
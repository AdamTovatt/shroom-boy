#include "button.h"
#include "driver/gpio.h"

#define BUTTON_GPIO 10

esp_err_t button_init(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    return gpio_config(&io_conf);
}

bool button_is_pressed(void)
{
    // Button is active low (pressed = 0)
    return gpio_get_level(BUTTON_GPIO) == 0;
}


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <stdio.h>

#include "led.h"
#include "button.h"
#include "solar.h"

void app_main(void)
{
    // Initialize all components
    led_init();
    button_init();
    solar_init();

    bool strobe_state = false;

    while (1)
    {
        bool is_pressed = button_is_pressed();
        int solar_percent = solar_read_percentage();

        printf("Button:%s  Solar:%d%%\n", is_pressed ? "Pressed" : "Released", solar_percent);

        // LED behavior based on light level
        if (solar_percent >= 100)
        {
            // 100%: Strobe mode - flash rapidly at max brightness
            strobe_state = !strobe_state;
            led_set_brightness(strobe_state ? 100 : 0);
            vTaskDelay(pdMS_TO_TICKS(40)); // 40ms interval
        }
        else if (solar_percent >= 50)
        {
            // 50-99%: LED off
            led_set_brightness(0);
            vTaskDelay(pdMS_TO_TICKS(30));
        }
        else
        {
            // 0-50%: LED brightness scales with light level (minimum 3%)
            int brightness = solar_percent;
            if (brightness < 3)
                brightness = 3;
            led_set_brightness(brightness);
            vTaskDelay(pdMS_TO_TICKS(30));
        }
    }
}

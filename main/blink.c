#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"

#define LED_GPIO 7
#define BUTTON_GPIO 10
#define SOLAR_ADC_GPIO 4
#define ADC_CHANNEL ADC_CHANNEL_4 // GPIO4 = ADC1_CH3 on ESP32-C3

void app_main(void)
{
    gpio_config_t io_conf_led = {
        .pin_bit_mask = (1ULL << LED_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE};
    gpio_config(&io_conf_led);

    gpio_config_t io_conf_button = {
        .pin_bit_mask = (1ULL << BUTTON_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&io_conf_button);

    adc_oneshot_unit_handle_t adc_handle;
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1};
    adc_oneshot_new_unit(&init_config, &adc_handle);

    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT};
    adc_oneshot_config_channel(adc_handle, ADC_CHANNEL, &config);

    while (1)
    {
        int button_state = gpio_get_level(BUTTON_GPIO);

        int sum = 0;
        for (int i = 0; i < 32; i++)
        {
            int sample = 0;
            adc_oneshot_read(adc_handle, ADC_CHANNEL, &sample);
            sum += sample;
        }
        int adc_avg = sum / 32;

        int percent = adc_avg * 100 / 2500;
        if (percent > 100)
            percent = 100;
        if (percent < 0)
            percent = 0;

        printf("Button:%s  Solar:%d%%\n", button_state == 0 ? "Pressed" : "Released", percent);

        gpio_set_level(LED_GPIO, button_state == 0 ? 1 : 0);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

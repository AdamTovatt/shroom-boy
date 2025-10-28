#include "solar.h"
#include "esp_adc/adc_oneshot.h"

#define SOLAR_ADC_GPIO 4
#define ADC_CHANNEL ADC_CHANNEL_4 // GPIO4 = ADC1_CH3 on ESP32-C3
#define SAMPLE_COUNT 32
#define MAX_ADC_VALUE 2500

static adc_oneshot_unit_handle_t adc_handle = NULL;

esp_err_t solar_init(void)
{
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };
    esp_err_t ret = adc_oneshot_new_unit(&init_config, &adc_handle);
    if (ret != ESP_OK)
    {
        return ret;
    }

    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    return adc_oneshot_config_channel(adc_handle, ADC_CHANNEL, &config);
}

int solar_read_percentage(void)
{
    int sum = 0;
    for (int i = 0; i < SAMPLE_COUNT; i++)
    {
        int sample = 0;
        adc_oneshot_read(adc_handle, ADC_CHANNEL, &sample);
        sum += sample;
    }
    int adc_avg = sum / SAMPLE_COUNT;

    int percent = adc_avg * 100 / MAX_ADC_VALUE;
    if (percent > 100)
        percent = 100;
    if (percent < 0)
        percent = 0;

    return percent;
}

void solar_deinit(void)
{
    if (adc_handle != NULL)
    {
        adc_oneshot_del_unit(adc_handle);
        adc_handle = NULL;
    }
}


#ifndef LED_H
#define LED_H

#include "esp_err.h"
#include <stdbool.h>

/**
 * Initialize the LED with PWM support
 */
esp_err_t led_init(void);

/**
 * Set the LED brightness
 * @param brightness brightness level from 0 (off) to 100 (full brightness)
 */
void led_set_brightness(int brightness);

#endif // LED_H


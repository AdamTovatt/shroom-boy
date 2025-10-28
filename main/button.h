#ifndef BUTTON_H
#define BUTTON_H

#include "esp_err.h"
#include <stdbool.h>

/**
 * Initialize the button GPIO
 */
esp_err_t button_init(void);

/**
 * Check if the button is currently pressed
 * @return true if pressed, false if released
 */
bool button_is_pressed(void);

#endif // BUTTON_H


#ifndef SOLAR_H
#define SOLAR_H

#include "esp_err.h"

/**
 * Initialize the solar panel ADC
 */
esp_err_t solar_init(void);

/**
 * Read the solar panel voltage as a percentage (0-100%)
 * Takes 32 samples and returns the average
 * @return percentage value from 0 to 100
 */
int solar_read_percentage(void);

/**
 * Cleanup solar panel resources
 */
void solar_deinit(void);

#endif // SOLAR_H


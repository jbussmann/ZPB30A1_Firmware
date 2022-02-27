#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include <stdint.h>

typedef enum {
    DP_TOP,
    DP_BOT
} display_t;

void disp_char(uint8_t position, uint8_t c, uint8_t dot, uint8_t pin);
void disp_leds(uint8_t leds);
void disp_brightness(uint8_t brightness, uint8_t pin);

#endif

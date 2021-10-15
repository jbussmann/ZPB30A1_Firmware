#include "utils.h"
#include "systick.h"
#include "config.h"

void delay10ms(uint32_t d)
{
    uint32_t start = systick;
    while ((uint32_t)(systick - start) < d * (F_SYSTICK/100));
}

void delay_ms(uint16_t ms)
{
    while (ms--)
    {
        _delay_us(1000);
    }
}

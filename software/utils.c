#include "utils.h"
#include "timer.h"
#include "config.h"

void delay10ms(uint32_t d)
{
	uint32_t start = systick;
	while ((uint32_t)(systick - start) < d * (F_SYSTICK/100));
}

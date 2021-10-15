#ifndef _TIMER_H_
#define _TIMER_H_
#include <stdint.h>
void systick_init();
extern volatile uint32_t systick;
#define SYSTICK_COUNT 1
#define SYSTICK_OVERFLOW 2
extern volatile uint8_t systick_flag; /* Gets set when the systick IRQ is
    executed. Reset in main loop after all events are handled. */
#endif

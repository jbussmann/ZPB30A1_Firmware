#include "systick.h"
#include "config.h"
#include "inc/stm8s_tim2.h"
#include "inc/stm8s_itc.h"

volatile uint32_t systick = 0;
volatile uint8_t systick_flag = 0;

void systick_init()
{
    #define SYSTICK_PRESCALER 8
    #define SYSTICK_RELOAD (F_CPU / F_SYSTICK / SYSTICK_PRESCALER)
    TIM2->PSCR   = TIM2_PRESCALER_8;
    TIM2->ARRH   = SYSTICK_RELOAD >> 8;
    TIM2->ARRL   = SYSTICK_RELOAD & 0xff;
    TIM2->IER    = TIM2_IER_UIE;
    TIM2->CR1    = TIM2_CR1_CEN;
}
//TODO: IRQ priorities
void systick_irq() __interrupt(ITC_IRQ_TIM2_OVF)
{
    if (systick_flag & SYSTICK_COUNT) {
        systick_flag |= SYSTICK_OVERFLOW;
    }
    systick_flag |= SYSTICK_COUNT;
    systick++;
    TIM2->SR1 &= ~TIM2_SR1_UIF;
}

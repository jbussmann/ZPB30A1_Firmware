#ifndef _LOAD_H_
#define _LOAD_H_
#include <stdbool.h>
#include <stdint.h>
#include "settings.h"

//NOTE: Keep this enum in sync with the messages in ui_error_handler()!
typedef enum {
    ERROR_NONE,
    ERROR_POLARITY, // input polarity reversed
    ERROR_OVERVOLTAGE, // input voltage to high
    ERROR_OVERLOAD, // input can't supply the required current
    ERROR_MAX_POWER, // power > POW_ABS_MAX and max_power_action == MAX_P_OFF
    ERROR_OVERTEMPERATURE, // heat sink temperature to high
    ERROR_POWER_SUPPLY, // supply voltage to low
    ERROR_TIMER_OVERFLOW, // timer tick lost
    ERROR_INTERNAL, // other internal error
    ERROR_COMMAND, // invalid command received
} error_t;
extern error_t error;

typedef enum {
    CAL_NONE,
    CAL_CURRENT,
} calibration_t;

typedef enum {
    DISABLE_USER,
    DISABLE_ERROR,
    DISABLE_CUTOFF,
} disable_reason_t;

extern bool load_active;
extern bool load_regulated;
extern uint8_t load_disable_reason;
extern calibration_t calibration_step;
extern uint16_t calibration_value;

/* Current setpoint after all constraints are taken into account. */
extern uint16_t current_setpoint;
extern uint32_t mAmpere_seconds;
extern uint32_t mWatt_seconds;


void load_init();
void load_timer();
void load_enable();
void load_disable(uint8_t reason);

#endif

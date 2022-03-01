#ifndef _CONFIG_H
#define _CONFIG_H_

// Hardware configuration:
// #define DISP_DRIVER_ET6226
// #define MAX_POWER_110W

// F_xxx is in Hz
#define F_CPU 16000000L
#define F_SYSTICK 100

#define BAUDR 115200L

#define F_DISPLAY_BLINK 15
#define F_UI_SWITCH_DISPLAY 0.2
#define F_UI_UPDATE_DISPLAY 2

#define BRIGHTNESS_BRIGHT 4
#define BRIGHTNESS_DIM 2

/* F_POWER_CALC must be an integer 1 <= f <= F_SYSTICK and an
   integer divider of F_SYSTICK */
#define F_POWER_CALC 100
#define F_FAN 5
#define F_BEEP_ERROR 2
#define F_BEEP_CUTOFF 5
#define F_BEEP_KHZ 1 // 1, 2 or 4
#define F_LOG 5

#define VOLT_MIN 500 //mV
#define VOLT_MAX 30000 //mV
#define VOLT_DOT_OFFSET 3

#define CUR_MIN 200 //mA
#define CUR_MAX 10000 //mA
#define CUR_DOT_OFFSET 3

#define POW_MIN 1 //mW
#define POW_DOT_OFFSET 3

#ifdef MAX_POWER_110W
#define POW_MAX 110000 //mW: maximum settable power
#define POW_ABS_MAX 115000 //mW: Current at which the load current is reduced
#else
#define POW_MAX 60000 //mW: maximum settable power
#define POW_ABS_MAX 65000 //mW: Current at which the load current is reduced
#endif

/* Usable range:
   Rmin = 1V / 10A = 0.1 Ohm
   Rmax = 30V / 0.2A = 150 Ohm */
#define R_MIN 10 //10*mOhm
#define R_MAX 15000 //10*mOhm
#define R_DOT_OFFSET 2

#define AS_DOT_OFFSET 3
#define WS_DOT_OFFSET 3

/* Defintion of t and m:
   PWM = (current *  m - t) / 2^16 */
#define LOAD_CAL_T 8821987L
#define LOAD_CAL_M 350445L

/* Maximum: 64 */
#define ADC_SAMPLES_PER_MEASUREMENT 64
#define ADC_NUM_CHANNELS 4
#define ADC_CH_TEMPERATURE 0
#define ADC_CH_LOAD 1
#define ADC_CH_SENSE 2
#define ADC_CH_12V 3


/* Calibration data: hardware/temperature.ods */
#define ADC_CAL_TEMP_M 42
#define ADC_CAL_TEMP_T 64014
/* 12V mesurement Voltage divider: 1/3
   V12V in mV = ADC * 5Vref * 3 / 2^16 * 1000mV/V = ADC * 15000 / 2^16 */
#define ADC_CAL_12V 15080

/* Defintion of t and m:
   result = (ADC - t) * m / 2^16
*/
#define ADC_CAL_LOAD_T 1246
#define ADC_CAL_LOAD_M 41430
#define ADC_CAL_SENSE_T 1326
#define ADC_CAL_SENSE_M 36546

/* ADC value at which reverse voltage protection is triggered. */
#define ADC_LOAD_MIN  100 // ADC counts
#define ADC_SENSE_MIN 100 // ADC counts
#define ADC_12V_MIN 10000 // mV
#define ADC_INPUT_MAX 35000 // mV

#define FAN_TEMPERATURE_OTP_LIMIT 850 // * 0.1°C
#define FAN_TEMPERATURE_FULL 750 // * 0.1°C
#define FAN_TEMPERATURE_LOW  400 // * 0.1°C
#define FAN_ON_OFF_HYSTERESIS 50 // * 0.1°C
#define FAN_ALWAYS_ON 0
#define FAN_PWM_MAX 0xfff
#define FAN_SPEED_LOW ((uint16_t)(FAN_PWM_MAX/20)) // PWM value
#define FAN_SPEED_FULL FAN_PWM_MAX // PWM value. max: 0xffff

// port B
#define PINB_ENC_A (1u<<5)
#define PINB_ENC_B (1u<<4)

// port C
#define PINC_I_SET (1u<<1)
#define PINC_OL_DETECT (1u<<2)
#define PINC_ENC_P (1u<<3)
#define PINC_RUN_P (1u<<4)

#ifdef DISP_DRIVER_ET6226
#define PINC_SDA   (1u << 5)
#define PINC_SCL1  (1u << 6)
#define PINC_SCL2  (1u << 7)
#else
#define PINC_SCL (1u<<5)
#define PINC_SDA1 (1u<<6)
#define PINC_SDA2 (1u<<7)
#endif

// port D
#define PIND_FAN (1u<<0)
#define PIND_SWIM (1u<<1)
#define PIND_BUS_F (1u<<2)
#define PIND_V_OK (1u<<3)
#define PIND_BEEPER (1u<<4)
#define PIND_TX (1u<<5)
#define PIND_RX (1u<<6)
#define PIND_TLI (1u<<7)

// port E
#define PINE_ENABLE (1u<<5)
#define GPIO_DISPLAY GPIOC

#ifdef DISP_DRIVER_ET6226
#define DP_TOP_PIN PINC_SCL2
#define DP_BOT_PIN PINC_SCL1
#else
#define DP_TOP_PIN PINC_SDA2
#define DP_BOT_PIN PINC_SDA1
#endif

#define LED_V       0x01
#define LED_AH      0x02
#define LED_WH      0x04
#define LED_A       0x08
#define LED_RUN     0x10
#define LED_DIGIT1  0x20
#define LED_DIGIT2  0x40

#endif

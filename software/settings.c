#include "settings.h"
#include "systick.h"
#include "config.h"

#include "inc/stm8s_flash.h"

settings_t settings;


#define _MEM_(mem_addr) (*(volatile uint8_t *)(mem_addr))
uint8_t eeprom_read(uint16_t address) {
    return _MEM_(address + FLASH_DATA_START_PHYSICAL_ADDRESS);
}

void eeprom_write(uint16_t address, uint8_t data) {
    if (eeprom_read(address) == data) return; //Avoid unnecessary writes
    _MEM_(address + FLASH_DATA_START_PHYSICAL_ADDRESS) = data;
}


/* Note: The checksum is placed after the data so when the settings size grows
   The checksum automatically becomes invalid. */
//TODO: Seems to be broken. Needs testing.
static uint8_t settings_calc_checksum(uint8_t *data, uint16_t size)
{
    uint16_t i;
    uint8_t checksum = 0x55;
    for (i = 0; i < size; i++)
    {
        checksum ^= *data++;
    }
    return checksum;
}

void settings_init()
{
    uint16_t addr;
    uint8_t *data = (uint8_t*)(&settings);
    for (addr = 0; addr < sizeof(settings); addr++)
    {
        data[addr] = eeprom_read(addr);
    }
    uint8_t checksum = eeprom_read(sizeof(settings));
    if (checksum != settings_calc_checksum(data, sizeof(settings))) {
        // Invalid checksum => initialize default values
        settings.mode = MODE_CC;
        settings.setpoints[MODE_CC] = 1000;
        settings.setpoints[MODE_CW] = 30000;
        settings.setpoints[MODE_CR] = 50000;
        settings.setpoints[MODE_CV] = 10000;
        settings.beeper_enabled = 1;
        settings.cutoff_enabled = 0;
        settings.cutoff_voltage = 3300;
        settings.current_limit = CUR_MAX;
        settings.max_power_action = MAX_P_LIM;
    }
}

void settings_update()
{
    uint16_t addr;
    uint8_t *data = (uint8_t*)(&settings);
    for (addr = 0; addr < sizeof(settings); addr++)
    {
        eeprom_write(addr, data[addr]);
    }
    uint8_t checksum = settings_calc_checksum(data, sizeof(settings));
    eeprom_write(sizeof(settings), checksum);
    /* TODO: Writing the EEPROM can take several 10s of milliseconds. This leads
    to timer overflow errors. As EEPROM writes only happen while the load is
    inactive this should be no problem and we simply delete the error flags.
    However in the future this write function could be split into smaller parts
    */
    systick_flag &= ~(SYSTICK_OVERFLOW|SYSTICK_COUNT);
}

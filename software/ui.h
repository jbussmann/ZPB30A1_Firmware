#ifndef _UI_H_
#define _UI_H_
#include <stdbool.h>
#include <stdint.h>
#include "menu_items.h"

void ui_init();
void ui_timer();

void ui_mainmenu(uint8_t event, MenuItem *item);
void ui_submenu(uint8_t event, MenuItem *item);
void ui_select_item(uint8_t event, MenuItem *item);
void ui_edit_value(uint8_t event, const MenuItem *item);
void ui_edit_setpoint(uint8_t event, const MenuItem *item);
void ui_run_mode(uint8_t event, const MenuItem *item);
void ui_info_mode(uint8_t event, const MenuItem *item);
void ui_error_handler(uint8_t event, const MenuItem *item);
void ui_clear_counters(uint8_t event, const MenuItem *item);

void ui_activate_load();
void ui_disable_load();
#endif

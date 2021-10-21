#ifndef _MENU_ITEMS_H_
#define _MENU_ITEMS_H_
#include <stdint.h>

typedef struct _MenuItem  MenuItem;
typedef struct _NumericEdit NumericEdit;
typedef void     (*callback_func)        (uint8_t event, const MenuItem *item);

struct _MenuItem {
    /* Label shown in menu. */
    const uint8_t               caption[5];
    /* Associated value Meaning depends on the handler (e.g. used in leaf items as the target variable's value when selecting this items) */
    const uint8_t                 value;
    /* Data pointer. Meaning depends on the handler (e.g. points to the target variable) */
    const void                 *data;
    /* Event handler. Show the UI. */
    const callback_func         handler;
    /* List of subitems. Terminate with 0 entry! */
    const MenuItem             *subitems[];
};

struct _NumericEdit {
    uint16_t *var;
    uint16_t min;
    uint16_t max;
    uint8_t dot_offset;
};

extern const MenuItem menu_main;
extern const MenuItem menu_error;
extern const MenuItem menu_run;
extern const NumericEdit menu_value_edit_CC;
extern const NumericEdit menu_value_edit_CV;
extern const NumericEdit menu_value_edit_CR;
extern const NumericEdit menu_value_edit_CW;

#endif

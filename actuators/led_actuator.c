#include "actuator.h"
#include <stdio.h>

// Internal state
typedef struct {
    int is_on;
} led_state_t;

static void led_activate(void *params) {
    led_state_t *st = (led_state_t *)params;
    st->is_on = 1;
    printf("[LED] ON\n");
}

static void led_deactivate(void *params) {
    led_state_t *st = (led_state_t *)params;
    st->is_on = 0;
    printf("[LED] OFF\n");
}

static int led_status(void *params) {
    led_state_t *st = (led_state_t *)params;
    return st->is_on;
}

// Factory function: return a ready-to-use actuator
actuator_t led_actuator_new(void) {
    static led_state_t state = {0};
    actuator_t a = {
        .params = &state,
        .activate = led_activate,
        .deactivate = led_deactivate,
        .status = led_status
    };
    return a;
}

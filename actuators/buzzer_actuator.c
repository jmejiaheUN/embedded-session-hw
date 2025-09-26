#include "actuator.h"
#include <stdio.h>

typedef struct {
    int is_on;
} buzzer_state_t;

static void buzzer_activate(void *params) {
    buzzer_state_t *st = (buzzer_state_t *)params;
    st->is_on = 1;
    printf("[Buzzer] ON\n");
}

static void buzzer_deactivate(void *params) {
    buzzer_state_t *st = (buzzer_state_t *)params;
    st->is_on = 0;
    printf("[Buzzer] OFF\n");
}

static int buzzer_status(void *params) {
    buzzer_state_t *st = (buzzer_state_t *)params;
    return st->is_on;
}

actuator_t buzzer_actuator_new(void) {
    static buzzer_state_t state = {0};
    actuator_t a = {
        .params = &state,
        .activate = buzzer_activate,
        .deactivate = buzzer_deactivate,
        .status = buzzer_status
    };
    return a;
}

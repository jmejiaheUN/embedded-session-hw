#include <stdio.h>
#include "../actuators/actuator.h"

// forward declarations of factory functions
actuator_t led_actuator_new(void);
actuator_t buzzer_actuator_new(void);

int main(void) {
    actuator_t led = led_actuator_new();
    actuator_t buzzer = buzzer_actuator_new();

    // Use same interface for both
    led.activate(led.params);
    buzzer.activate(buzzer.params);

    printf("LED status: %d\n", led.status(led.params));
    printf("Buzzer status: %d\n", buzzer.status(buzzer.params));

    led.deactivate(led.params);
    buzzer.deactivate(buzzer.params);

    return 0;
}

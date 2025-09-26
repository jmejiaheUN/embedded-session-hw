
#include <stdio.h>
#include "sensor.h"

int main(void) {
    sensor_init();

    for (int i = 0; i < 5; i++) {
        double val = sensor_read();
        printf("Sensor value: %.2f\n", val);
    }

    return 0;
}

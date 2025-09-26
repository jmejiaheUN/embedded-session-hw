// sensor.c
#include "sensor.h"
#include <stdlib.h>
#include <time.h>

void sensor_init(void) {
    // Seed random number generator
    srand((unsigned int) time(NULL));
}

double sensor_read(void) {
    // Return random value in [0, 100)
    return (double) rand() / RAND_MAX * 100.0;
}

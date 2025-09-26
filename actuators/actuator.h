#ifndef ACTUATOR_H
#define ACTUATOR_H

// Abstract actuator interface
typedef struct {
    void *params;                        // custom state for each actuator
    void (*activate)(void *params);      // turn on
    void (*deactivate)(void *params);    // turn off
    int  (*status)(void *params);        // return 0=off, 1=on
} actuator_t;

#endif // ACTUATOR_H

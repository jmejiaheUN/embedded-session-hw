#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

#include "../sensor/sensor.h"
#include "../actuators/actuator.h"

// Factories implemented in your Exercise 2 files
actuator_t led_actuator_new(void);
actuator_t buzzer_actuator_new(void);

// --- time helpers (monotonic) ----------------------------------------------

static long long now_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL;
}

static void sleep_ms(long ms) {
    struct timespec rq = { .tv_sec = ms / 1000, .tv_nsec = (ms % 1000) * 1000000L };
    while (nanosleep(&rq, &rq) == -1) { /* retry if interrupted */ }
}

// Optional: allow Ctrl+C to exit cleanly during tests
static volatile sig_atomic_t g_stop = 0;
static void on_sigint(int sig) { (void)sig; g_stop = 1; }

// --- controller --------------------------------------------------------------

int main(int argc, char **argv) {
    // Optional args: [threshold] [run_seconds]
    double threshold = 50.0;
    long run_seconds = -1; // <0 means run forever
    if (argc >= 2) threshold = atof(argv[1]);
    if (argc >= 3) run_seconds = atol(argv[2]);

    // Init subsystems
    sensor_init();
    actuator_t led = led_actuator_new();
    actuator_t buzzer = buzzer_actuator_new();

    signal(SIGINT, on_sigint);

    const long SAMPLE_MS = 100;
    const long BUZZER_OFF_MS = 1000;
    const long LED_OFF_MS = 5000;

    long long buzzer_deadline = 0;
    long long led_deadline = 0;

    const long long t0 = now_ms();

    while (!g_stop) {
        long long t = now_ms();
        if (run_seconds >= 0 && (t - t0) >= run_seconds * 1000LL) break;

        // 1) Sample
        double val = sensor_read();

        // 2) Decide & schedule/cancel
        if (val >= threshold) {
            // Immediate ON
            led.activate(led.params);
            buzzer.activate(buzzer.params);

            // Cancel any pending offs
            buzzer_deadline = 0;
            led_deadline = 0;
        } else {
            // Schedule offs if not already scheduled
            if (buzzer_deadline == 0) buzzer_deadline = t + BUZZER_OFF_MS;
            if (led_deadline    == 0) led_deadline    = t + LED_OFF_MS;
        }

        // 3) Execute scheduled deactivations
        if (buzzer_deadline && t >= buzzer_deadline) {
            buzzer.deactivate(buzzer.params);
            buzzer_deadline = 0;
        }
        if (led_deadline && t >= led_deadline) {
            led.deactivate(led.params);
            led_deadline = 0;
        }

        // 4) Log state
        printf("[%lld ms] Sensor=%.2f LED=%d Buzzer=%d\n",
               t - t0, val, led.status(led.params), buzzer.status(buzzer.params));

        // 5) Wait until next 100 ms tick
        sleep_ms(SAMPLE_MS);
    }

    return 0;
}
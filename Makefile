CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Isensor

# Build the Exercise 1 test program
test_sensor: tests/main.c sensor/sensor.c
	$(CC) $(CFLAGS) tests/main.c sensor/sensor.c -o test_sensor

# Remove compiled binaries
clean:
	rm -f test_sensor

test_actuators: actuators/actuator.h actuators/led_actuator.c actuators/buzzer_actuator.c tests/test_actuators.c
	$(CC) $(CFLAGS) -Iactuators $^ -o $@

ctl64: sensor/sensor.c actuators/led_actuator.c actuators/buzzer_actuator.c controller/ctl.c
	$(CC) $(CFLAGS) -m64 -Isensor -Iactuators controller/ctl.c sensor/sensor.c actuators/led_actuator.c actuators/buzzer_actuator.c -o ctl64

ctl32: sensor/sensor.c actuators/led_actuator.c actuators/buzzer_actuator.c controller/ctl.c
	$(CC) $(CFLAGS) -m32 -Isensor -Iactuators controller/ctl.c sensor/sensor.c actuators/led_actuator.c actuators/buzzer_actuator.c -o ctl32

#ifndef SENSOR_H
#define SENSOR_H

// Initializes the sensor (e.g., prepare random generator, open file, etc.)
void sensor_init(void);

// Reads one sample from the sensor.
// Could be random or read from a CSV file.
double sensor_read(void);

#endif // SENSOR_H
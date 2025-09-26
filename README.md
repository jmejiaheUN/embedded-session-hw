# Embedded Systems Programming – Homework

## Overview
This project implements a **closed-loop controller** in C, developed in three stages:

1. **Sensor Library** (`sensor/`)  
   Provides `sensor_init()` and `sensor_read()` that simulate a sensor with random values (can be extended to CSV input).

2. **Actuator Interface** (`actuators/`)  
   Defines a polymorphic interface (`actuator_t`) with function pointers for `activate`, `deactivate`, and `status`.  
   Two backends are implemented: LED and Buzzer.

3. **Controller** (`controller/ctl.c`)  
   Samples the sensor every 100 ms, compares against a threshold, and activates/deactivates actuators:  
   - If value ≥ threshold: LED and buzzer ON immediately (cancel pending offs).  
   - If value < threshold: buzzer OFF after 1 s, LED OFF after 5 s.  
   Uses **monotonic time** and logs sensor + actuator states.

---

## Repository Structure

embedded-session-hw/
├── Makefile
├── README.md
├── actuators/
│   ├── actuator.h
│   ├── buzzer_actuator.c
│   └── led_actuator.c
├── controller/
│   └── ctl.c
├── sensor/
│   ├── sensor.c
│   └── sensor.h
└── tests/
    ├── main.c            # sensor test
    └── test_actuators.c  # actuator test

**Note:** Compiled binaries (e.g., `ctl64`, `test_sensor`, `test_actuators`) are not included in the repo tree above, since they are generated automatically by `make`.

## Build Instructions
The project uses a **Makefile** for reproducibility.

- Build and run sensor test:

  make test_sensor
  ./test_sensor

- Build and run actuator test:
make test_actuators
./test_actuators

- Build 64-bit controller:
make ctl64
./ctl64

- Build 32-bit controller
make ctl32
./ctl32

- Clean binaries:
make clean

# Controller Usage
./ctl64 [threshold] [run_seconds]
 - Example:
  ./ctl64 70 15
# Binary Inspection
file ctl64

## Reflection
- **Compilation vs Linking errors**:  
  - Compilation errors occur when headers are missing or symbols undeclared (e.g., calling `sensor_read` without including `sensor.h`).  
  - Linking errors occur if a symbol is declared but never defined (e.g., `undefined reference to sensor_init`).  

- **Include guards**:  
  Prevent redefinition errors by ensuring headers are only processed once.  

- **Wrappers/Interfaces**:  
  Using `actuator_t` with function pointers allowed LED and Buzzer to be handled polymorphically through the same API.  

## AI Interaction
All AI-assisted steps are documented in **`ai_log.md`**, including:  
- Structuring the repo  
- Clarifying compilation vs linking errors  
- Writing headers with include guards  
- Building the Makefile step by step  
- Implementing sensor, actuators, and controller  

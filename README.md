# STM32F103C8 Custom OS Scheduler JSON Communication System

## Project Overview
This project implements a custom OS scheduler on the STM32F103C8 microcontroller. It integrates JSON parsing and generation to communicate sensor readings and control a relay via USART. The system supports temperature and light sensors with periodic tasks for data acquisition and relay status management.

### Key Features
- Custom OS scheduler for lightweight and efficient task management.
- JSON-based communication for structured data exchange.
- Temperature and light sensor readings.
- Relay control with status feedback.
- Dynamic task periodicity modification through JSON commands.

## System Requirements

### Hardware Requirements
- STM32F103C8 microcontroller.
- Temperature sensor (compatible with the `HTEMP_f32GetTemp()` function).
- Light sensor (compatible with the `HLDR_f32GetReading()` function).
- Relay module for on/off control.


### Software Requirements
- GCC for ARM or equivalent compiler.
- STM32 libraries and custom drivers:
  - RCC (Clock Control)
  - GPIO (Digital I/O)
  - USART (UART Communication)
  - STK (Systick)
  - Timers 
  - ADC (Analog-to-Digital Conversion)
- CJSON library for JSON parsing and generation.


## Architecture and Design

### System Architecture
1. **Custom OS Scheduler**:
   - Lightweight and tailored for the project's needs.
   - Manages periodic tasks for sensor readings and communication.
2. **Peripherals**:
   - ADC for sensor data acquisition.
   - USART for communication with external devices.
   - GPIO for relay control.

### Design Considerations
- **JSON Communication**: Structured data exchange with minimal overhead using the CJSON library.
- **Task Periodicity**: Task intervals can be dynamically adjusted using JSON commands.
- **Scalability**: The architecture supports adding new sensors and actuators with minimal changes.

## Functional Specifications

### Core Functions
1. **Temperature Reading**:
   - **Input**: Periodic task enabled via JSON command.
   - **Output**: Temperature data in JSON format via USART.
   - **JSON Command**:
     - Enable: `{"command":"ENA", "nodeID":"0x80", "data":"NULL"}`
     - Set Periodicity: `{"command":"DUR", "nodeID":"0x80", "data":"<seconds>"}`

2. **Light Reading**:
   - **Input**: Periodic task enabled via JSON command.
   - **Output**: Light intensity data in JSON format via USART.
   - **JSON Command**:
     - Enable: `{"command":"ENA", "nodeID":"0x81", "data":"NULL"}`
     - Set Periodicity: `{"command":"DUR", "nodeID":"0x81", "data":"<seconds>"}`

3. **Relay Control**:
   - **Input**: JSON command for ON/OFF state or status request.
   - **Output**: Relay status feedback in JSON format.
   - **JSON Command**:
     - Enable: `{"command":"ENA", "nodeID":"0x50", "data":"NULL"}`
     - Activate: `{"command":"ACT", "nodeID":"0x50", "data":"<1|0>"}`
     - Status: `{"command":"STA", "nodeID":"0x50", "data":"NULL"}`

### Additional Features
- **Error Handling**: Ensures JSON parsing errors or communication issues are reported.
- **Data Validation**: Validates JSON fields before processing commands.



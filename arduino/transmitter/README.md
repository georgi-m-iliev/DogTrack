# Arduino Sketch for Receiver

## Required libraries

- RF24
- SoftwareSerial (builtin library)

## Schematic

![schematic of transmitter circuit](https://files.georgi-iliev.dev/u/dogtack_transmitter.png)

**NB:** Even though the Arduino Nano has an integrated 3.3V regulator, an external one is needed
to provide enough current for the PA_MAX mode of the RF24 transceiver!
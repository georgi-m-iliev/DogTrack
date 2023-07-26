# Arduino Sketch for Transmitter

## Required libraries

- RF24
- SoftwareSerial (builtin library)

## Schematic

![schematic of receiver circuit](http://files.georgi-iliev.dev/u/dogtrack_receiver.png)

**NB:** Even though the Arduino Nano has an integrated 3.3V regulator, an external one is needed
if you have an intention for the receiver to talk back to the transmitter. If not then it is not needed
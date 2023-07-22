#include "SPI.h"
#include "RF24.h"
#include "nRF24L01.h"
#include "SoftwareSerial.h"

#define CE_PIN 9
#define CSN_PIN 10

#define BLUETOOTH_RX 4
#define BLUETOOTH_TX 3

RF24 radio(CE_PIN, CSN_PIN);
SoftwareSerial bluetooth(BLUETOOTH_RX, BLUETOOTH_TX);

const byte address[6] = "00001";
struct {
  double latitude;
  double longitude;
} payload;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  radio.begin();
  radio.setAutoAck(false);  //(true|false)
  radio.setDataRate(RF24_250KBPS);  //(RF24_250KBPS|RF24_1MBPS|RF24_2MBPS)
  radio.setPALevel(RF24_PA_MIN);  //(RF24_PA_MIN|RF24_PA_LOW|RF24_PA_HIGH|RF24_PA_MAX)
  radio.setPayloadSize(sizeof(payload));
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  if(radio.available()) {
    radio.read(&payload, sizeof(payload));
    Serial.print("Latitude: ");
    Serial.println(payload.latitude, 6);
    Serial.print("Longitude: ");
    Serial.println(payload.longitude, 6);

    bluetooth.print(payload.latitude, 6);
    bluetooth.print(" ");
    bluetooth.print(payload.longitude, 6);
    bluetooth.print('\n');

    Serial.println("Payload sent successfully to bluetooth interface!");
  }
}

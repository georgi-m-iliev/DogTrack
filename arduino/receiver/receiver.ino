#include "SPI.h"
#include "RF24.h"
#include "nRF24L01.h"
#include "SoftwareSerial.h"

#define CE_PIN 9
#define CSN_PIN 10
#define INTERVAL_MS_SIGNAL_LOST 1000
#define INTERVAL_MS_SIGNAL_RETRY 250

RF24 radio(CE_PIN, CSN_PIN);
SoftwareSerial bluetooth(3, 4);

const byte address[6] = "00001";
struct payload {
  double longitude;
  double latitude;
} payload;

unsigned long lastSignalMillis = 0;

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.setAutoAck(false);  //(true|false)
  radio.setDataRate(RF24_250KBPS);  //(RF24_250KBPS|RF24_1MBPS|RF24_2MBPS)
  radio.setPALevel(RF24_PA_MIN);  //(RF24_PA_MIN|RF24_PA_LOW|RF24_PA_HIGH|RF24_PA_MAX)
  radio.setPayloadSize(sizeof(payload));
  radio.openReadingPipe(0, address);
  radio.startListening();
  bluetooth.begin(115200);
}

void loop() {
  unsigned long currentMillis = millis();
  if (radio.available() > 0) {
    radio.read(&payload, sizeof(payload));
    Serial.print("Latitude: ");
    Serial.println(payload.latitude);
    Serial.print("Longitude: ");
    Serial.println(payload.longitude);

    bluetooth.write(&payload);

    lastSignalMillis = currentMillis;
  }
  if (currentMillis - lastSignalMillis > INTERVAL_MS_SIGNAL_LOST) {
    lostConnection();
  }
}

void lostConnection() {
  Serial.println("We have lost connection, preventing unwanted behavior");
  delay(INTERVAL_MS_SIGNAL_RETRY);
}

#include "SPI.h"
#include "RF24.h"
#include "nRF24L01.h"
#include "TinyGPS++.h"
#include "SoftwareSerial.h"

#define CE_PIN 9
#define CSN_PIN 10
#define INTERVAL_MS_TRANSMISSION 250

#define GPS_RX 4
#define GPS_TX 3
#define GPS_BAUD 9600

RF24 radio(CE_PIN, CSN_PIN);
TinyGPSPlus gps;
SoftwareSerial ss(GPS_RX, GPS_TX);

const byte address[6] = "00001";
struct payload {
  double longitude;
  double latitude;
} payload;

void setup() {
  Serial.begin(9600);
  ss.begin(GPS_BAUD);

  Serial.begin(115200);
  radio.begin();
  //Append ACK packet from the receiving radio back to the transmitting radio
  radio.setAutoAck(false);          //(true|false)
  radio.setDataRate(RF24_250KBPS);  //(RF24_250KBPS|RF24_1MBPS|RF24_2MBPS)
  radio.setPALevel(RF24_PA_MAX);    //(RF24_PA_MIN|RF24_PA_LOW|RF24_PA_HIGH|RF24_PA_MAX)
  radio.setPayloadSize(sizeof(payload));
  radio.openWritingPipe(address);
  radio.stopListening();
}
void loop() {
  while (ss.available() > 0) {
    gps.encode(ss.read());
    if (gps.location.isUpdated()) {
      Serial.print("Latitude= ");
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= ");
      Serial.println(gps.location.lng(), 6);

      payload.longitude = gps.location.lng();
      payload.latitude = gps.location.lat();
      radio.write(&payload, sizeof(payload));
      Serial.println("GPS data sent via Radio!");
    }
  }
  delay(INTERVAL_MS_TRANSMISSION);
}

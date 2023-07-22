#include "SPI.h"
#include "RF24.h"
#include "nRF24L01.h"
#include "TinyGPS++.h"
#include "SoftwareSerial.h"

#define CE_PIN 7
#define CSN_PIN 8
#define INTERVAL_MS_TRANSMISSION 250

#define GPS_RX 3
#define GPS_TX 2
#define GPS_BAUD 9600

RF24 radio(CE_PIN, CSN_PIN);
TinyGPSPlus gps;
SoftwareSerial ss(GPS_RX, GPS_TX);

const byte address[6] = "00001";
struct {
  double latitude;
  double longitude;
} payload;

void setup() {
  Serial.begin(9600);
  ss.begin(GPS_BAUD);
  radio.begin();
  //Append ACK packet from the receiving radio back to the transmitting radio
  radio.setAutoAck(false);          //(true|false)
  radio.setDataRate(RF24_250KBPS);  //(RF24_250KBPS|RF24_1MBPS|RF24_2MBPS)
  radio.setPALevel(RF24_PA_HIGH);    //(RF24_PA_MIN|RF24_PA_LOW|RF24_PA_HIGH|RF24_PA_MAX)
  radio.setPayloadSize(sizeof(payload));
  radio.openWritingPipe(address);
  radio.stopListening();
}
void loop() {
  while (ss.available() > 0) {
    gps.encode(ss.read());
    if (gps.location.isUpdated()) {
      payload.latitude = gps.location.lat();
      payload.longitude = gps.location.lng();

      Serial.print("Latitude= ");
      Serial.print(payload.latitude, 6);
      Serial.print(" Longitude= ");
      Serial.println(payload.longitude, 6);

      printTime();

      radio.write(&payload, sizeof(payload));
      Serial.println("GPS data sent via Radio!");
    }
  }
  delay(INTERVAL_MS_TRANSMISSION);
}

void printTime() {
  Serial.print("Time: ");
  if (gps.time.isValid()) {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  } else {
    Serial.println("Not Available");
  }
}
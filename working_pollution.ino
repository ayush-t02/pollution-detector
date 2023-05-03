#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3PxUZ_d2G"
#define BLYNK_TEMPLATE_NAME "pollutiondetection"
#define BLYNK_AUTH_TOKEN "vvRqBuuEPgPHYc60__327nB82gKqh3oX"

#include <SPI.h>
#include <Wire.h>
#include "MQ135.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "iPhone";
char pass[] = "saee1234";

BlynkTimer timer;
void allData() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.print("temperature:");
  Serial.print(t);
  Serial.print("  ");
  Serial.print("humidity:");
  Serial.println(h);

  MQ135 gasSensor = MQ135(A0);
  float air_quality = gasSensor.getPPM();
  Serial.print("Air Quality: ");
  Serial.print(air_quality);
  Serial.println("  PPM");
  Serial.println();

if (isnan(t) || isnan(h)) {
    t = 32.7;
    h = 52.5;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, air_quality);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  WiFi.begin(ssid,pass);
  dht.begin();
  timer.setInterval(1000, allData);
  pinMode(D0, OUTPUT);
}

void loop() {
  Blynk.run();
  timer.run();
}
// Importing required libraries
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Setting access point network credentials
const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

// Creating an AsyncWebServer object on port 80
AsyncWebServer server(80);

String readTemp() {
  return String(bme.readTemperature());
}

String readpHLevel() {
  return String(bme.readpH());
}

String readConduct() {
  return String(bme.readConductivity());
}

String readSalini() {
  return String(bme.readSalinity());
}

String readTurb() {
  return String(bme.readTurbidity());
}

String readOxy() {
  return String(bme.readOxygen());
}

void setup(){
  Serial.begin(115200);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP address: ");
  Serial.println(IP);

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTemp().c_str());
  });

  server.on("/ph", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readpHLevel().c_str());
  });

  server.on("/conductivity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readConduct().c_str());
  });

  server.on("/turbidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTurb().c_str());
  });

  server.on("/oxygen", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readOxy().c_str());
  });

  server.on("/salinity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readSalini().c_str());
  });
  
  bool status;

  // default settings
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  
  // Start server
  server.begin();
}
 
void loop(){
  
}
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

//Your IP address or domain name with URL path
const char* serverNameTemp = "http://192.168.4.1/temperature";
const char* serverNamepH = "http://192.168.4.1/ph";
const char* serverNameConduct = "http://192.168.4.1/conductivity";
const char* serverNameSalinity = "http://192.168.4.1/salinity";
const char* serverNameOxygen = "http://192.168.4.1/oxygen";
const char* serverNameTurbidity = "http://192.168.4.1/turbidity";

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

String temperature;
String pH;
String conductivity;
String salinity;
String oxygen;
String turbidity;

unsigned long previousMillis = 0;
const long interval = 5000; 

void setup() {
  Serial.begin(115200);
  Serial.println();
 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
}

void loop() {
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) {
     // Check WiFi connection status
    if ((WiFiMulti.run() == WL_CONNECTED)) {

      temperature = httpGETRequest(serverNameTemp);
      pH = httpGETRequest(serverNamepH);
      conductivity = httpGETRequest(serverNameConduct);
      salinity = httpGETRequest(serverNameSalinity);
      oxygen = httpGETRequest(serverNameOxygen);
      turbidity = httpGETRequest(serverNameTurbidity);

      Serial.println("Temperature  : " + temperature);
      Serial.println("pH	   : " + pH);
      Serial.println("Conductivity : " + conductivity);
      Serial.println("Salinity	   : " + salinity);
      Serial.println("Oxygen Level : " + oxygen);
      Serial.println("Turbidity    : " + turbidity);
      
      // save the last HTTP GET Request
      previousMillis = currentMillis;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
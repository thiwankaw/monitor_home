#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "htmlpage.h"

#define DHTPIN            5         // Pin which is connected to the DHT sensor.
// Uncomment the type of sensor in use:
//#define DHTTYPE           DHT11     // DHT 11 
#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
const char* ssid = "<wifi_name>";
const char* password = "wifi_password";
Adafruit_BMP085 bmp;
int n = 0;

ESP8266WebServer server(80);


void handleRoot() {
  n++;
  String s = main_page;
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  float t = event.temperature;
  dht.humidity().getEvent(&event);
  float h = event.relative_humidity;
  int sensorValue = analogRead(A0);
  double c=(5.0/100.0)*(sensorValue-492);

  s.replace("@@@t@@@",String(t));
  s.replace("@@@h@@@",String(h));
  s.replace("@@@t1@@@",String(bmp.readTemperature()));
  s.replace("@@@p1@@@",String(bmp.readPressure()));
  s.replace("@@@s@@@",String(sensorValue));
  s.replace("@@@c@@@",String(c));
  s.replace("@@@n@@@",String(n));
  server.send(200, "text/html", s);
}



void setup(void){
  Wire.begin(D2,D3);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

// Initialize device.
  dht.begin();

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }

  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  if (WiFi.status() == 6)
  {
    ESP.reset();
  }
  server.handleClient();
}
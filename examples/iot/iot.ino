#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include "Adafruit_MCP9808.h"

#define LICHT A0//Grove - Light Sensor is connected to A0 of Arduino
#define VIJFMINUTEN 300000
#define TWEEMINUTEN 120000
//Ingave netwerk

unsigned long time_1 = 0;
unsigned long time_2 = 0;
const char* ssid     = "telenet-apn-a26e6";
const char* password = "2yao18psxaqd";

//Ingave website voor ingave 
const char* serverName = "http://11800025.pxl-ea-ict.be/IOT/insertdb.php";

// API code , moet ook in de php code zitten. 
String apiKeyValue = "tPmAT5Ab3j7F9";

//object temperatuursensor
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
void setup() {
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  Serial.println("Verbinding aan het maken");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.print("Is verbonden met het netwerk");
  Serial.println(WiFi.localIP());

  if (!tempsensor.begin(0x18)) {
    Serial.println("Sensor is niet gevonden");
    while (1);
  }
}

void loop() {
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    float temperatuur = tempsensor.readTempC() ; 
    int analoog = analogRead(LICHT);
   
    // Prepare your HTTP POST request data
     if(millis() > time_1 + VIJFMINUTEN){
     time_1 = millis();
     String httpRequestData = "api_key=" + apiKeyValue + "&id=" + 1 + "&value=" + temperatuur + " ";
     Serial.println(httpRequestData);
     int httpResponseCode = http.POST(httpRequestData);
     }

     else if(millis() > time_2 + TWEEMINUTEN){
     time_2 = millis();
     String httpRequestData2 = "api_key=" + apiKeyValue + "&id=" + 2 + "&value=" + analoog + " ";
     int httpResponseCode = http.POST(httpRequestData2);
     Serial.println(httpRequestData2);
     }
    http.end();
  }
}

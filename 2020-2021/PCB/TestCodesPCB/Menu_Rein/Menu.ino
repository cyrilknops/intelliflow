#include "WiFi.h"

int incoming = 0;
int old = 0;


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop() {
  incoming = 0;
  if (Serial.available() > 0) {
    incoming = Serial.read();
    if(incoming != old and incoming != 10)
    {
      readInput(incoming);
    }
   old = incoming;
  }
}
void readInput(int in){
    if(in == 49){
    Serial.println("Menu:");
    Serial.println("2. Scan for wifi networks");
    Serial.println("3. connect to wifi network");
    Serial.println("4. get ADC sensor(s) input");
    Serial.println("5. get DAC sensor(s) input");
    }
    else if (in == 50){
       Serial.println("scan start");
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }
    Serial.println("");
    
    }
    else if (in == 51){Serial.println("connect to wifi network...");}
    else if (in == 52){Serial.println("get ADC sensor(s) input...");}
    else if (in == 53){Serial.println("get DAC sensor(s) input...");}
    else{
    Serial.println("Unknown command");
    }
    
 }

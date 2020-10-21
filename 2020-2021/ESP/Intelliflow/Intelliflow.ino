#include "intelliflow.pb.h"
#include <dht11.h>
#include "pb_common.h"
#include "pb.h"
#include "pb_encode.h"

#include <WiFi.h>
#include <timestamp32bits.h>
#include <PubSubClient.h>
#include "config.h"

//pins
#define DHT11PIN 4


//wifi connection
WiFiClient espClient;

// parameters
uint32_t celsius = 0;
uint32_t fahrenheit = 0;
uint32_t bar = 0;
uint32_t psi = 0;
uint32_t ph = 0;
uint32_t ppm = 0;
uint32_t volts = 0;
uint32_t current = 0;
uint32_t cmp = 0;
uint32_t timestamp = 0;


//mqtt
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
uint32_t  messages = 0;
uint32_t succes = 0;

//protobuf
uint8_t buffer[10];
int values = 0;

//temp sensor
dht11 DHT11;
Loggings_Log message = Loggings_Log_init_zero ;
pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

void setup() {
  //status led
  pinMode(BUILTIN_LED, OUTPUT);
  //serial
  Serial.begin(115200);

  //wifi
  setup_wifi();
  //mqtt
  client.setServer(mqtt_server, 24075);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }else{
    celsius = DHT11.read(DHT11PIN);
    fahrenheit = 1.8 * celsius + 32;  //celsius converted to fahrenheit --> fahrenheit=1.8*celsius+32
    bar = 0;                          
    psi = 0;
    ph = 0;
    ppm = 0;
    volts = 0;
    current = 0;
    cmp = 0;
    timestamp = timestamp32bits();
    
    message.cesluis = celsius;
    message.fahrenheit = fahrenheit;
    message.bar = bar;
    message.psi = psi;
    message.ph = ph;
    message.ppm = ppm;
    message.volts = volts;
    message.current = current;
    message.cmp = cmp;
    message.timestamp = timestamp;
    
    if(encode())
      pub();
  }
  delay(1000);
}

bool encode(){
  if(!pb_encode(&stream, Loggings_Log_fields, &message)){
      Serial.println("Failed to encode");
      return false;
  }
  return true;
}
bool pub(){
  messages++;
  if (!client.publish("device", buffer, stream.bytes_written)) {
    Serial.println(F("Publishing Failed"));
    resetValues();
  } else {
    succes++;
    Serial.println(F("Publish succesful"));
    resetValues();
  }
  /*
  Serial.print("succes-rate: ");
  Serial.print(succes);
  Serial.print("/");
  Serial.println(messages);
  */
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void resetValues() {
  message.cesluis = 0;
  message.fahrenheit = 0;
  message.bar = 0;
  message.psi = 0;
  message.ph = 0;
  message.ppm = 0;
  message.volts = 0;
  message.current = 0;
  message.cmp = 0;
  message.timestamp = 0;
  memset(buffer, 0, sizeof(buffer));
  stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
}

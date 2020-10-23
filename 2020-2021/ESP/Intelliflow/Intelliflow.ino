#include <pb.h>
#include <pb_common.h>
#include <pb_decode.h>
#include <pb_encode.h>

#include "intelliflow.pb.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"

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
intelliflow_Sensor sensor = intelliflow_Sensor_init_zero;
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
    celsius = 25;
    fahrenheit = 1.8 * celsius + 32;  //celsius converted to fahrenheit --> fahrenheit=1.8*celsius+32
    bar = 3;                          
    psi = 1800;
    ph = 7;
    ppm = 4;
    volts = 2;
    current = 1;
    cmp = 3;
    timestamp = 0;

    sensor.value=celsius;
    char* value = "1";
    sensor.id.arg = value;
    sensor.unit=intelliflow_Sensor_units_celsius;    
    if(encode())
      pub();
  }
  delay(1000);
}

bool encode(){
  if(!pb_encode(&stream, intelliflow_Sensor_fields, &sensor)){
      Serial.println("Failed to encode");
      return false;
  }
  return true;
}
bool pub(){
  messages++;
  if (!client.publish("sensor", buffer, stream.bytes_written)) {
    Serial.println(F("Publishing Failed"));
    resetValues();
  } else {
    succes++;
    Serial.println(F("Publish succesful"));
    resetValues();
  }
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
  char* value = "";
  sensor.id.arg = value;
  sensor.value = 0;
  sensor.unit=intelliflow_Sensor_units_celsius;
  memset(buffer, 0, sizeof(buffer));
  stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
}

#include <EEPROM.h>
#include <WiFi.h>
#include <PubSubClient.h>
//protobuf includes
#include <pb.h>
#include <pb_common.h>
#include <pb_encode.h>
#include "intelliflow.pb.h"
//sensor includes
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "Adafruit_SGP30.h"
//CLI  
#define LINE_BUF_SIZE 128   //Maximum input string length
#define ARG_BUF_SIZE 64     //Maximum argument string length
#define MAX_NUM_ARGS 8      //Maximum number of arguments
bool error_flag = false;
char line[LINE_BUF_SIZE];
char args[MAX_NUM_ARGS][ARG_BUF_SIZE];
int cmd_help();
int cmd_wifi();
int cmd_mqtt();
int (*commands_func[])(){
    &cmd_help,
    &cmd_wifi,
    &cmd_mqtt,
    &cmd_cli,
    
};
const char *commands_str[] = {
    "help",
    "wifi",
    "mqtt",
    "cli"
};
int num_commands = sizeof(commands_str) / sizeof(char *);
bool cliMode;
//Sensors
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
Adafruit_SGP30 sgp;
//Settings
String ssid;
String password;
String url;
String port;
//wifi connection
WiFiClient espClient;
//mqtt
int trys = 0;
int wifiTrys = 0;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
uint32_t  messages = 0;
uint32_t succes = 0;
//protobuf
int values = 0;

void setup() {
  //status led
  pinMode(BUILTIN_LED, OUTPUT);
  //serialg
  Serial.begin(115200);
  EEPROM.begin(400);
  ssid = EEPROM.readString(0);
  password = EEPROM.readString(100);
  url = EEPROM.readString(200);
  port = EEPROM.readString(300);
  Serial.println("Settings:");
  Serial.print(ssid);
  Serial.print("|");
  Serial.println(password);
  Serial.println("-----------------------");
  Serial.print(url);
  Serial.print("|");
  Serial.println(port);
  Serial.println("-----------------------");
  Serial.println("Type cli to change these settings");
  cli_init();
  
  sgp.begin();
  tcs.begin();

  //wifi
  setup_wifi();
  //mqtt
  client.setServer(url.c_str(), port.toInt());
  client.setCallback(callback);
}

void loop() {
  if(!cliMode){
    if (!client.connected()) {
      if(trys < 2){
        reconnect();
      }
      else{
        Serial.println("failed:");
        Serial.println("There is a problem with mqtt, change the settings");
        cliMode = true;
        cmd_mqtt();
      }
    }else{    
      RGB_Sensor();
      Gas_Sensor();
      Temp_Sensor();
      delay(1000);
    } 
  }
    my_cli();
}

bool encode(intelliflow_Sensor &sensor){
  uint8_t buffer[50];
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  if(!pb_encode(&stream, intelliflow_Sensor_fields , &sensor)){
      Serial.println("Failed to encode");
  }else{
    for(int i = 0; i<stream.bytes_written; i++){
      Serial.printf("%02X",buffer[i]);
    }
    Serial.println("");
    if (!client.publish("sensor", buffer, stream.bytes_written)) {
        Serial.println(F("Publishing Failed"));
    } else {
        succes++;
        Serial.println(F("Publish succesful"));
    }
  }
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid.c_str(), password.c_str());

  while (WiFi.status() != WL_CONNECTED && !cliMode) {
    delay(500);
    Serial.print(".");
    wifiTrys++;
    if(wifiTrys >= 10){
      cliMode = true;
      Serial.println("");
      Serial.println("Could not connect, change wifi settings");
      cmd_wifi();
    }
  }

  randomSeed(micros());
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
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
  
  while (!client.connected() && trys <= 1) {
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
        delay(5000);
        trys++;
    }
  }
}

void RGB_Sensor(){ 
  uint16_t r, g, b, c, colorTemp, lux;
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  
  intelliflow_Sensor sensor = intelliflow_Sensor_init_zero;
  strcpy(sensor.id, "1");
  sensor.value=colorTemp;
  strcpy(sensor.unit, "K");   
  Serial.println(sensor.value);
  Serial.println(sensor.id);
  Serial.println(sensor.unit);
  encode(sensor);
  Serial.println("-------------------------");
}

void Gas_Sensor(){
  if (! sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return;
  }
  
  intelliflow_Sensor sensor = intelliflow_Sensor_init_zero;
  strcpy(sensor.id, "1");
  sensor.value=sgp.eCO2;
  strcpy(sensor.unit, "ppm");   
  Serial.println(sensor.value);
  Serial.println(sensor.id);
  Serial.println(sensor.unit);
  encode(sensor);
  Serial.println("-------------------------");
}

void Temp_Sensor(){
  int reading = analogRead(25);
  float Temp   = (reading - 509)/6.45;
  
  intelliflow_Sensor sensor = intelliflow_Sensor_init_zero;
  strcpy(sensor.id, "1");
  sensor.value=round(Temp);
  strcpy(sensor.unit, "°C");   
  Serial.println(sensor.value);
  Serial.println(sensor.id);
  Serial.println(sensor.unit);
  encode(sensor);
  Serial.println("-------------------------");
}

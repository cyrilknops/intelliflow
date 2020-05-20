# Speed test for the ESP32
This project can test for 3 things:
* Wi-Fi connection
* Protobuf conversion
* MQTT connection

## Configuration
In the config.h file change the following things
```c
const char* ssid = "Your_ssid";
const char* password = "Your_pwd";
const char* mqtt_server = "intelliflow.pxl-ea-ict.be"; //change this to your mqtt broker adress
```
## How to run
Open the project in arduino ide and upload to the ESP32

# instructions

Add a config.h to the root of your arduino project containing the following:
``` c++
const char* ssid = "SSID"; //change this to the SSID of your Wi-Fi network
const char* password = "*********"; //change this to the password of your Wi-Fi network
const char* mqtt_server = "home.iwg-it.com"; // change this to your mqtt broker url or ip
const int mqtt_port = 24075; //change this to your mqtt broker port
```

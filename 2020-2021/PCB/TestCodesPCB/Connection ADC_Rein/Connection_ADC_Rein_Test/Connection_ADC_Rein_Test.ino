#include <SPI.h>

#define cs_pin 15
#define drdy_pin 8
#define res_pin 7
#define strt_pin 2

void setup() 
{
 Serial.begin(115200);
 delay (10);
 pinMode(res_pin, OUTPUT);
}

void loop() {
 
 digitalWrite( res_pin, LOW);
 Serial.println("LOW");
 delay(5000);
 digitalWrite( res_pin , HIGH);
 Serial.println("HIGH");
 delay(5000);
}

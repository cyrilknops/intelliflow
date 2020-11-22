#include <Wire.h>

int x = 0;

void setup()
{
Wire.begin(); // Start I2C Bus as Master
Wire.setClock(100000);
}

void loop()
{
Wire.beginTransmission(0x08); // transmit to device #9
Wire.write(x); // sends x
Wire.endTransmission(); // stop transmitting
x++;
if (x > 5) x=0;
delay(500);
}

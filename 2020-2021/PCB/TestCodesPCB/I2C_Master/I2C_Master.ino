// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

#define I2C_SCL 22
#define I2C_SDA 21

void setup()
{
  Serial.begin(9600);
  while (!Serial); //waits for serial terminal to be open, necessary in newer arduino boards.
  
  Wire.begin(0x08); // join i2c bus (address optional for master)
  Wire.setClock(100000);
  
  if(!Wire.begin(0x08))
  {
    Serial.println("PSOC not found");
    while (1);
    delay(500);
  }

   Serial.println("PSOC found!");
  
}

byte x = 0;

void loop()
{
  Wire.beginTransmission(0x08); // transmit to device #4
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting

  x++;
  delay(500);
}

#include <SPI.h>

byte fromSlave ;

int slaveSelect = 5;
char buff[] = "ESP32!";
byte recieve ;

int count = 0;

void setup() {
  pinMode(slaveSelect, OUTPUT);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);//divide the clock by 4
  Serial.begin(9600);
}

void loop() {
  
 for(int i=0; i <sizeof buff; i++)
 {
  digitalWrite(slaveSelect, LOW);
  SPI.transfer(buff[i]);
  digitalWrite(slaveSelect, HIGH); 
  delay(100); 
 } 

 //SPI.transfer(fromSlave); 
 Serial.println(fromSlave);

}

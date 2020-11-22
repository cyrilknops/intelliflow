#include <SPI.h>

byte fromSlave ;

int slaveSelect = 5;
char toSend;

unsigned char sending[]= "ESP32!" ;

short int countTx = 0;

int count = 0;

SPISettings settingsA(1500000, MSBFIRST, SPI_MODE1); 

void shiftArray()
{
  for(int shift = 0 ; shift <= 5 ; shift++)
  {
    sending[shift] = sending[shift] << 1;
  }  
}

void setup() {
  pinMode(slaveSelect, OUTPUT);
  SPI.begin();
  Serial.begin(9600);
  digitalWrite(slaveSelect,HIGH); 
  shiftArray();
}

void loop() {

  SPI.beginTransaction(settingsA);
  digitalWrite(slaveSelect,LOW); 
  
  for(countTx = 0; countTx <= 5 ; countTx++)
  { 
    SPI.transfer(sending[countTx]);
    delay(100);    
  }
  
  digitalWrite(slaveSelect,HIGH); 
  SPI.endTransaction();

 
}

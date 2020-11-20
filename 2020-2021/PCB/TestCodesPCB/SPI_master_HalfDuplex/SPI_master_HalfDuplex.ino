#include <SPI.h>

byte toSend ;
int slaveSelect = 5;
char stringSend[]= "ESP32!";
short int countRx = 0;

SPISettings settingsA(12000000, MSBFIRST, SPI_MODE1); 


void setup() {
  pinMode(slaveSelect, OUTPUT);
  SPI.begin();
  Serial.begin(9600);
  digitalWrite(slaveSelect,HIGH); 
}

void loop() {

  SPI.beginTransaction(settingsA);
  digitalWrite(slaveSelect,LOW); 

  for(countRx = 0 ; countRx <= 6 ; countRx++)
  { 
    toSend  = SPI.transfer(stringSend[countRx]);
    Serial.print(stringSend[4]);
    delay(500);    
  }
  
  digitalWrite(slaveSelect,HIGH); 
  SPI.endTransaction();
 
}

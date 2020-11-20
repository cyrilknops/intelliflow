#include <SPI.h>

byte fromSlave ;

int slaveSelect = 5;
char recieve;
char toSend;
char stringRecieve[5];

char sending = 'A' ;
short int countRx = 0;
short int countTx = 0;

int count = 0;

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
    recieve = SPI.transfer(0);
    toSend  = SPI.transfer(sending);
    Serial.print(recieve);
    delay(500);    
  }
  
  digitalWrite(slaveSelect,HIGH); 
  SPI.endTransaction();

 
}

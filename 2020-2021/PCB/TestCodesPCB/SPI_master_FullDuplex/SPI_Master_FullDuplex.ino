#include <SPI.h>

byte fromSlave ;

int slaveSelect = 5;
char toSend;
char stringRecieve[5];

unsigned char sending[]= "ESP32!" ;

short int countTx = 0;
short int countRx = 0;

int count = 0;

SPISettings settingsA(12000000, MSBFIRST, SPI_MODE1); 

void BitwiseArray()
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
  BitwiseArray();
}

void loop() {

  SPI.beginTransaction(settingsA);
  digitalWrite(slaveSelect,LOW); 
  
  for(countTx = 0, countRx = 0 ; countTx <= 5 , countRx <= 5 ; countTx++, countRx++)
  { 
    stringRecieve[countRx] = SPI.transfer(sending[countTx]);
    Serial.print(stringRecieve[countRx]);
    delay(100);    
  }

  if(stringRecieve[0] == 'P')
  {
  Serial.print('\n');
  }
  digitalWrite(slaveSelect,HIGH); 
  SPI.endTransaction();

 
}

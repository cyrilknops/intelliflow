#include <SPI.h>

#define cs_pin 15
#define drdy_pin 8
#define res_pin 7
#define strt_pin 2

const int ADResetPulse = 1;    
const int ADResetDelay = 1;     

void setup() 
{
 Serial.begin(115200);
 delay (10);
 SPIinitialize(); 
 ADreset();
 ADsetup();
}

void loop() 
{ 
   if (digitalRead(drdy_pin) == 0)
       {
          ADread();
       }
}
 
void ADread()
{
 digitalWrite(cs_pin, LOW);
 delayMicroseconds(1);   
 delay(250);
 SPI.transfer(0x12);          

 int32_t regData;
    regData |= SPI.transfer(0xff); 
    regData <<= 8; 
    regData |= SPI.transfer(0xff); 
    regData <<= 8;
    regData |= SPI.transfer(0xff); 
    Serial.print(regData, HEX);
    Serial.print(" <--> ");
    Serial.println(regData, DEC); 
 }

void ADsetup()
{
  digitalWrite(cs_pin, LOW);       
  delayMicroseconds(1);       
  SPI.transfer(0x06);          
  delay(ADResetDelay);         
  SPI.transfer(0x16);          
  delay(210);                  
  
  SPI.transfer(0x42);           
  SPI.transfer(0x01);           
  SPI.transfer(0x33);           
  SPI.transfer(0x00);           
  delayMicroseconds(10);       
  digitalWrite(cs_pin, HIGH);       
  }


void ADreset()  
{
 digitalWrite( res_pin, LOW);
 delay(ADResetPulse);
 digitalWrite( res_pin , HIGH);
 delay(ADResetDelay); 
 }

 
void SPIinitialize()
{
 pinMode(cs_pin, OUTPUT); 
 pinMode(drdy_pin, INPUT); 
 pinMode(res_pin, OUTPUT); 
 pinMode(strt_pin, OUTPUT); 
 digitalWrite(cs_pin, HIGH);  
 digitalWrite(res_pin , HIGH); 
 digitalWrite(strt_pin , HIGH); 
 
 SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE1)); 
 delay(200); 
 SPI.begin();
 
}

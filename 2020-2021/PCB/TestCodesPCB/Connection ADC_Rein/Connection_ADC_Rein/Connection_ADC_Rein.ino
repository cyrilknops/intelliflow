#include <SPI.h>

#define cs_pin 5
#define drdy_pin 17
#define res_pin 21
#define strt_pin 22

const int ADResetPulse = 200;    
const int ADResetDelay = 1;     

bool drdy = 0;
bool prevState = 0;

void setup() 
{
 Serial.begin(115200);
 delay (16);

 pinMode(cs_pin, OUTPUT); 
 pinMode(drdy_pin, INPUT); 
 attachInterrupt(digitalPinToInterrupt(drdy_pin), ADread, FALLING);
 pinMode(res_pin, OUTPUT); 
 pinMode(strt_pin, OUTPUT);
 
 digitalWrite(strt_pin, HIGH);  //starting adc
 
 SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE1)); 
 delay(200); 
 SPI.begin();

 
 ADreset();
 
 Serial.print("setup ADC...\n");
 ADsetup();
 Serial.print("setup ADC Done\n");
}

void loop() 
{ 
  //delayMicroseconds(1000000); 
  //Serial.println(digitalRead(drdy_pin));
   /*if (fallingEdge() == 1)
       {
          Serial.print("falling edge");
          ADread();
          delay(1000);
       }*/
}
 
void ADread()
{
  Serial.print("reading...\n");
  digitalWrite(cs_pin, LOW);
  delayMicroseconds(1);   
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

  SPI.transfer(0x40);
  SPI.transfer(0x03);
  SPI.transfer(0x01);
  SPI.transfer(0x00);
  SPI.transfer(0x03);
  SPI.transfer(0x42);
            
  SPI.transfer(0x04);           
         
  delayMicroseconds(10);       
  digitalWrite(cs_pin, HIGH);       
  }


void ADreset()  
{
 digitalWrite( res_pin, LOW);
 Serial.println("RESET -> LOW");
 delay(ADResetPulse);
 digitalWrite( res_pin , HIGH);
 Serial.println("RESET -> HIGH");
 delay(ADResetDelay); 
 }

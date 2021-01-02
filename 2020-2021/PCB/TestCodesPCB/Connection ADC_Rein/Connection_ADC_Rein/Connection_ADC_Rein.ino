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
 
 Serial.print("setup ADC...\n");
 ADsetup();
 Serial.print("setup ADC Done\n");
}

void loop() 
{ 
  
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
  ADreset();
  delayMicroseconds(600);        
  SPI.transfer(0x16);           //Stop read data continuous mode
  delay(210);                  

  SPI.transfer(0x40);           //write register beginning at register 0 (mux0)
  SPI.transfer(0x02);           //send how buch bites there will be send - 1
  SPI.transfer(0x01);           //set mux0
  SPI.transfer(0x00);           //set vbias
  SPI.transfer(0x03);           //set mux1
  SPI.transfer(0x42);           //
            
  SPI.transfer(0x04);           
         
  delayMicroseconds(10);       
  digitalWrite(cs_pin, HIGH);       
  }


void ADreset()  
{
 SPI.transfer(0x06);
 Serial.println("RESET");
 delay(ADResetPulse);
 digitalWrite( res_pin , HIGH);
 Serial.println("RESET -> HIGH");
 delay(ADResetDelay); 
 }

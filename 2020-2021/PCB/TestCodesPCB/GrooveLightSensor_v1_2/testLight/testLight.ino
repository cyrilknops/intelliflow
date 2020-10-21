/* Grove - Light Sensor demo v1.0
* 
* Signal wire to A0.
* By: http://www.seeedstudio.com
*/
#include <math.h>

#define LIGHT_SENSOR1 A3
#define LIGHT_SENSOR2 A6
#define LIGHT_SENSOR3 A7
#define LIGHT_SENSOR4 A4

const int ledPin=12;                 //Connect the LED Grove module to Pin12, Digital 12
const int thresholdvalue=10;         //The treshold for which the LED should turn on. Setting it lower will make it go on at more light, higher for more darkness

float Rsensor1; //Resistance of sensor in K
float Rsensor2; //Resistance of sensor in K
float Rsensor3; //Resistance of sensor in K
float Rsensor4; //Resistance of sensor in K

void setup() 
{
    Serial.begin(9600);                //Start the Serial connection
}
void loop() 
{
    int sensorValue1 = analogRead(LIGHT_SENSOR1);     
    int sensorValue2 = analogRead(LIGHT_SENSOR2);
    int sensorValue3 = analogRead(LIGHT_SENSOR3);
    int sensorValue4 = analogRead(LIGHT_SENSOR4);

  //  Rsensor1 = (float)(1023-sensorValue1)*10/sensorValue1;
  //  Rsensor2 = (float)(1023-sensorValue2)*10/sensorValue2;
  //  Rsensor3 = (float)(1023-sensorValue3)*10/sensorValue3;
  //  Rsensor4 = (float)(1023-sensorValue4)*10/sensorValue4;
    
    Serial.println("the analog read data is ");
    
    Serial.println(sensorValue1);
    Serial.println(sensorValue2);
    Serial.println(sensorValue3);
    Serial.println(sensorValue4);
    
    Serial.println("the sensor resistance is ");//show the ligth intensity on the serial monitor;
    
   /* Serial.println(Rsensor1,DEC);
    Serial.println(Rsensor2,DEC);
    Serial.println(Rsensor3,DEC);
    Serial.println(Rsensor4,DEC);*/
    
    delay(2000);
    
}

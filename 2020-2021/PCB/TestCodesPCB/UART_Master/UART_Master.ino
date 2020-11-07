const char *sending = "Hello from ESP32";
String reading;
  
void setup()
{
  Serial.begin(19200);
}
void loop()
{
  Serial.println(sending);              // sends one byte  
 
    while(Serial.available()) 
   {
   reading = Serial.readString();// read the incoming data as string  
   //Serial.println(reading) string is recieved but it will send it back to the psoc4
   }
   
  
  delay(1000);
}

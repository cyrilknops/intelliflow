void setup() {
  Serial.begin(115200);
}

void loop() {
  int reading = analogRead(25);
  float Temp   = (reading - 509)/6.45 ;
  Serial.print("Temp: ");
  Serial.println(Temp);
  delay(1000);
}

#define LED1 34
#define LED2 35
#define LED3 32
#define LED4 33


void setup() 
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED3, OUTPUT);
  
}
void loop() 
{
  digitalWrite(LED1, HIGH);   
  digitalWrite(LED2, HIGH);     
  digitalWrite(LED3, HIGH); 
  digitalWrite(LED4, HIGH);  
  delay(1000); 
  digitalWrite(LED1, LOW);   
  digitalWrite(LED2, LOW);     
  digitalWrite(LED3, LOW); 
  digitalWrite(LED4, LOW);   
  delay(1000);
   
    
}

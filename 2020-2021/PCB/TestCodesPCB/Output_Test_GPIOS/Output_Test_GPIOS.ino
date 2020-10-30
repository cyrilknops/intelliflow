#define GPIO36 36
#define GPIO39 39
#define GPIO34 34
#define GPIO35 35
#define GPIO32 32
#define GPIO5  5
#define GPIO15 15
#define GPIO2  2
#define GPIO7  7
#define GPIO8  8


void setup() 
{
  pinMode(GPIO36, OUTPUT);
  pinMode(GPIO39, OUTPUT);
  pinMode(GPIO34, OUTPUT);
  pinMode(GPIO35, OUTPUT);
  pinMode(GPIO32, OUTPUT);
  pinMode(GPIO5 , OUTPUT);
  pinMode(GPIO15, OUTPUT);
  pinMode(GPIO2,  OUTPUT);
  pinMode(GPIO7,  OUTPUT);
  pinMode(GPIO8,  OUTPUT);
  
}
void loop() 
{
  digitalWrite(GPIO36, HIGH);   
  digitalWrite(GPIO39, HIGH);     
  digitalWrite(GPIO34, HIGH); 
  digitalWrite(GPIO35, HIGH);  
  digitalWrite(GPIO32, HIGH);  
  digitalWrite(GPIO5,  HIGH);  
  digitalWrite(GPIO15, HIGH); 
  digitalWrite(GPIO2,  HIGH);  
  digitalWrite(GPIO7,  HIGH);   
  digitalWrite(GPIO8,  HIGH); 

  delay(1000);

  digitalWrite(GPIO36, LOW);   
  digitalWrite(GPIO39, LOW);     
  digitalWrite(GPIO34, LOW); 
  digitalWrite(GPIO35, LOW);  
  digitalWrite(GPIO32, LOW);  
  digitalWrite(GPIO5,  LOW);  
  digitalWrite(GPIO15, LOW); 
  digitalWrite(GPIO2,  LOW);  
  digitalWrite(GPIO7,  LOW);   
  digitalWrite(GPIO8,  LOW); 

  delay(1000);

  
}

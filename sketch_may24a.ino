int ledPin = 13;   
int buzzerPin = 8;  

void setup() {
  pinMode(ledPin, OUTPUT);     
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);   
  digitalWrite(buzzerPin, HIGH); 
  delay(500);                 

  digitalWrite(ledPin, LOW);    
  digitalWrite(buzzerPin, LOW); 
  delay(500);                  
}

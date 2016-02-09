int inPin   = 2; 
int outPin  = 3; 
int potPin  = A0; 

int state = LOW;     
int reading;          
int previous = LOW;   

long time = 0;        
long debounce = 1000;  

int potVal = 0;  
int prevPotVal = 0;

void setup() {
  Serial.begin(9600);
  delay(500);
  
  pinMode(inPin, INPUT);    
  pinMode(outPin, OUTPUT);  
  Serial.println("Program started ...");
}

void loop() {
  reading = digitalRead(inPin);  

  if (reading && (millis() - time > debounce)) {
    if (previous == LOW) {
      Serial.println("[PHYSICAL] LED turned on"); state = HIGH;
    } else {
      Serial.println("[PHYSICAL] LED turned off"); state = LOW;
    }

    time = millis();
    digitalWrite(outPin, state);
    previous = state;
    prevPotVal = potVal - 10;
  }
  potVal = analogRead(potPin);
  if((state == HIGH) && (abs(potVal-prevPotVal)>4)){
    analogWrite(outPin, potVal/4);  
    Serial.print("[PHYSICAL] LED intensity ");
    Serial.println(potVal/4);
    prevPotVal = potVal;
  }
}



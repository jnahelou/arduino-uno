/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int ledB = 2;
int ledG = 4;
int ledR = 6;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledB, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(ledB, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(ledB, HIGH);
  delay(400);        
  digitalWrite(ledB, LOW);
  digitalWrite(ledG, HIGH);
  delay(400);
  digitalWrite(ledG, LOW);
  digitalWrite(ledR, HIGH);
  delay(400);
  digitalWrite(ledR, LOW);
  digitalWrite(ledB, HIGH);  
}


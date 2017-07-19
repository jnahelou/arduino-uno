/*
Arduino     Touch Sensor
  5V         VCC
  GND        GND
  D3         SIG
*/

int TouchSensor = 13; //connected to Digital pin D3
int led = 6;

boolean force = false;

void setup(){
  Serial.begin(9600); // Communication speed
  pinMode(led, OUTPUT);
  pinMode(TouchSensor, INPUT);
}

void loop(){
  if(digitalRead(TouchSensor)==HIGH)
  {
    digitalWrite(led, HIGH);   // if Touch sensor is HIGH, then turn on
    Serial.println("Led ON");
  }
  else
  {
    digitalWrite(led, LOW);    // if Touch sensor is LOW, then turn off the led
    Serial.println("Led OFF");
  }
  delay(100); // Slow down the output for easier reading
}

/*
Arduino     Touch Sensor
 5V         VCC
 GND        GND
 D3         SIG
 */

#include <Wire.h>

#define SLAVE_ADDRESS 0x13
int dataReceived = 0;

int TouchSensor = 13;
int led = 6;

boolean state = false;

void setup(){
  Serial.begin(9600); // Communication speed
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  pinMode(led, OUTPUT);
  pinMode(TouchSensor, INPUT);
}

void loop(){



  if(digitalRead(TouchSensor)==HIGH)
  {
    Serial.print("TOUCHED !");
    state = !digitalRead(led);
  }
  
  digitalWrite(led, state);

  delay(500); // Slow down the output for easier reading
}


void receiveData(int byteCount){
  while(Wire.available()) {
    dataReceived = Wire.read();
  }
  switch (dataReceived) {
  case 0:
    //Turn on Ligh
    state = LOW;
    Serial.println("TurnOff");
    break;
  case 1:
    //Turn off Ligh
    state = HIGH;
    Serial.println("TurnOn");
    break;
  default:
    Serial.print("State : ");
    Serial.println(digitalRead(led));
    break;
  }
}
void sendData(){
  Wire.write(digitalRead(led));
}


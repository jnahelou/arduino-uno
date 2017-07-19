#include <Wire.h>

#define SLAVE_ADDRESS 0x13

int Mode, Pin, Value;
const int MAX = 8;
const int AVG = 1;
/* PIN DECLARATION */
int Pin_AmbientLight_LDR = A1;
int Pin_Temperature = A0;

volatile short Value_AmbientLight_LDR, Value_Temperature;

int TouchSensor = 13;
int ledR = 6;
int ledG = 4;
int ledB = 2;

void setup(){
  Serial.begin(9600); // Communication speed

  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  pinMode(Pin_AmbientLight_LDR, INPUT);
  pinMode(Pin_Temperature, INPUT);
  pinMode(TouchSensor, INPUT);

  for(int i = 0; i < MAX; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(Pin, LOW);

  }


}

void loop(){
  if(digitalRead(TouchSensor)==HIGH)
  {
    Serial.print("TOUCHED !");
    digitalWrite(ledR, !digitalRead(ledR));
  }


  delay(1000); // Slow down the output for easier reading
}


void receiveData(int byteCount){
  int code[5];
  int i = 0;
  while(Wire.available()){
    if(i < 4){
      code[i] = Wire.read();
      i++;
    }
  }
  int cmd = code[0];
  Serial.print("- cmd ");
  Serial.print(cmd);
  if (cmd == 0) {
    Mode = code[1];
    Serial.print("- Mode ");
    Serial.print(Mode);

    // Signal specified pin if Mode 2 is received
    if (Mode == 2)
    {

      Pin = code[2];
      Value = code[3];
      Serial.print(" - Pin ");
      Serial.print(Pin);
      Serial.print(" - Value ");
      Serial.print(Value);

      digitalWrite(Pin, Value);
    }
  }
  Serial.println("");

}



void sendData()
{
  byte tab[MAX];
  int availableBytes = Wire.available();
  for(int i = 0; i < MAX; i++)
    tab[i] = 3;

  volatile int val = 0;
  volatile float incel;
  switch (Mode)
  {

  case 0: // Mode: Read Sensor 

    //Get Temperature AVG
    for(int i = 0; i < AVG; i++) {
      val = val + analogRead(Pin_Temperature);
    }
    val= val/AVG;
    incel = (val/1024.0)*5000/10;
    Value_Temperature = (short) incel;
    Serial.print("- Temperature : ");
    Serial.print(incel);

    //Get Light AVG
    val = 0;
    for(int i = 0; i < AVG; i++) {
      val = val + analogRead(Pin_AmbientLight_LDR);
    }
    Value_AmbientLight_LDR= val/AVG;
    Value_AmbientLight_LDR = map(Value_AmbientLight_LDR, 0, 1023, 0, 255);
    Serial.print(" - Light : ");
    Serial.println(Value_AmbientLight_LDR);

    //Return result
    tab[0] = Value_AmbientLight_LDR;
    tab[1] = (byte)((Value_Temperature < 0) ? 0 : 1);  
    // -ve Temperature can't be sent in byte. Convert it into +ve equivalent
    tab[2] = (byte)((Value_Temperature < 0) ? (Value_Temperature*(-1)) : Value_Temperature);
    break;
  case 1: // Mode: Read Devices State
    for(int i = 0; i < MAX; i++)
      tab[i] = (digitalRead(i) == HIGH) ? 1 : 0;
    break;
  case 2: // Mode: Set Device State
    Serial.print("State Pin ");
    Serial.print(Pin);
    Serial.println(digitalRead(Pin));
    tab[Pin] = (digitalRead(Pin) == HIGH) ? 1 : 0;
    break;
  default:
    break;
  }

  // Wire back tab
  byte *ptr = tab;
  Wire.write(ptr, 14);
}






























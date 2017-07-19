#include <Wire.h>

#define I2C_ADDRESS 0x13

void setup() {
 Serial.begin(9600);
 Serial.print("initialize..");
 Wire.begin(I2C_ADDRESS);
 Wire.onReceive(dataReceive);
 Wire.onRequest(dataRequest);
 Serial.println(".");
}

void loop() {
 delay(10);
}

void dataRequest(){
 byte b[32];
 int availableBytes = Wire.available();
 Serial.print("dataRequest() called with command: ");
 Serial.println(availableBytes);
 for(int i = 0; i < 32; i++)
   b[i] =(byte) i;
 byte *ptr = b;
 Wire.write(ptr, 32);
}

void dataReceive(int byteCount) {
 byte receiveArray[32];
 byte *arrayPtr = receiveArray;
 while(Wire.available())
 {
   byte b = Wire.read();
   *arrayPtr = b;
   arrayPtr++;
 }
 
 Serial.println("Data received");
}


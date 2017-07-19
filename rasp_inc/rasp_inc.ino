#include <Wire.h>

#define SLAVE_ADDRESS 0x13
int dataReceived = 0;
const int MAX = 14;



void setup() {
    Serial.begin(9600);
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
    Serial.println("Initialized");

}

void loop() {
    delay(10);
}

void receiveData(int byteCount){

 Serial.println("Data received");
}

void sendData(){
    byte tab[MAX];
    int availableBytes = Wire.available();
    for(int i = 0; i < MAX; i++)
        tab[i] = dataReceived + i*4;
        
    Serial.print("Donnee envoyee");
    byte *ptr = tab;
    Wire.write(ptr, MAX);
}

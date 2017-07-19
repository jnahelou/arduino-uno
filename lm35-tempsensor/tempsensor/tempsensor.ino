int val;
float oldval;
int tempPin = 0;
int ledR = 6;


void setup()
{
  Serial.begin(9600);
  oldval=0;
  pinMode(ledR, OUTPUT);

}
void loop()
{
int val = analogRead(tempPin);
float mv = ( val/1024.0)*5000;
float cel = mv/10;

Serial.print("TEMPRATURE = ");
Serial.print(cel);
Serial.print("*C Old temp =");
Serial.print(oldval);
Serial.print("*C");
Serial.println();
if (oldval-1 < cel && oldval+1 > cel) {
   digitalWrite(ledR, LOW);
} else { 
   //Turn On Light if temp up 2°C
   digitalWrite(ledR, HIGH); 
}

oldval = cel;
delay(1000);

}



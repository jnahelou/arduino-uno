int photocellPin = 1;     // La photo-résistance et la résistance 10K connectées sur la pin/broche analogique A0
int photocellReading;     // Contient la lecture analogique sur le pont diviseur Photo-résistance + R 10 KOhms
int ledB = 2;
int ledG = 4;
int ledR = 6;
boolean go = false;
int forceStop=0;


void setup(void) {
  // Démarrons la connexion série pour envoyer des message de debugging.
  Serial.begin(9600);  
  pinMode(ledB, OUTPUT);
  pinMode(ledG, OUTPUT); 
  go = false;
  forceStop = 0;
}
 
void loop(void) {
  digitalWrite(ledR, LOW);  
  digitalWrite(ledG, LOW);  
  digitalWrite(ledB, LOW);  
  photocellReading = analogRead(photocellPin);  
 
  Serial.print("Lecture Analogique = ");
  Serial.print(photocellReading);     // La valeur analogique brute
 
  // Utilisons quelques seuils, détermination qualitative
  if (photocellReading < 10) {
    Serial.println(" - Noir");   // Dark en anglais
    digitalWrite(ledB, HIGH);
    go = true;
    forceStop++;
  } else if (photocellReading < 200) {
    Serial.println(" - Sombre"); // Dim en anglais (aussi traduit par Obscur)
    go = true;
    forceStop++;
  } else if (photocellReading < 500) {
    Serial.println(" - Léger");  // Light en anglais
    go = false;
    forceStop = 0;
  } else if (photocellReading < 800) {
    Serial.println(" - Lumineux"); // Bright en anglais
    go = false;
    forceStop = 0;

  } else {
    Serial.println(" - Très lumineux");  // Very bright en anglais
    go = false;
    forceStop = 0;

  }
  
  if (go & forceStop <= 2) {
    for (int i=0; i <= 5; i++){
      digitalWrite(ledB, LOW);    // turn the LED off by making the voltage LOW
      digitalWrite(ledB, HIGH);
      delay(666);        
      digitalWrite(ledB, LOW);
      digitalWrite(ledG, HIGH);
      delay(666);
      digitalWrite(ledG, LOW);
      digitalWrite(ledR, HIGH);
      delay(666);
      digitalWrite(ledR, LOW);
      digitalWrite(ledB, HIGH);
    } 
  } else {
    digitalWrite(ledG, LOW);
    digitalWrite(ledB, LOW);
    digitalWrite(ledR, LOW);
    delay(10000);
  }
}


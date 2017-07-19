int photocellPin = 1;     // La photo-résistance et la résistance 10K connectées sur la pin/broche analogique A0
int photocellReading;     // Contient la lecture analogique sur le pont diviseur Photo-résistance + R 10 KOhms
int ledB = 2;
int ledG = 4;
int ledR = 6;

void setup(void) {
  // Démarrons la connexion série pour envoyer des message de debugging.
  Serial.begin(9600);  
  pinMode(ledB, OUTPUT);
  pinMode(ledG, OUTPUT); 
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
  } else if (photocellReading < 200) {
    Serial.println(" - Sombre"); // Dim en anglais (aussi traduit par Obscur)
    digitalWrite(ledG, HIGH);
  } else if (photocellReading < 500) {
    Serial.println(" - Léger");  // Light en anglais
    digitalWrite(ledR, HIGH);
  } else if (photocellReading < 800) {
    Serial.println(" - Lumineux"); // Bright en anglais
  } else {
    Serial.println(" - Très lumineux");  // Very bright en anglais
  }
  delay(1000);
}


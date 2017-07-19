const int led_rouge = 2;
 
//fonction d'initialisation de la carte
void setup()
{
    //initialisation de la broche 2 comme étant une sortie
    pinMode(led_rouge, OUTPUT);
}
 
//fonction principale, elle se répète (s’exécute) à l'infini
void loop()
{
    // écriture en sortie (broche 2) d'un état BAS
    digitalWrite(led_rouge, LOW);
}

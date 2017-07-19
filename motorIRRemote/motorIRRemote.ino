#include "Stepper.h"
#include "IRremote.h"

/*----- Variables, Pins -----*/
#define STEPS  32   // Number of steps per revolution of Internal shaft
int  Steps2Take;  // 2048 = 1 Revolution
int receiver = 12; // Signal Pin of IR receiver to Arduino Digital Pin 6

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4

Stepper small_stepper(STEPS, 8, 10, 9, 11);
IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'
int keepRunning = 0;

void setup()
{ 
  Serial.begin(9600);
  Serial.println("IR Receiver Raw Data + Button Decode Test");
  irrecv.enableIRIn(); // Start the receiver

}

void loop()
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    Serial.print("Recieved : ");
    Serial.println(results.value);
    switch(results.value)
    {
    case 0xFFE21D: // UP button pressed
      Steps2Take  =  128;  // Rotate CW
      small_stepper.step(Steps2Take);
      keepRunning = 1;
      Serial.println("Ask to Up");
      break;
    case 0xFFA25D: // DOWN button pressed
      Serial.println("Ask to Down");

      Steps2Take  =  -128;  // Rotate CCW
      keepRunning = 1;
      break;
    case 0xFF629D:
      Serial.println("Ask to stop");
      keepRunning = 0;
      break;
    }

    irrecv.resume(); 

  }  

  if (keepRunning == 1) {
    Serial.println("Continue");

    small_stepper.setSpeed(700);
    small_stepper.step(Steps2Take);
  }

}/* --end main loop -- */







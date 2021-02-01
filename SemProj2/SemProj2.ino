/* semproj2.ino */

//
// <JUDY PARK, JULIANNE PABONA, SHIRLEY LI>
// SEMESTER PROJECT
// U. Of Illinois, Chicago
// CS 362: Fall 2020
//

/* Description: Code that uses two servos attached to a catapult like device
 *  that throws a ball for a dog to fetch. This will also use serial communication
 *  so that two arduinos can communicate to each other. For this code, we will send
 *  information through Serial to the other Arduino once the button on the Arduino is pushed to
 *  reset the servos and turn the red LED on. If the button connected to this Arduino is pushed, 
 *  it will make the buzzer go off. The volume of the buzzer could also be controlled via the potentiometer.
 */
 
#include <LiquidCrystal.h>

/* VARIABLES TO RUN PROGRAM */
// Variable to hold the pin numbers for buttons and leds
const int buttonPin = 7;
const int ledPin = 13;
const int buzzerPin = 6;
const int potPin = A2;

// Variables to hold the button states to notify if buttons have been pressed
int curButtonState;
int prevButtonState;

//Variable to hold potentiometer value
int potVal;

// Variables to hold the led state
int ledState = 0;

/* SETUP THE INPUTS AND OUTPUTS*/
void setup() {
  // Set up the Serial
  Serial.begin(9600);
  
  // Set the button as input and led as output
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);

  // Update the button state to read in if it has been pushed or not
  curButtonState = digitalRead(buttonPin);
}

void loop() {
  // Update the previous button state
  prevButtonState = curButtonState;

  // Read in the new state of the button and update curButtonState
  curButtonState = digitalRead(buttonPin);

  // Check if the serial got any input--if button was pressed it should receive a 1
  if(Serial.read() == 1) {
    // Update the led state to the opposite of what it was before
    ledState = !ledState;

    // Reflect it onto the led by writing to it
    digitalWrite(ledPin, ledState);

    //write 2 to the serial to indicate a reset of servos
    Serial.write(2);
  }

  // Check if the button has been pressed
  if (curButtonState == HIGH && prevButtonState == LOW) {
    
    // Write in a 1 to the serial to communicate
    Serial.write(1);

    //set potVal to the value at the potentiometer
    potVal = analogRead(potPin);
    
    // map the values stored in potval to store into a variable holding what the volume buzzer should be (0 to 6)
    byte volume = map(potVal, 0, 1024, 0, 6);

    // change volume of buzzer
    analogWrite(buzzerPin, volume);
    delay(3000);

    //stop the buzzer from making sound
    analogWrite(buzzerPin, 0);
  }

  
}

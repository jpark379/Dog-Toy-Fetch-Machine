/* semproj.ino */

//
// <JUDY PARK, JULIANNE PABONA, SHIRLEY LI>
// SEMESTER PROJECT
// U. Of Illinois, Chicago
// CS 362: Fall 2020
//

/* Description: Code that uses two servos attached to a catapult like device
 *  that throws a ball for a dog to fetch. This will also use serial communication
 *  so that two arduinos can communicate to each other. For this code, we will control the
 *  servos--if the button on this arduino is pushed, it will reset the servos and clear the lcd screen. 
 *  If the button on the other arduino is pushed, we will read it in from this program and move the servo to throw.
 *  Once the button is pushed to throw, "FETCH!" will appear on the lcd and a 1 will be
 *  written to the serial monitor for the other arduino to read and light up its green LED
 *  and sound the buzzer.
 */

#include <LiquidCrystal.h>
#include <Servo.h>

// CREATE SERVO OBBJECTS
Servo servo;
Servo servo2;

// VARIABLES TO HOLD PINS FOR BUTTONS AND LED
const int buttonPin = 7;
const int ledPin = 13;

// INITIALIZE THE LCD WITH PINS
LiquidCrystal lcd (12, 11, 5,4,3,2);

// VARIABLES TO HOLD THE BUTTON STATES TO NOTIFY IF BUTTONS HAVE BEEN PRESSED
int curButtonState;
int prevButtonState;

// VARIABLES TO HOLD LED STATE
int ledState = 0;

// VARIABLES TO KEEP TRACK OF SERVO POSITION
int servoPos = 0;

void setup() {
  // SET UP SERIAL
  Serial.begin(9600);

  // INITIALIZE THE SIZE OF LCD TO START
  lcd.begin(16, 2);
  
  // ATTACH THE SERVOS BASED ON THE PIN NUMBERS
  servo.attach(10);
  servo2.attach(9);
  
  // SET THE BUTTON AS INPUT AND THE LED AS OUTPUT
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // UPDATE THE BUTTON STATE TO READ IN IF IT HAS BEEN PUSHED OR NOT
  curButtonState = digitalRead(buttonPin);
}

void loop() {
  
  // UPDATE THE PREVIOUS BUTTON STATE
  prevButtonState = curButtonState;

  // READ IN THE NEW STATE OF THE BUTTON AND UPDATE CURBUTTONSTATE
  curButtonState = digitalRead(buttonPin);

  // CHECK IF THE SERIAL GOT ANY INPUT--IF BUTTON WAS PRESSED IT SHOULD RECEIVE A 1
  if(Serial.read() == 1) {

    // UPDATE THE LED STATE TO THE OPPOSITE OF WHAT IT WAS BEFORE
    ledState = !ledState;

    // REFLECT IT ONTO THE LED BY WRITING TO IT
    digitalWrite(ledPin, ledState);

    // SET THE CURSOR TO 0TH ROW AND 0TH COLUMN
    lcd.setCursor(0,0);

    // WRITE "FETCH" ONTO THE LCD
    lcd.print("FETCH!");

    // MOVE THE SERVOS
    servo.write(135);
    servo2.write(135);

  }

  // CHECK IF THE BUTTON HAS BEEN PRESSED
  if (curButtonState == HIGH && prevButtonState == LOW) {
    
    // WRITE IN A 1 TO THE SERIAL TO COMMUNICATE
    Serial.write(1);

    // CLEAR THE LCD
    lcd.clear();
    
    // RESET THE SERVOS
    servo.write(30);
    servo2.write(30);
  }
}

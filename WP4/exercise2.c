// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 4
// Exercise 2
// Submission code:

// Libraries
#include <Servo.h>    // includes the Servo library which will be used to control the micro servo motor component

// Macros
#define HALF_MINUTE 30          // used for setting the direction and angle of the shaft
#define ONE_MINUTE 60           // used for counting up to one minute
#define HALF_MINUTE_MARK 180    // marks the degrees the servo shaft will be turned at the half minute mark
#define MINUTE_MARK 0           // marks the degrees the servo shaft will be turned at the whole minute mark
#define PIN 3                   // the Arduino board pin connected to the micro servo motor
#define SPEED 9600              // data rate in bits per second of serial data transmission
#define MIN_PULSE_WIDTH 500     // the pulse width, in microseconds, corresponding to the angle on the servo at the whole minute mark (0 degrees)
#define MAX_PULSE_WIDTH 2500    // the pulse width, in microseconds, corresponding to the angle on the servo at the half minute mark (180 degrees)
#define ONE_SECOND 1000         // one second in milliseconds

// Function declarations
void printSeconds();            // declares the printSeconds() function

// Global variables
int pos = 0;                    // variable for storing current degree of the servo while running the program
int counter = 0;                // variable for storing number of seconds counted by the timer
Servo servo_9;                  // declares the motor variable from the Servo.h library

void setup()
{
  Serial.begin(SPEED);                                      // establishes serial communication
  servo_9.attach(PIN, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);    // attaches the servo variable to pin 3 on the Arduino board
}

void loop()
{
  servo_9.write(pos);                                                              // sets the angle of the servo
  printSeconds();                                                                  // prints the seconds of the timer
  if (counter == ONE_MINUTE)                                                       // if the counter has counted one full minute
  {
    counter = 0;                                                                   // reset counter to zero
  }
  if (counter <= HALF_MINUTE)                                                      // if the counter is between 0 and 30
  {
    pos = map(counter, 0, HALF_MINUTE, MINUTE_MARK, HALF_MINUTE_MARK);             //maps the angle of the shaft for the first half minute
  }
  else
  {
    pos = map(counter, HALF_MINUTE, ONE_MINUTE, HALF_MINUTE_MARK, MINUTE_MARK);    // maps the angle of the shaft for the second half minute
  }
  Serial.println(pos);                                                             // prints shaft angle to console
}

void printSeconds()           // this function prints the current second 
{
  delay(ONE_SECOND);          // waits one full second
  counter++;                  // increments counter variable
  Serial.println(counter);    // prints counter 
}

// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 4
// Exercise 2
// Submission code: 648664

// Libraries
#include <Servo.h>    // includes the Servo library which will be used to control the micro servo motor component

// Macros
#define ONE_MINUTE 60           // used for counting up to one minute
#define DOWN 180                // marks the degrees the servo shaft will be turned at the end of the minute
#define UP 0                    // marks the degrees the servo shaft will be turned at the start of the minute
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
  
  pos = map(counter, 0, ONE_MINUTE, UP, DOWN);                                     //maps the angle of the shaft
  if (counter == ONE_MINUTE)                                                       // if the counter has counted one full minute
  {
    counter = 0;                                                                   // reset counter to zero
  }
}

void printSeconds()           // this function prints the current second 
{
  delay(ONE_SECOND);          // waits one full second
  counter++;                  // increments counter variable
  Serial.println(counter);    // prints counter 
}

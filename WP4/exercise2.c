// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 4
// Exercise 2
// Submission code:

// includes the Servo library which will be used to control the micro servo motor component
#include <Servo.h>

//MACROS
//TODO: make macros for 30 seconds
#define HALF_MINUTE_MARK 180       // marks the degrees the servo shaft will be turned at the half minute mark
#define MINUTE_MARK 0       // marks the degrees the servo shaft will be turned at the whole minute mark
#define PIN 3       // the Arduino board pin connected to the micro servo motor
#define SPEED 9600       // data rate in bits per second of serial data transmission
#define MIN_PULSE_WIDTH 500       // the pulse width, in microseconds, corresponding to the angle on the servo at the 
                                  // whole minute mark (0 degrees)
#define MAX_PULSE_WIDTH 2500       // the pulse width, in microseconds, corresponding to the angle on the servo at the 
                                   // half minute mark (180 degrees)
#define ONE_SECOND 1000       // one second in milliseconds

void printSeconds();       // declares the printSeconds() function

int pos = 0;       // variable for storing current degree of the servo while running the program
int counter = 0;       // variable for storing number of seconds counted by the timer
Servo servo_9;       // declares the motor variable from the Servo.h library

void setup()
{
  Serial.begin(SPEED);       // establishes serial communication
  servo_9.attach(PIN, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);    // attaches the servo variable to pin 3 on the Arduino board
}

void loop()
{
  servo_9.write(pos);
  printSeconds();
  // TODO: use macros instead of numbers here
  if (counter == 60)
  {
    counter = 0;
  }
  // TODO: use macros instead of numbers here
  if (counter <= 30)
  {
    pos = map(counter, 0, 30, 0, 180);
  }
  else 
  {
    pos = map(counter, 30, 60, 180, 0);
  }
  Serial.println(pos);
}

       //
void printSeconds()
{
  delay(ONE_SECOND);      //
  counter++;       //
  Serial.println(counter);       //
}

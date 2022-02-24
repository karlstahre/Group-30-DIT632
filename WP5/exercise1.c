// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 5
// Exercise 1
// Submission code: 725062

// The following code has been taken from the submission of WP3 - Exercise 1 - Group 30 (2022)

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPin12 =  12; // the number of the button-connected LED pin
const int ledPin13 = 13;  // the number of the blinking LED pin

// constants won't change:
const long interval = 1000; // interval at which to blink (milliseconds)

// variables will change:
int buttonState = 0;    // variable for reading the pushbutton status
int ledState = LOW;     // used to set ledPin13

unsigned long previousMillis = 0; // will store last time ledPin13 was updated


void setup() {
  // initialize the LED pins as output
  pinMode(ledPin12, OUTPUT);
  pinMode(ledPin13, OUTPUT);
  // initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT);
}

void loop() {
  
  //LED_PIN12
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // Handles case where the button is pressed:
  if (buttonState == HIGH) 
  {
    // Turn LED on
    digitalWrite(ledPin12, HIGH);
  }
  // Handles case where button is not pressed
  else 
  {
    // Turn LED off:
    digitalWrite(ledPin12, LOW);
  }
  
  // LED_PIN13
  
  unsigned long currentMillis = millis(); // Store current time value
 
  // Handles case where more than interval time has passed since last blink
  if (currentMillis - previousMillis >= interval) 
  {
    // save the last time LED blinked
    previousMillis = currentMillis;
    // Handles case where LED is off
    if (ledState == LOW) 
    {
      // Set ledState to HIGH value
      ledState = HIGH;
    } 
    // Handles case where LED is on
    else 
    {
      // Set ledState to LOW value
      ledState = LOW;
    }
    // Set ledPin13 with the relevant ledState
    digitalWrite(ledPin13, ledState);
  }
}

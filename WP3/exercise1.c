//TODO: add header comment with our names
//TODO: make proper comments
//TODO: translate to c code

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin12 =  12;      // the number of the LED pin
const int ledPin13 = 13;

const int ledPin =  12;// the number of the LED pin

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated


void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin12, OUTPUT);
  pinMode(ledPin13, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  
  //LED_PIN12
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin12, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin12, LOW);
  }
  //TODO: connect button directly to led
  // LED_PIN13
  // here is where you'd put code that needs to be running all the time.
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
}

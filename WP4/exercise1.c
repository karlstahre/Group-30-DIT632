// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 4
// Exercise 1
// Submission code:

// constants
// initializing the LEDs to the corresponding pins
const int LED1 = 12;
const int LED2 = 11;
const int LED3 = 10;
const int LED4 = 9;
const int LED5 = 8;

const int TEMP = 3; // Initializing the temperature sensor power to pin D3 to be able to use interrupt
const int TEMP_SENSOR = 0; // Initializing the temperature sensor vout to an analog pin

const int OFFSET = 50; // Used for conversion from volt to Celsius

// Constant variables for the celsius degrees
const int TEMP_0 = 0;
const int TEMP_10 = 10;
const int TEMP_20 = 20;
const int TEMP_30 = 30;
const int TEMP_40 = 40;
const int TEMP_50 = 50;

const long interval = 3000; // Interval between the measurements of the temperature sensor

unsigned long currentMillis; // Store current time value
unsigned long previousMillis; // Store previous time value
double currentTemp; // Store current temperature

void setup()
{
  DDRB &= B00011111; // Pins from 8 to 12 are set to output
  pinMode(TEMP, INPUT); // Pin 3 in set to input
  pinMode(TEMP_SENSOR, INPUT); // Pin A0 is set to input
}

void loop()
{
  updateTempState(); // Function call to update the state of the temperature sensor
  // Function call to use interrupts, sets the digital pin 3 to interrupt
  // calls the ISR function readTemp and the mode is set to RISING so that
  // the interrupt triggers when the pin state goes from LOW to HIGH
  attachInterrupt(digitalPinToInterrupt(TEMP), readTemp, RISING);
  updateLeds(); // Function call to light the LEDs
  delay(10);
}

// This function checks if the interval has passed and changes
// the state of the temperature sensor pin 3 to HIGH or LOW
// depending if the interval time has passed or not
void updateTempState()
{ 
   currentMillis = millis(); // Sets the variable to milliseconds
   // Handles case where more than interval time has passed since last measurement
   if (currentMillis - previousMillis >= interval) 
   {
      // save the last time of measurement
      previousMillis = currentMillis;
      digitalWrite(TEMP, HIGH); // Change pin 3 state to HIGH
   }
   else 
   {
     digitalWrite(TEMP, LOW); // Change pin 3 state to LOW
   }
}

// This funtion calculates and returns the temperature in degrees celsius
double toCelsius(double rawReading)	
{
  // This formula calculates the celsius equivalent of measured voltage
  return (rawReading*500/1023) - OFFSET;                                
}

// This function reads the temperature from the temperature sensor
// via the analog pin A0
void readTemp()
{
  // Store the current temperature in celsius
  currentTemp = toCelsius(analogRead(TEMP_SENSOR));
}

// This function lights the LEDs 
// depending on the temperature range
// by turning the corresponding pin to HIGH
void updateLeds()
{
  PORTB = B00000000; // Turn all pins on port B to LOW
  // Handles case when the temperature ranges from 0 to 10
  if (currentTemp >= TEMP_0 && currentTemp <= TEMP_10)
  {
    digitalWrite(LED1, HIGH);
  }
  // Handles case when the temperature ranges from 11 to 20
  else if (currentTemp > TEMP_10 && currentTemp <= TEMP_20)
  {
    digitalWrite(LED2, HIGH);
  }
  // Handles case when the temperature ranges from 21 to 30
  else if (currentTemp > TEMP_20 && currentTemp <= TEMP_30)
  {
    digitalWrite(LED3, HIGH);
  }
  // Handles case when the temperature ranges from 31 to 40
  else if (currentTemp > TEMP_30 && currentTemp <= TEMP_40)
  {
    digitalWrite(LED4, HIGH);
  }
  // Handles case when the temperature ranges from 41 to 50
  else if (currentTemp > TEMP_40 && currentTemp <= TEMP_50)
  {
    digitalWrite(LED5, HIGH);
  }
}

// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 5
// Exercise 3
// Submission code: 725062

// The following code has been taken from the submission of WP3 - Exercise 2 part 1 - Group 30 (2022)

/* constants */
const int TEMP_SENSOR = 0;     // Analog pin for temperature sensor
const int LIGHT_SENSOR = 1;   // Analog pin for light sensor
const int RED_LED = 13;     // Digital pin for red led
const int GREEN_LED = 12;   // Digital pin for green led
const int BLUE_LED = 11;    // Digital pin for blue led
const int OFFSET = 50;      // Used for conversion from volt to Celsius
const int ERROR = 8000;     // Used for error handling
const int ALL_LOW = B00000000;    // Used to reset all pins to LOW
const double K = 7.6923;    // Used for light to percentage conversion

// variable numbers
double currentTemp = 0;     // Initialize temperature value
double currentLight = 0;    // Initialize light value

// Temperature - light intensity constants
const int LOW_TEMP = -12;   // Temperature values
const int MED_TEMP = 0;
const int HIGH_TEMP = 20;
const int MIN_LIGHT = 0;    // Light intensity values
const int LOW_LIGHT = 20;
const int HIGH_LIGHT = 60;
const int MAX_LIGHT = 100;

void setup()
{
  Serial.begin(9600);     // set up serial communication
  pinMode(TEMP_SENSOR, INPUT);    // set tempSensor as INPUT
  pinMode(LIGHT_SENSOR, INPUT);   // set lightSensor as INPUT
  pinMode(RED_LED, OUTPUT);   // set redLed as OUTPUT
  pinMode(GREEN_LED, OUTPUT);   // set greenLed as OUTPUT
  pinMode(BLUE_LED, OUTPUT);    // set blueLed as OUTPUT
}

void loop()
{
  currentTemp = toCelsius(analogRead(TEMP_SENSOR));     // takes temperature measurement
  Serial.println(currentTemp);            // tests temperature measurement
  currentLight = toLightPercentage(analogRead(LIGHT_SENSOR));   // takes light intensity measurement
  Serial.println(currentLight);           // tests light intensity measurement
  int ledToTurnOn = checkDependency(currentTemp, currentLight);   // use measurements taken to decide which light to turn on
  
  if (ledToTurnOn != ERROR)           // handles undesirable errors
  {
    PORTB = ALL_LOW;              // resets all pins
    digitalWrite(ledToTurnOn, HIGH);          // turn on colored LED
  }
  delay(1000);                // wait for 1 second
}

double toCelsius(double rawReading)         // calculates the temperature in degres Celsius
{
  return (rawReading*500/1023) - OFFSET;                                // This formula calculates the celcius equivalent of measured voltage
}

double toLightPercentage(int rawReading)        // calculates light intensity in percentage
{
  return rawReading * K;            // This formula calculates the percentage equivalent of measured light intensity
}
    
// checks the dependency between temperature and light intensity
int checkDependency(double currentTemp, double currentLight)    
{
// Handles case if temperature lower than light (BLUE)
  if (   (currentTemp < LOW_TEMP && currentLight > MIN_LIGHT)
      || (currentTemp >= LOW_TEMP && currentTemp <= MED_TEMP && currentLight > LOW_LIGHT)
      || (currentTemp > MED_TEMP && currentTemp <= HIGH_TEMP && currentLight > HIGH_LIGHT))
  {
    return BLUE_LED;
  }
  // Handles case if temperature normally dependent with light (GREEN)
  else if (   (currentTemp < LOW_TEMP && currentLight == MIN_LIGHT)
           || (currentTemp >= LOW_TEMP && currentTemp <= MED_TEMP && currentLight > MIN_LIGHT && currentLight <= LOW_LIGHT)
           || (currentTemp > MED_TEMP && currentTemp <= HIGH_TEMP && currentLight > LOW_LIGHT && currentLight <= HIGH_LIGHT)
           || (currentTemp > HIGH_TEMP && currentLight > HIGH_LIGHT))
  {
    return GREEN_LED;
  }
  // Handles case if temperature higher than light (RED)
  else if (    (currentTemp > LOW_TEMP && currentLight == MIN_LIGHT)
          || (currentTemp > MED_TEMP && currentLight > MIN_LIGHT && currentLight <= LOW_LIGHT)
          || (currentTemp > HIGH_TEMP && currentLight > LOW_LIGHT && currentLight <= HIGH_LIGHT))
  {
  return RED_LED;
  }
  // Handles any undesirable outcome
  else
  { 
    return ERROR;
  }
}

// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 3
// Exercise 2 part 2
// Submission code: 185160

// constants
const int TEMP_SENSOR = 0; 	                            // Analog pin for temperature sensor
const int OFFSET = 50;                                  // Used for conversion from volt to Celsius

// variable numbers
double currentTemp = 0;	                                // Initialize temperature value

void setup()
{
  Serial.begin(9600);                                   // set up serial communication
  pinMode(TEMP_SENSOR, INPUT);	                        // set tempSensor as INPUT
}

void loop()
{
  currentTemp = toCelsius(analogRead(TEMP_SENSOR));     // reads temperature measurement
  Serial.println(currentTemp);                          // tests measurement
  delay(500);                                           // Wait for half of a second
}

double toCelsius(double rawReading)                     // calculates temperature from voltage measurement
{
  return (rawReading*500/1023) - OFFSET;                // This formula calculates the celcius equivalent of measured voltage
}

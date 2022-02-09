//TODO: add comments and header with our names
/* constants */
const int TEMP_SENSOR = 0; 	// Analog pin for temperature sensor
const int OFFSET = 50;

// variable numbers
double currentTemp = 0;	// Initialize temperature value

void setup()
{
  Serial.begin(9600);
  pinMode(TEMP_SENSOR, INPUT);	// set tempSensor as INPUT
}

void loop()
{
  //TODO: add comments
  currentTemp = toCelsius(analogRead(TEMP_SENSOR));
  Serial.println(currentTemp);
  
  delay(500); // Wait for 1000 millisecond(s)
}

//TODO: add comments
double toCelsius(double rawReading)
{
  return (rawReading*500/1023) - OFFSET;
}

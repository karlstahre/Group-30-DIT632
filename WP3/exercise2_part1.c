//TODO: add comments and header with our names
/* constants */
const int TEMP_SENSOR = 0; 	// Analog pin for temperature sensor
const int LIGHT_SENSOR = 1;	// Analog pin for light sensor
const int RED_LED = 13;		// Digital pin for red led
const int GREEN_LED = 12;		// Digital pin for green led
const int BLUE_LED = 11;		// Digital pin for blue led
const int OFFSET = 50;
const int ERROR = 8000;
const int ALL_LOW = B00000000;

// offset used for volt to celsius conversion
const double K = 7.6923;	// Constant used for light to percentage conversion

// variable numbers
double currentTemp = 0;	// Initialize temperature value
double currentLight = 0;	// Initialize light value

//TODO: add values for temperature and light table
// Temperature dependency values
const int LOW_TEMP = -12;
const int MED_TEMP = 0;
const int HIGH_TEMP = 20;
// Light intensity dependency values
const int MIN_LIGHT = 0;
const int LOW_LIGHT = 20;
const int HIGH_LIGHT = 60;
const int MAX_LIGHT = 100;


void setup()
{
  Serial.begin(9600);
  pinMode(TEMP_SENSOR, INPUT);	// set tempSensor as INPUT
  pinMode(LIGHT_SENSOR, INPUT);	// set lightSensor as INPUT
  pinMode(RED_LED, OUTPUT);		// set redLed as OUTPUT
  pinMode(GREEN_LED, OUTPUT);	// set greenLed as OUTPUT
  pinMode(BLUE_LED, OUTPUT);		// set blueLed as OUTPUT
}

void loop()
{
  //TODO: add comments
  currentTemp = toCelsius(analogRead(TEMP_SENSOR));
  Serial.println(currentTemp);
  
  currentLight = toLightPercentage(analogRead(LIGHT_SENSOR));
  Serial.println(currentLight);
  
  int ledToTurnOn = checkDependency(currentTemp, currentLight);
  
  if (ledToTurnOn != ERROR)
  {
    PORTB = ALL_LOW;
    digitalWrite(ledToTurnOn, HIGH);
  }
  
  delay(1000); // Wait for 1000 millisecond(s)
}

//TODO: add comments
double toCelsius(double rawReading)
{
  return (rawReading*500/1023) - OFFSET;
}

//TODO: add comments
double toLightPercentage(int rawReading)
{
  return rawReading * K;
}
    
//TODO: add comments
int checkDependency(double currentTemp, double currentLight)
{
// Handles case if temperature lower than light (BLUE)
  if (	 (currentTemp < LOW_TEMP && currentLight > MIN_LIGHT)
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
  else
  { 
    return ERROR;
  }
}

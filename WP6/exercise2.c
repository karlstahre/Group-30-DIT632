// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 6
// Exercise 2
// Submission code: 771088

// Constants
// Initialize the components to their corresponding pins
const int LED1_PIN = 2;
const int LED2_PIN = 3;
const int LED3_PIN = 4;
const int LED4_PIN = 5;
const int US_SIG_PIN = 7;
const int SPEAKER_PIN = 9;

const double SOUND_SPEED = 0.034;	// Speed of sound (cm/microseconds)
const int MAX_DIST = 200;   // Maximum distance measurable by US sensor (cm)
const int MIN_DIST = 25;    // Minimum distance measurable by US sensor (cm)

// Define and initialize a range for distance in cm
const int DIST_30_CM = 30;
const int DIST_100_CM = 100;
const int DIST_150_CM = 150;

// Define and initialize a range for the tone in herz
const int HERZ_1000 = 1000;
const int HERZ_800 = 800;
const int HERZ_600 = 600;
const int HERZ_400 = 400;
const int HERZ_200 = 200;
const int HERZ_0 = 0;

// Variables
long duration;	// Used for travel time in US distance measurements
long distance;	// Used for storing distance in US distance measurements

int annoyingness; // Used in the tone function for the speaker, stores herz

void setup()
{
  Serial.begin(9600); // Initialize serial communication
  
  // Set LED pins as OUTPUT
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  // Set Speaker pin as OUTPUT
  pinMode(SPEAKER_PIN, OUTPUT);
  
   // Ultrasonic sensor is set in the readDistance() function
}

void loop()
{
  // Function calls
  readDistance();
  controlLeds();
  speaker();
  // Delay needed to not optimize the simulation on Tinkercad 
  delay(10);
}

// This function computes the distance from the objects and updates distance variable
void readDistance()
{  
  // Listen to input if some echo returns. The time until the echo returns is related to the distance of the
  // object from which the ping reflected.
  // Set US Pin to Output.
  pinMode(US_SIG_PIN, OUTPUT);
  // Write a zero to the output to clear the system. Wait 2 microseconds
  digitalWrite(US_SIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Write a one to the output to send a ping. Wait 10 microseconds
  digitalWrite(US_SIG_PIN, HIGH);
  delayMicroseconds(10);
  
  // Write a zero to the output to stop sending the ping
  digitalWrite(US_SIG_PIN, LOW);
  // Set Pin to Input
  pinMode(US_SIG_PIN, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  duration = pulseIn(US_SIG_PIN, HIGH);

  // Distance (cm) = (Time x Speed) / 2
  distance = (duration * SOUND_SPEED) / 2;
}

// This function turns on or off the LEDs depending on the distance range
void controlLeds()
{
  // When distance is less than 25
  if (distance < MIN_DIST)
  {
    // Blink all lights
    blink();
  } 
  // When distance is less than 30
  else if (distance < DIST_30_CM)
  {
    // Turn on all lights
    PORTD = B00111100;
  }
  // When distance is between 30 and 99
  else if (distance >= DIST_30_CM && distance < DIST_100_CM)
  {
    // Turn on three lights
    PORTD = B00111000;
  }
  // When distance is between 100 and 149
  else if (distance >= DIST_100_CM && distance < DIST_150_CM)
  {
    // Turn on two lights
    PORTD = B00110000;
  }
  // When distance is between 150 and 200
  else if (distance >= DIST_150_CM && distance <= MAX_DIST)
  {
    // Turn on one light
    PORTD = B00100000;
  }
  // When distance less than 25 and greater than 200
  else
  {
    // Turn off all lights
    PORTD = B00000000;
  }
}

// This function makes the four LEDs blink
void blink()
{
  PORTD = B00111100; // Turn on all LEDs
  delay(100);
  PORTD = B00000000; // Turn off all LEDs
  delay(100);
}

// This function changes the herz of the tone of the speaker depending on
// the distance range
// The tone becomes more annoying the closer the distance is
void speaker()
{ 
  // When distance is less than 25
  if (distance < MIN_DIST)
  {
    annoyingness = HERZ_1000;
  } 
  // When distance is less than 30
  else if (distance < DIST_30_CM)
  {
    annoyingness = HERZ_800;
  }
  // When distance is between 30 and 99
  else if (distance >= DIST_30_CM && distance < DIST_100_CM)
  {
    annoyingness = HERZ_600;
  }
  // When distance is between 100 and 149
  else if (distance >= DIST_100_CM && distance < DIST_150_CM)
  {
    annoyingness = HERZ_400;
  }
  // When distance is between 150 and 200
  else if (distance >= DIST_150_CM && distance <= MAX_DIST)
  {
    annoyingness = HERZ_200;
  }
  // When distance less than 25 and greater than 200
  else
  {
    annoyingness = HERZ_0; 
  }
  
  // Handles case when the speaker should be quiet
  if (annoyingness == HERZ_0)
  {
    noTone(SPEAKER_PIN); // Turn off the tone
  }
  // Handles case when the speaker should sound
  else
  {
    tone(SPEAKER_PIN, annoyingness); // Adjust the tone according to the herz
  }
}

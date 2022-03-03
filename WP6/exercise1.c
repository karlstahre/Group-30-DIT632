// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 6
// Exercise 1
// Submission code: 771088

// Power Supply values used:
// Voltage = 5
// Current = 1.1

// Definition of pins
#define ENCA 2 	// Encoder-A pin
#define ENCB 3  // Encoder-B pin
#define PWM1 5	// PWM1 pin
#define PWM2 6	// PWM2 pin
 
volatile int pos = 0; // Position in ticks. Volatile because used in ISR.
int deg = 0; // Position in degrees

int degtarget = 0; // Target position in degrees

int speed = 0; // Desired motor speed

int kp = 5; // Proportional constant for controller (tuning parameter)
int u_out = 0; // output of controller

int e = 0; // error
int a = 0; // a-encoder signal
int b = 0; // b-encoder signal

void ISR_readEncoder();

void setup() {
 
  Serial.begin(9600);
  pinMode(ENCA,INPUT_PULLUP);
  pinMode(ENCB,INPUT_PULLUP);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);  
  
  // Trigger ISR on RISING of ENCA (when receiving signal from encoder)
  attachInterrupt(digitalPinToInterrupt(ENCA),ISR_readEncoder,RISING);
  
  // Start the motor, just a tiny little bit because otherwise TinkerCad dies....
  analogWrite(PWM2, 10); 
  delay(1000); // TinkerCad bug
  analogWrite(PWM1, 10);
}

void loop() {
  // Stop the motor, but not to zero because then TinkerCad dies....
  analogWrite(PWM1, 10);
  delay(1000); // TinkerCad...bug
  analogWrite(PWM2, 10);
  
  // Check if motor rotated all the way around, and reset counter
    if (pos > 2299){
      deg = deg - 359;
      pos = pos - 2299;
    }
    if (pos < 0){
      deg = 359 + deg;
  	  pos = 2299 + pos;
    }
  
  // Print current position
  Serial.print("The current position is: ");
  Serial.print(deg);
  Serial.print("\n");
   
  // Get input 
  degtarget = getInput();
  
  // Calculate initial error.
  // When calculating e, deg and degtarget have been swapped
  // according to assignment description.
  e = deg - degtarget;
  
  // Print error
  Serial.print("Initial error: ");
  Serial.println(e);
  
  // Loop until error is zero
  while(e){
    
    // Printing the error as it decreases
    Serial.println(e);
    
    // Map current position into degrees
    deg = map(pos,0,2299,0,359);
       
  	// Get necessary speed signal
  	speed = getAction(e);
    
  	// Send speed signal to motor
    // Rotating clockwise
    if(speed >= 0){
    	if (speed < 100) // motor does not react with too low inputs
      	speed = 100;
      analogWrite(PWM2, 0);
      analogWrite(PWM1, speed);
  	}
  
    // Rotating counter-clockwise
  	else{
    	if (-speed < 100) // motor does not react with too low inputs
      	speed = -100; 
      analogWrite(PWM1, 0);
      analogWrite(PWM2, -speed); 
    }
	
    // Calculate new error
  	e = deg - degtarget;
  }
}

int getInput(){
  
  int ready = 0;
  char buf[3];
  int input = -1;
  
  Serial.print("Please enter the desired position: \n");
  
  while(!ready){
    ready = Serial.readBytes(buf,3);
    input = atoi(&buf[0]);
  }
 
  return input;
}  

int getAction(int error){
  
  //Calculate u_out as function of the error and the kp (tuning parameter).
  u_out = kp * error;
  
  if (u_out > 254){ //u_out cannot be more than 255...
  	return 255;
  }
  else if (u_out < -254){ //...or less than -254
    return -255;
  }  
  else
     return u_out;
}

// This method reads the encoder signals and increase or decrease pos accordingly.
// pos increases when both signals are high,
// pos decreases when signals are different,
// since the clockwise movement of the motor corresponds
// to negative rpm according to TinkerCad, and vice-versa.
void ISR_readEncoder(){
  
  a = digitalRead(ENCA);	// Read state of Encoder-A
  b = digitalRead(ENCB);	// Read state of Encoder-B
  
  // Handles case when b and a are both high
  if(b == a){
    pos++;	// Increase position
  }
  // Handles case when b and a are different values
  else{
    pos--;	// Decrease position
  }
}

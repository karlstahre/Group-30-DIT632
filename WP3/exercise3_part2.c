// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 3
// Exercise 3 part 2
// Submission code: 185160

#include <Keypad.h> 	// Library used for keypad operations

// Taken from https://arduinogetstarted.com/tutorials/arduino-keypad

const int ROW_NUM = 4; 		// four rows
const int COLUMN_NUM = 4; 	// four columns

// Initialize array of keys according to physical keypad structure
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_rows[ROW_NUM] = {11, 10, 9, 8}; 	//connect to the row pins of the keypad
byte pin_column[COLUMN_NUM] = {7, 6, 5, 4}; //connect to the column pins of the keypad

// Create an instance of keypad, passing the parameters declared above to a constructor
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup(){
  Serial.begin(9600); 	// set up serial communication
}

void loop(){
  // Scan keypad by accessing each row and column
  // and store pressed key in a variable
  char key = keypad.getKey();

  // Handles case if key is pressed
  if (key){
    // Print pressed key to the serial monitor
    Serial.println(key);
  }
}

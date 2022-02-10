// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 3
// Exercise 3 part 1
// Submission code: 185160

// constants, rows and columns are initialized to their corresponding pins
const int row1 = 11;
const int row2 = 10;
const int row3 = 9;
const int row4 = 8;
const int column1 = 7;
const int column2 = 6;
const int column3 = 5;
const int column4 = 4;
const int ROW_NUM = 4; 
const int COLUMN_NUM = 4;

// arrays for the rows and columns, refering to the corresponding pins
char rows[ROW_NUM] = {row1, row2, row3, row4};
char columns[COLUMN_NUM] = {column1, column2, column3, column4};

// matrix with 4 rows and 4 columns representing the keypad
char keypad[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

void setup()
{
  Serial.begin(9600); // Set up serial communication
  DDRB |= B00001111; // Pins from 8 to 11 are set to output
  DDRD |= B00000000; // Pins from 4 to 7 are set to input
}

void loop()
{
    // Function call to scan the keypad
    scanKeypad();
  	// Delay by 1 second
    delay(1000);
}

void scanKeypad()
{
  // Iterating through the row
  for (int row = 0; row < ROW_NUM; row++)
  {
    // Iterating through the column
    for (int col = 0; col < COLUMN_NUM; col++)
    {
      // Function call to check row by row
      PORTB = selectRow(row);
      // Handles case to check when one button is pressed
      if (digitalRead(columns[col]) == LOW)
      {
         // Print the value of the current position in the matrix
         Serial.println(keypad[row][col]);
      }
    }
  }
}

// This function sets row pins one by one to low depending on
// the parameter which is the current row checked
byte selectRow(int currentRow)
{
  // Handles case for checking the first row
  // and returns the byte value so that the current row
  // gets turned low
  if (rows[currentRow] == row1)
  {
    return B00000111;
  }
  // Handles case for checking the second row
  // and returns the byte value so that the current row
  // gets turned low
  else if (rows[currentRow] == row2)
  {
    return B00001011;
  }
  // Handles case for checking the third row
  // and returns the byte value so that the current row
  // gets turned low
  else if (rows[currentRow] == row3)
  {
    return B00001101;
  }
  // Handles case for checking the fourth row
  // and returns the byte value so that the current row
  // gets turned low
  else if (rows[currentRow] == row4)
  {
    return B00001110;
  }
}

//TODO: add comments and headers with our names
const int row1 = 11;
const int row2 = 10;
const int row3 = 9;
const int row4 = 8;
const int column1 = 7;
const int column2 = 6;
const int column3 = 5;
const int column4 = 4;

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char rows[ROW_NUM] = {row1, row2, row3, row4};
char columns[COLUMN_NUM] = {column1, column2, column3, column4};

char keypad[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

char previousInput = UNUSED_CHAR;
int counter = 0;

void setup()
{
  Serial.begin(9600);
  DDRB |= B00001111; // Pins from 8 to 11 are set to output
  DDRD |= B00000000; // Pins from 4 to 7 are set to input
}

void loop()
{
    
    readRows();
    delay(1000);
}

void readRows()
{
  // Iterating throught the row pins
  for (int row = 0; row < ROW_NUM; row++)
  {
    // Iterating through the column pins
    for (int col = 0; col < COLUMN_NUM; col++)
    {
      PORTB = selectRow(row);
      if (digitalRead(columns[col]) == LOW)
      {
         Serial.println(keypad[row][col]);
      }
    }
  }
}

byte selectRow(int currentRow)
{
  if (rows[currentRow] == row1)
  {
    return B00000111;
  }
  else if (rows[currentRow] == row2)
  {
    return B00001011;
  }
  else if (rows[currentRow] == row3)
  {
    return B00001101;
  }
  else if (rows[currentRow] == row4)
  {
    return B00001110;
  }
}

// TODO: add comments and header with our names

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

char keypad[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

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
  /*
  for (int row = 0; row < sizeof keypad; row++)
  {
    for (int col = 0; col < sizeof keypad[row]; col++)
    {
      delay(1000);
      PORTB = B00000111;
      if (digitalRead(column1) == LOW)
      {
         Serial.println(keypad[row][col]);
      }
      else if (digitalRead(column2) == LOW)
      {
         Serial.println(keypad[row][col]);
      }
    }
  }
  */
    
  Serial.print(sizeof keypad);
  PORTB = B00000111;
  if (digitalRead(column1) == LOW)
  {
    Serial.println(keypad[0][0]);
  }
  else if (digitalRead(column2) == LOW)
  {
    Serial.println(keypad[0][1]);
  }
  else if (digitalRead(column3) == LOW)
  {
    Serial.println(keypad[0][2]);
  }
    else if (digitalRead(column4) == LOW)
  {
    Serial.println(keypad[0][3]);
  }

  PORTB = B00001011;
    if (digitalRead(column1) == LOW)
  {
    Serial.println(keypad[1][0]);
  }
  else if (digitalRead(column2) == LOW)
  {
    Serial.println(keypad[1][1]);
  }
  else if (digitalRead(column3) == LOW)
  {
    Serial.println(keypad[1][2]);
  }
    else if (digitalRead(column4) == LOW)
  {
    Serial.println(keypad[1][3]);
  }
  
  PORTB = B00001101;
  if (digitalRead(column1) == LOW)
  {
    Serial.println(keypad[2][0]);
  }
  else if (digitalRead(column2) == LOW)
  {
    Serial.println(keypad[2][1]);
  }
  else if (digitalRead(column3) == LOW)
  {
    Serial.println(keypad[2][2]);
  }
    else if (digitalRead(column4) == LOW)
  {
    Serial.println(keypad[2][3]);
  }
    
  PORTB = B00001110;
  if (digitalRead(column1) == LOW)
  {
    Serial.println(keypad[3][0]);
  }
  else if (digitalRead(column2) == LOW)
  {
    Serial.println(keypad[3][1]);
  }
  else if (digitalRead(column3) == LOW)
  {
    Serial.println(keypad[3][2]);
  }
    else if (digitalRead(column4) == LOW)
  {
    Serial.println(keypad[3][3]);
  }
}

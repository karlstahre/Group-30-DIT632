// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 1
// Exercise 4
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // library used for getting max and min value of data types

#define SIZE_8 8
#define SIZE_16 16
#define SIZE_32 32

typedef unsigned char byte;
/*
   Two programs:
1. Decimal to binary
2. Binary to hex
  Constraints:
- Must be executed in a pipeline
- Any  number  between  0  and  the  maximum  value  of  type  long  in  C  for  your compiler
- Use the smallest possible datatype for a given number.
- Use the program arguments so that it is possible to use these two programs like this:
  dec2bin.exe 12 | bin2hec.exe
  The programs should be fail-safe, i.e.
• Should check if the string of the argument contains the correct digits
• Should be able to provide help if the user provides the parameter ‘-h’
• Should output an error message if the conversion was not successful
• Should return 2 if the conversion is unsuccessful
*/
void toBinary(long input, char arr[], int size);
long countBits(long input);
void fillArray(char arr[], int size);

int main(int argc, char* argv[])
{
    long input = strtol(argv[1], NULL, 10);

    if (argc < 2)
    {
        printf("Please provide an argument");
    }
    else if (input >= 0 && input < LONG_MAX)
    {
        long bits = countBits(input);
        if (bits <= SIZE_8)
        {
            char arr8[SIZE_8];
            toBinary(input, arr8, SIZE_8);
        }
        else if (bits <= SIZE_16)
        {
            char arr16[SIZE_16];
            toBinary(input, arr16, SIZE_16);
        }
        else if (bits <= SIZE_32)
        {
            char arr32[SIZE_32];
            toBinary(input, arr32, SIZE_32);
        }
        return 0;
    }
    else if (strcmp(argv[1], "-h") == 0)
    {
        printf("Please provide a decimal number to convert to binary");
    }
    else
    {
        printf("%s", "The conversion was not successful");
        return 2;
    }
}
void toBinary(long decimalNo, char arr[], int size )
{
    fillArray(arr, size);
    int i = size - 1;
    while (decimalNo > 0)
    {
        int remainder = decimalNo % 2;
        arr[i] = remainder;
        i--;
        decimalNo = decimalNo / 2;
    }
    for (int j = 0; j < size; j++) {
        printf("%d", arr[j]);
    }
}
// https://www.includehelp.com/cpp-programs/find-total-number-of-bits-required-to-represent-a-number-in-binary.aspx
// method to count bits for a given number
long countBits(long decimalNo)
{
    long count = 0;
    while (decimalNo)
    {
        count++;
        decimalNo = decimalNo >> 1;
    }
    return count;
}
// Iterate through the given array setting all occurrencies at 0
void fillArray(char arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = 0;
    }
}

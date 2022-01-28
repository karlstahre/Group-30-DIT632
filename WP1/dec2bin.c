// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 1
// Exercise 4
// Submission code: 920759
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // library used for getting max and min value of data types
#include <string.h> // used for strcmp() to convert to a string
#include <errno.h>  // used to check errors

// define macros with different bit sizes
#define SIZE_8 8
#define SIZE_16 16
#define SIZE_32 32
#define PROMPT_1 "Please provide one argument" // Displays when the user provides more or less than one argument
#define PROMPT_2 "Please provide a decimal number to convert to binary" // Displays when the user enters "-h" to get help
#define NO_SUCCESS "The conversion was not successful" // Displays when conversion was not possible due to out of range, string provided or any other potential issue

// ------ Function declarations ----------

// This funtion takes user input which is a decimal number, 
// then converts it to binary and prints it
void toBinary(long input, char arr[], int size);

// This function counts how many bits there are for a given number
long countBits(long input);

// This function is passed an empty array and the size it needs (i.e. how many bits)
// and fills the array with 0s
void fillArray(char arr[], int size);

// ------ Function definitions ----------

int main(int argc, char* argv[])
{
    long input = strtol(argv[1], NULL, 10); // Variable storing the user input, casting it to a long

    // Handles case where the number of arguments provided exeeds or is lower that one
    if (argc < 2 || argc > 2)
    {
        printf("%s", PROMPT_1);
        return 2;
    }
    // Handles case where the user types "-h" and wants help
    else if (strcmp(argv[1], "-h") == 0)
    {
        printf("%s", PROMPT_2);
        return 0;
    }
    // Handles case where if the value provided was out of range, 
    // or if letters are provided instead of a number,
    // which means that the content of the first argument should not be equal to 0
    // but the input will be 0 because it was casted to a long earlier
    else if (errno == ERANGE || (strcmp(argv[1], "0") != 0 && input == 0))
    {
        // output an error message if the conversion was not successful
        printf("%s", NO_SUCCESS);
        return 2;
    }
    // Handles case where input should be larger or equal to 0 and smaller or equal to the maximum value of datatype long
    else if (input >= 0 && input <= LONG_MAX)
    {
        // Function call, count bits and store it in a variable
        long bits = countBits(input);
        // Handles case when the bits are smaller or equal to 8
        if (bits <= SIZE_8)
        {
            // Create an array of size 8
            char arr8[SIZE_8];
            // Function call, pass the input, array and bit size
            toBinary(input, arr8, SIZE_8);
        }
        // Handles case when the bits are smaller or equal to 16
        else if (bits <= SIZE_16)
        {
            // Create an array of size 16
            char arr16[SIZE_16];
            // Function call, pass the input, array and bit size
            toBinary(input, arr16, SIZE_16);
        }
        // Handles case when the bits are smaller or equal to 32
        else if (bits <= SIZE_32)
        {
            // Create an array of size 32
            char arr32[SIZE_32];
            // Function call, pass the input, array and bit size
            toBinary(input, arr32, SIZE_32);
        }
        return 0;
    }
    // Handles any other case that may occur
    else
    {
        printf("%s", NO_SUCCESS);
        return 2;
    }
}

// ------ to_binary --------------------------
void toBinary(long decimalNo, char arr[], int size)
{
    // Function call to fill empty array with 0s
    fillArray(arr, size);
    int i = size - 1; // variable for the last position in the array

    // As long as the user input/decimal number is larger than 0
    while (decimalNo > 0)
    {
        int remainder = decimalNo % 2; // Store the remainder of the decimal number modulo 2
        arr[i] = remainder; // Insert the remainder in the correct position in the array
        i--; // Decrease index to move the position the left in the array
        decimalNo = decimalNo / 2; // Update the decimal number
    }
    // Print each position in the array
    for (int j = 0; j < size; j++) {
        printf("%d", arr[j]);
    }
}

// ------ count_bits --------------------------
// Code inspired by: https://www.includehelp.com/cpp-programs/find-total-number-of-bits-required-to-represent-a-number-in-binary.aspx
long countBits(long decimalNo)
{
    long count = 0; // Variable to store a counter of how many bits there are, default 0
    // As long a decimal number is not 0
    while (decimalNo)
    {
        count++; // Increase count by 1
        decimalNo = decimalNo >> 1; // Shift the bit by one and update the new value for decimal number
    }
    // Return value
    return count;
}

// ------ fill_array --------------------------
void fillArray(char arr[], int size)
{
    // Iterate through the given array setting all occurrencies at 0
    for (int i = 0; i < size; i++)
    {
        arr[i] = 0;
    }
}

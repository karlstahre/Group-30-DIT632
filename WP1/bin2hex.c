// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 1
// Exercise 4 part 2
// Submission code: 920759

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Used for strlen() method to check length of array
#include <errno.h> // Library used for error handling

#define PROMPT_1 "Please provide one argument" // Used if user does not provide arguments or provides more than one
#define HELP "Please provide a binary number to convert to hexadecimal" // Used if user provides -h as argument
#define CONVERSION_UNSUCCESSFUL "The conversion was not successful" // Used if an error occurred in the conversion due to wrong user input
#define RANGE_HEX 15 // Range of hex values 0-15
#define ASCII_0 48 // ASCII value of 0
#define ASCII_1 49 // ASCII value of 1

// ------ Functions declarations -----------

// This function is passed an empty array and the size it needs (i.e. how many bits)
// and fills the array with 0s
void fillArray(char arr[], int size);

// This methods checks if the first argument of the program contains digits different than 1 or 0
// Returns 1 if the argument provided is in binary format
// Returns 0 if the argument provided is in another number format
int isBinary(char* firstArgument);

// Algorithm inspired from: https://codeforwin.org/2015/08/c-program-to-convert-binary-to-hexadecimal-number-system.html
// This funtion takes user input which is a binary number, 
// then converts it to hexadecimal and prints it
void toHexadecimal(long long binary);

// ------ Function definitions ----------

// ------ Main --------------------------
// This program converts the first argument, a binary number, 
// to its hexadecimal value, and prints it
int main(int argc, char* argv[])
{
   long long binary = strtoll(argv[1], NULL, 10); // Parse first string argument 

    // Handles case where the number of arguments provided exeeds or is lower than one
    if (argc < 2 || argc > 2)
    {
        printf("%s", PROMPT_1);
        return 2;
    }
    // Handles case where the user types "-h" and wants help
    else if (strcmp(argv[1], "-h") == 0)
    {
        printf("%s", HELP); // Output help message
    }
    // Handles case where user input is a character or a string or a number format that is not binary
    else if ((strcmp(argv[1], "0") != 0 && binary == 0) || isBinary(argv[1]) == 0)
    {
        printf("%s", CONVERSION_UNSUCCESSFUL); // Output error message if the conversion was not successful
        return 2;
    }
    
    toHexadecimal(binary); // Convert binary number to hexadecimal

}

// ------ fillArray --------------------------
// Iterate through the given array setting all occurrencies at 0
void fillArray(char hex[], int size)
{
    for (int i = 0; i < size; i++)
    {
        hex[i] = 0;
    }
}

// ------ isBinary --------------------------
int isBinary(char* firstArgument)
{
    // Iterate through each character in the first argument
    for (int i = 0; i < strlen(firstArgument); i++)
    {
        // If a character is not 0 and not 1, the first argument is not in binary format
        // Note: we have to check for the ascii value of "0" and "1" the character
        // Therefore return 0

        if (firstArgument[i] != ASCII_0 && firstArgument[i] != ASCII_1)
        {
            return 0;
        }
    }
    // Otherwise the first argument is in binary format
    // Therefore return 1
    return 1;
}

// ------ toHexadecimal --------------------------
void toHexadecimal(long long binary) 
{
    // Declare array containing all hexadecimal values 0-F
    int hexConstant[] = { 0, 1, 10, 11, 100, 101, 110, 111, 1000,
                         1001, 1010, 1011, 1100, 1101, 1110, 1111 };

    long long tempBinary; // Temporary binary that will hold groups of four digits
    char hex[20]; // Array that will be printed as output, each slot containing an hex digit
    int index = 0; // Index to be used in array hex
    int digit; // Element that will go into a slot of hex array

    fillArray(hex, 20); // Fill the array with 0s for output format reasons

    // Copy binary number to temp variable
    tempBinary = binary;
    index = 0;

    // Loop until tempBinary reaches 0
    while (tempBinary != 0)
    {
        // Group binary to last four digits, since four binary digits are equal to one hexadecimal digit
        digit = tempBinary % 10000;

        // Find hexadecimal equivalent of last four digits
        // Loop until i reaches range for hexadecimal
        for (int i = 0; i <= RANGE_HEX; i++)
        {
            // Handles case if current digit is equal to current position in array of constants
            if (digit == hexConstant[i])
            {
                // Handles case if current i corresponds to a number in hex
                if (i < 10)
                {
                    // 0-9 integer constant
                    hex[index] = (char)(i + 48);
                }
                // Handles case if current i corresponds to a letter in hex
                else
                {
                    // A-F character constant
                    hex[index] = (char)((i - 10) + 65);
                }

                index++;
                break;
            }
        }

        // Remove the last 4 digits, sinze they have been processed
        tempBinary /= 10000;
    }

    _strrev(hex); // Reverse the hex array

    printf("%s", hex); // Print output array
}

// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 2
// Exercise 4 part 2 (decode.c)
// Submission code: 960059

#include <stdio.h>          // Library used for printf() and others
#include <stdlib.h>         // Library used for strtol()
#include <string.h>         // Library used for strcmp()
#include <ctype.h>          // Library used for isxdigit()

#define REQUIRED_ARGS   2   // Required number of arguments, including name of executable
#define MAX_ARGS_LENGTH 2   // Maximum length of hex argument. Here, not longer than what can be stored in a byte
#define OUTPUT_BITS     5   // Amount of bit values that will be unpacked from the argument
// ------ Error messages regarding arguments ------
#define WRONG_ARGS_AMOUNT   "Wrong arguments amount. Please provide 1 argument for this program\n"
#define ARGS_TOO_LARGE      "Argument provided too large. Please provide 1 byte hexadecimal argument (e.g., AB)\n"
#define ARGS_NOT_HEX        "Argument not in hexadecimal format. Please provide argument in hexadecimal format\n"
#define ARGS_OUTSIDE_RANGE  "Argument outside defined ranges. Please provide argument within defined ranges\n"
#define HELP                "Please provide 1 byte hexadecimal argument (e.g., AB)\n"
#define ARGS_GENERIC_ERROR  "Argument was not provided correctly. Please try again\n"
// ------ Output table strings ------
#define HEADER_NAME         "Name"
#define HEADER_VALUE        "Value"
#define LINE_SEPARATOR      "-------------------------"
#define ENGINE_ON_STR       "engine_on"
#define GEAR_POS_STR        "gear_pos"
#define KEY_POS_STR         "key_pos"
#define BRAKE_1_STR         "brake_1"
#define BRAKE_2_STR         "brake_2"
// ------ Bit positions for each argument provided -------
//                          BIT_POSITION    Info                Description
#define BIT_ENGINE_ON       7               // Bit 7 (MSB).     Is engine on or off
#define BIT_GEAR_POS        4               // Bits 4, 5, 6.    The position of the gear
#define BIT_KEY_POS         2               // Bits 2, 3.       Key 0 -> stop, 1 -> on, 2-> engine starter on
#define BIT_BRAKE_1         1               // Bit 1.           Position of the front brakes
#define BIT_BRAKE_2         0               // Bit 0 (LSB).     Position of the rear brakes
// ------ Ranges for each argument provided ------
//                          MAX_VALUE       Range
#define RANGE_ENGINE_ON     1               // 0..1
#define RANGE_GEAR_POS      4               // 0..4
#define RANGE_KEY_POS       2               // 0..2
#define RANGE_BRAKE_1       1               // 0..1
#define RANGE_BRAKE_2       1               // 0..1
// ------ Bit values in decimal format used for mask operations ------
//                          VALUE           Masks
#define BIT_7               128             // ENGINE_ON
#define BIT_4_5_6           112             // GEAR_POS
#define BIT_2_3             12              // KEY_POS
#define BIT_1               2               // BRAKE_1
#define BIT_0               1               // BRAKE_2

// ------ Function declarations ----------

// This method takes an unsigned char in decimal format and an unsigned char array
// And fills it with values according to the defined bits above for the car
void unpackByteToBits(unsigned char decimalValue, unsigned char bits[]);

// This method takes an array containing the bit values
// and prints them out according to the format specified in main() example
void printOutputTable(unsigned char bits[]);

// This method checks the arguments provided by the user
// Returns 1 if REQUIRED_ARGS are provided and in hex format
// Example: AB => Returns 1
// Returns 0 otherwise, including "-h" input for help
// Note: needs isArgumentsHex() to function
int isArgumentsCorrect(int argc, char* argv[]);

// This method checks the format of the argument provided by the user
// Returns 1 if the argument is in hexadecimal format
// Returns 0 otherwise
int isArgumentsHex(char* argv[]);

// This method checks the value of the argument provided by the user
// after it has been converted into an array of bits
// Returns 1 if all the bits are within the defined ranges
// Returns 0 otherwise
int isBitsWithinRange(unsigned char bits[]);

// ------ Function definitions ----------

// This program takes 1 byte hexadecimal argument as input
// Unpacks it and prints out the result as below:
//
//  Example
//  Input: AB
//  Output:
//  Name            Value
//  -----------------------------
//  engine_on       1
//  gear_pos        2
//  key_pos         2
//  brake1          1
//  brake2          1
int main(int argc, char* argv[])
{
    // Handles case where argument is provided correctly
    if (isArgumentsCorrect(argc, argv))
    {
        // Store first argument in hex format in one byte
        unsigned char decimalValue = strtol(argv[1], NULL, 16);
        // Initialize array that will contain the output bits
        unsigned char bits[OUTPUT_BITS] = {0};
        // Unpack the argument provided and put the bits in the array
        unpackByteToBits(decimalValue, bits);
        // Handles case where argument is provided within defined range
        if (isBitsWithinRange(bits))
        {
            // Prints a formatted table showing the result bits and values
            printOutputTable(bits);
            return 0;
        }
        // Returns 1 if argument was not provided within defined range
        return 1;
    }
        // Handles case where argument is not provided correctly
    else
    {
        return 1;
    }
}

void unpackByteToBits(unsigned char decimalValue, unsigned char bits[])
{
    // Using mask operators to take only the relevant bit
    // Then use shift operator to store the real value of that bit
    // Example:
    // decimalValue == 171 ==   10101011
    //                        & 01110000  Mask operation takes only BIT_4_5_6
    //                        ----------
    //                          00100000
    //                  >> 4    00000010  Result needs to be shifted to become its real value
    bits[0] = (decimalValue & BIT_7) >> BIT_ENGINE_ON;      // Store bit value of engine_on
    bits[1] = (decimalValue & BIT_4_5_6) >> BIT_GEAR_POS;   // Store bit value of gear_pos
    bits[2] = (decimalValue & BIT_2_3) >> BIT_KEY_POS;      // Store bit value of key_pos
    bits[3] = (decimalValue & BIT_1) >> BIT_BRAKE_1;        // Store bit value of brake_1
    bits[4] = (decimalValue & BIT_0) >> BIT_BRAKE_2;        // Store bit value of brake_2
}

void printOutputTable(unsigned char bits[])
{
    // Print a table with headers and values formatted as described in the main() example
    printf("%s \t\t %s \n", HEADER_NAME, HEADER_VALUE);
    printf("%s \n", LINE_SEPARATOR);
    printf("%s \t %d \n", ENGINE_ON_STR, bits[0]);
    printf("%s \t %d \n", GEAR_POS_STR, bits[1]);
    printf("%s \t %d \n", KEY_POS_STR, bits[2]);
    printf("%s \t %d \n", BRAKE_1_STR, bits[3]);
    printf("%s \t %d \n", BRAKE_2_STR, bits[4]);
}

int isArgumentsCorrect(int argc, char* argv[])
{
    // Handles case where -h is provided as argument for help
    if (strcmp(argv[1], "-h") == 0)
    {
        printf("%s", HELP);
        return 0;
    }
        // Handles case where wrong amount of arguments is provided
    else if (argc != REQUIRED_ARGS)
    {
        printf("%s", WRONG_ARGS_AMOUNT);
        return 0;
    }
        // Handles case where too large argument is provided (more than 1 byte)
    else if (strlen(argv[1]) > MAX_ARGS_LENGTH)
    {
        printf("%s", ARGS_TOO_LARGE);
        return 0;
    }
        // Handles case where REQUIRED_ARGS are provided and in hexadecimal format
    else if (isArgumentsHex(argv))
    {
        return 1;
    }
        // Handles unexplored cases
    else
    {
        printf("%s", ARGS_GENERIC_ERROR);
        return 0;
    }
}

int isArgumentsHex(char* argv[])
{
    // Iterates through the content of one argument
    for (int j = 0; j < strlen(argv[1]); j++)
    {
        // Handles case where content of one argument is a value outside hexadecimal
        if (isxdigit(argv[1][j]) == 0)
        {
            printf("%s", ARGS_NOT_HEX);
            return 0;
        }
    }
    // Returns 1 if no values outside hexadecimal were encountered
    return 1;
}

int isBitsWithinRange(unsigned char bits[])
{
    // Handles case where at least one of the arguments provided is outside the defined ranges
    if (bits[0] > RANGE_ENGINE_ON ||
        bits[1] > RANGE_GEAR_POS ||
        bits[2] > RANGE_KEY_POS ||
        bits[3] > RANGE_BRAKE_1 ||
        bits[4] > RANGE_BRAKE_2)
    {
        printf("%s", ARGS_OUTSIDE_RANGE);
        return 0;
    }
    // Returns 1 if no values outside the defined ranges were encountered
    return 1;
}

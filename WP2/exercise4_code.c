// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 2
// Exercise 4 part 1 (code.c)
// Submission code: xxxxxx

#include <stdio.h>          // Library used for printf() and others
#include <stdlib.h>         // Library used for strtol()
#include <string.h>         // Library used for strcmp()

#define REQUIRED_ARGS 6     // Required number of arguments, including name of executable
// ------ Error messages regarding arguments ------
#define WRONG_ARGS_AMOUNT   "Wrong arguments amount. Please provide 5 arguments for this program\n"
#define ARGS_NOT_DECIMAL    "Arguments not in decimal format. Please provide arguments in decimal format\n"
#define ARGS_OUTSIDE_RANGE  "Arguments outside defined ranges. Please provide arguments within defined ranges\n"
#define HELP                "Please provide 5 bits arguments (e.g., 1 2 2 1 1)\n"
#define ARGS_GENERIC_ERROR  "Arguments were not provided correctly. Please try again\n"
// ------ Useful ASCII values for character comparison ------
#define ASCII_0 48
#define ASCII_9 57
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

// ------ Function declarations ----------

// This method takes an array of arguments
// And returns an unsigned char containing the arguments
// According to the defined bits above for the car
unsigned char packBitsToByte(char* argv[]);

// This method checks the arguments provided by the user
// Returns 1 if REQUIRED_ARGS are provided and in decimal format
// Example: 1 2 2 1 1 => Returns 1
// Returns 0 otherwise, including "-h" input for help
// Note: needs isArgumentsDecimal() and isArgumentsWithinRange() to function
int isArgumentsCorrect(int argc, char* argv[]);

// This method checks the format of the arguments provided by the user
// Returns 1 if all the arguments are in decimal format
// Returns 0 otherwise
int isArgumentsDecimal(char* argv[]);

// This method checks the value of the arguments provided by the user
// Returns 1 if all the arguments are within the defined ranges
// Returns 0 otherwise
int isArgumentsWithinRange(char* argv[]);

// ------ Function definitions ----------

// This program takes the following arguments as input
//
// Name         Range   Info
// engine_on    0..1    Is engine on or off.
// gear_pos     0..4    The position of the gear.
// key_pos      0..2    Position of the key – 0 == stop, 1 == on, 2 == engine starter on
// brake1       0..1    Position of the front brakes
// brake2       0..1    Position of the rear brakes
//
// Packs them into a byte using an unsigned char
// And prints the result in hexadecimal format.
// Example: Input        Output
//          1 2 2 1 1    ab
int main(int argc, char* argv[])
{
    // Handles case where arguments are provided correctly
    if (isArgumentsCorrect(argc, argv))
    {
        unsigned char packedByte = packBitsToByte(argv);    // Store packed byte into unsigned char
        printf("%x", packedByte);                    // Print packed byte in hexadecimal format
        return 0;
    }
        // Handles case where arguments are not provided correctly
    else
    {
        return 1;
    }
}

unsigned char packBitsToByte(char* argv[])
{
    int decimalValue; // Declare decimal value of one argument
    unsigned char byteValue = 0; // Declare byte value to be returned

    // Store decimal value of argument 1 into the byte
    // By shifting as many bits as specified by BIT_ENGINE_ON
    decimalValue = (strtol(argv[1], NULL, 10));
    byteValue += decimalValue << BIT_ENGINE_ON;

    // Store decimal value of argument 2 into the byte
    // By shifting as many bits as specified by BIT_GEAR_POS
    decimalValue = (strtol(argv[2], NULL, 10));
    byteValue += decimalValue << BIT_GEAR_POS;

    // Store decimal value of argument 3 into the byte
    // By shifting as many bits as specified by BIT_KEY_POS
    decimalValue = (strtol(argv[3], NULL, 10));
    byteValue += decimalValue << BIT_KEY_POS;

    // Store decimal value of argument 4 into the byte
    // By shifting as many bits as specified by BIT_BRAKE_1
    decimalValue = (strtol(argv[4], NULL, 10));
    byteValue += decimalValue << BIT_BRAKE_1;

    // Store decimal value of argument 5 into the byte
    // By shifting as many bits as specified by BIT_BRAKE_2
    decimalValue = (strtol(argv[5], NULL, 10));
    byteValue += decimalValue << BIT_BRAKE_2;

    return byteValue;
}

int isArgumentsCorrect(int argc, char* argv[])
{
    // Handles case where REQUIRED_ARGS are provided and in decimal format within defined range
    if (argc == REQUIRED_ARGS && isArgumentsDecimal(argv) && isArgumentsWithinRange(argv))
    {
        return 1;
    }
        // Handles case where -h is provided as argument for help
    else if (strcmp(argv[1], "-h") == 0)
    {
        printf("%s", HELP);
        return 0;
    }
        // Handles case where wrong amount of arguments is provided
    else if (argc != REQUIRED_ARGS)
    {
        printf("%s, %d", "This many args", argc);
        printf("%s", WRONG_ARGS_AMOUNT);
        return 0;
    }
        // Handles unexplored cases
    else
    {
        printf("%s", ARGS_GENERIC_ERROR);
        return 0;
    }
}

int isArgumentsDecimal(char* argv[])
{
    // Iterates through the arguments. Note: start at arg 1 and end at 5
    for (int i = 1; i < REQUIRED_ARGS; i++)
    {
        // Iterates through the content of one argument
        for (int j = 0; j < strlen(argv[i]); j++)
        {
            // Handles case where content of one argument is a value outside the decimals in the ASCII table
            if (argv[i][j] < ASCII_0 || argv[i][j] > ASCII_9)
            {
                printf("%s", ARGS_NOT_DECIMAL);
                return 0;
            }
        }
    }
    // Returns 1 if no values outside decimal were encountered
    return 1;
}

int isArgumentsWithinRange(char* argv[])
{
    // Handles case where at least one of the arguments provided is outside the defined ranges
    if (strtol(argv[1], NULL, 10) > RANGE_ENGINE_ON ||
        strtol(argv[2], NULL, 10) > RANGE_GEAR_POS ||
        strtol(argv[3], NULL, 10) > RANGE_KEY_POS ||
        strtol(argv[4], NULL, 10) > RANGE_BRAKE_1 ||
        strtol(argv[5], NULL, 10) > RANGE_BRAKE_2)
    {
        printf("%s", ARGS_OUTSIDE_RANGE);
        return 0;
    }
    // Returns 1 if no values outside the defined ranges were encountered
    return 1;
}

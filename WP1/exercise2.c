// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 1
// Exercise 2
/* At the beginning of the program we include the libraries containing the functions we will
need to use throughout the program */
/* The standard input output library contains the printf(), fgets() function and stdin
variable used in the program*/
#include <stdio.h>
/* The standard library contains the atoi() function used in the program */
#include <stdlib.h>
/* The string library contains the strlen() function used in the program */
#include <string.h>
/* The ctype library contains the isupper() and islower() functions used in the program */
#include <ctype.h>
#define WELCOME "Please enter a message to be encrypted:\n\n"
/* This program is an encryption program based on the Caesar cipher, which is an ancient
encryption algorithm. The message is encrypted using an integer encryption key, which is
passed as an additional argument when running this program. The program takes an input string
from the user and returns the encrypted string, using the integer key to shift each letter of
the string to be encrypted the number of times specified by the key along th alphabet. */
int main(int argc, char* argv[])
{
    /* The do-while loop executes the code inside its scope once and then over and over
    until the EOF character is provided by e.g. typing Ctrl+C */
    do {
        /* Provides a brief instruction on how to use the program */
        printf("%s", WELCOME);

        /* This line of code converts the string argument to an integer */
        int encryptionKey = atoi(argv[1]);
        /* Here an array for storing the message to be encrypted is defined */
        char input[1000];
        /* This line reads the line of characters passed as input using the standard input
        stream and stores each character in the input array declared above */
        fgets(input, sizeof(input), stdin);
        /* The for loop loops over each letter stored in the input array and checks if it is an
        upper- or lower-case letter. Depending on the if the letter is capiatl or not will
        determine the initial ASCII number to be used in the mathematical algorithm for calculating
        the character to be used for encryption. The ASCII number is then used together with the
        encryption key passed as an argument when running the program as well as modular arithmic
        to keep the character output within the bounds of the 26-letter alphabet. */
        for (int i = 0; i < strlen(input); i++)
        {
            /* Checks if the letter is upper-case */
            if (isupper(input[i]))
            {
                /* Encrypts the letter using modular arithmetic and the encryption key to
                shift the ASCII value of the letter */
                input[i] = ((input[i] - 65 + encryptionKey) % 26) + 65;
            }
            /* Checks if the letter is lower-case */
            else if (islower(input[i]))
            {
                /* Encrypts the letter using modular arithmetic and the encryption key to
                shift the ASCII value of the letter */
                input[i] = ((input[i] - 97 + encryptionKey) % 26) + 97;
            }
        }


        // Handles case if input is not EOF
        if (!feof(stdin))
        {
            /* Prints the updated string stored in the array, which is the encrypted message where
               each index position now has a new ASCII value, and therefore represents a different
               character */
            printf("%s", input);
        }
        /* Checks if the condition is satisfied that the EOF character is entered;
        if if is, the program will exit the loop and terminate, otherwise do-while
        will execute again */
    } while (!feof(stdin));
}
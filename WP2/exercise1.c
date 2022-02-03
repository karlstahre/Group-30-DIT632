// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 2
// Exercise 1
// Submission code:

#include <stdio.h>
#include <stdlib.h>

// define macros
#define MAX_NUMBER 99 // Maximum x and y position
#define MIN_NUMBER 0  // Minimum x and y position
#define ARRAY_SIZE 30 // Size of the instructions of 'm' and 't' that the user provides
// The user is prompt with different stings depending on the situation
#define INSTRUCTIONS "Provide a string with instructions where m means move one space and t means turn 90 degree\n"
#define START_POSITION "Provide a starting position for x and y with a number from 0 to 99\n"
#define END_POSITION "The robot's end position is:\n"
#define WRONG_NUMBER "Not accepted number\n"

// ----- Enums -------------------------
enum DIRECTION {N,O,S,W};

// ----- Typedefs ----------------------
typedef struct {
    int xpos;
    int ypos;
    enum DIRECTION dir;
} ROBOT;

// ------ Function declarations ---------
void move(ROBOT* robot); // Move one step in current direction
void turn(ROBOT* robot); // Turn direction 90 degrees clockwise

// ------ Function definitions ----------

// ------ Main --------------------------
int main(void)
{
    int x_position = 0; // Variable to store user input x value
    int y_position = 0; // Variable to store user input y value
    char instructions[ARRAY_SIZE]; // Variable to store user input instructions with m and t

    do {
        // Ask for robot's starting position
        printf("%s", START_POSITION);
        // Scans user input for x and y position
        scanf("%d %d", &x_position, &y_position);
        // Handles case when the x and y positions are too large or too small, i.e. when they're smaller than 0 and larger than 99
        if (x_position < MIN_NUMBER || x_position > MAX_NUMBER || y_position < MIN_NUMBER || y_position > MAX_NUMBER)
        {
            printf("%s", WRONG_NUMBER);
        }
        // Handles case when the x and y positions are within accepted range
        else
        {
            // Ask for a string with "t"s and "m"s
            printf("%s", INSTRUCTIONS);
            // Scan user input for instructions
            scanf("%s", &instructions);
        }
        // This only happens when x and y positions are within accepted range and there's no EOF character
        if (x_position >= MIN_NUMBER && x_position <= MAX_NUMBER && y_position >= MIN_NUMBER && y_position < MAX_NUMBER && !feof(stdin))
        {
        // Creates a new robot
        ROBOT* robot;
        robot = malloc(sizeof(ROBOT)); // Allocate space in memory
        robot->ypos = y_position; // Updates y position to user input
        robot->xpos = x_position; // Updates x position to user input
        robot->dir = 0; // Default starting direction set to N

            // Iterate over the instructions to get character by character and pass them into the correct functions
            for (int i = 0; i < sizeof instructions; i++)
            {
                // If the characters at the given position are 'm' or 't', the program calls the functions
                // move or turn depending on the character
                if (instructions[i] == 'm')
                {
                    // Function call
                    move(robot);
                }
                else if (instructions[i] == 't')
                {
                    // Function call
                    turn(robot);
                }
            }
            // Prints the final x and y position
            printf("%s", END_POSITION);
            printf("%d %d \n", robot->xpos, robot->ypos);
            free(robot); // Frees space in the memory
        }
        // The program runs until it encounters the EOF character
    } while (!feof(stdin));
}

// ------ Move --------------------------
void move(ROBOT* robot)
{
    // This switch takes the current direction of the robot and changes xpos or ypos by 1
    // depending on the direction
    switch(robot->dir)
    {
        case N :
            // When the robot is turned north, the y position is increased by 1
            robot->ypos += 1;
            break;
        case O:
            // When the robot is turned east, the y position is increased by 1
            robot->xpos += 1;
            break;
        case S:
            // When the robot is turned south, the y position is decreased by 1
            robot->ypos -= 1;
            break;
        case W:
            // When the robot is turned west, the y position is decreased by 1
            robot->xpos -= 1;
            break;
        default:
            printf("%s", "ERROR\n");
            break;
    }
}

// ------ Turn --------------------------
void turn(ROBOT* robot)
{
    // This switch takes the current direction of the robot and changes it 90 degrees clockwise
    switch(robot->dir)
    {
        case N :
            // When the robot is turned north, the direction is changed to east
            robot->dir = O;
            break;
        case O:
            // When the robot is turned east, the direction is changed to south
            robot->dir = S;
            break;
        case S:
            // When the robot is turned south, the direction is changed to west
            robot->dir = W;
            break;
        case W:
            // When the robot is turned west, the direction is changed to north
            robot->dir = N;
            break;
        default:
            printf("%s", "ERROR\n");
            break;
    }
}

// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 1
// Exercise 3
// Submission code: 920759
#include <stdio.h>
#include <stdlib.h> // library to use rand() and get pseudo-random number
#include<time.h>    // used for srand()

// define macros
#define MAX_NUMBER 100 // Highest value that the user can guess
#define MIN_NUMBER 1   // Lowest value that the user can guess
#define MAX_TRIES 5    // Maximum number of guesses before game ends
#define TOO_LOW "Your guess is too low \n"
#define TOO_HIGH "Your guess is too high \n"
#define PLAY_AGAIN "Do you want to play again? Press 1 for yes \n"
#define GUESS "Guess a number from 1-100 \n"
#define ERROR "Please provide a number from 1-100 \n"

// ------ Function declarations ----------

// This function takes user input, which should be a number between 1-100,
// handles cases when the input does not match a number between 1-100,
// and checks if the number is equal to the random generated number by the computer
void playGame(int randomNumber, int input, int nrOfGuesses, int play);

// ------ Function definitions ----------

int main(void)
{
	// Creates a new seed so that the number suite isn't the same as last time when running the program again
	srand(time(0));

	int randomNumber = rand() % MAX_NUMBER + 1; // rand() generates a pseudo-random number, remainder of 100 + 1 to get a number between 1 and 100
	int input = 0;			 // User input from scanf
	int nrOfGuesses = 0; // How many times the user has guessed, default 0
	int play = 1;		 // As long as play is 1 the game will play, default 1

	// Function call
	playGame(randomNumber, input, nrOfGuesses, play);
}

// ------ play_game --------------------------
void playGame(int randomNumber, int input, int nrOfGuesses, int play)
{
	do
	{
		// Display a sentence asking the user for a number between 1-100
		printf("%s", GUESS);
		// Scan the user input
		scanf_s("%d", &input);

		// Handles case when user input is a correct guess
		if (input > MAX_NUMBER || input < MIN_NUMBER)
		{
			printf("%s", ERROR);
		}
		else if (input == randomNumber)
		{
			nrOfGuesses++; 	// Number of guesses increases by 1 by each guess
			// Display a message when the user wins and display how many times they guessed in that game
			printf("%s %d %s", "You have guessed", nrOfGuesses, "times and your guess is correct \n");
			// Display a question if the user wants to play again
			printf(PLAY_AGAIN);
			// Scan the user input
			scanf_s("%d", &input);

			// Handles case when the user wants to play again
			if (input == 1)
			{
				// Creates new random numbers for the next game
				randomNumber = rand() % MAX_NUMBER + 1;
				// Play is 1 and the user will play again
				play = 1;
			}

			// Handles case when the user wants to quit
			else
			{
				// By setting play to 0, the while loop will end
				play = 0;
			}
			// Number of guesses is reset to 0 for a new game
			nrOfGuesses = 0;
		}
		// Handles case when user input guess is lower than correct answer
		else if (input < randomNumber)
		{
			// Display message that the guess is too low
			printf(TOO_LOW);
			nrOfGuesses++; 	// Number of guesses increases by 1 by each guess
		}
		// Handles case when user input guess is higher than correct answer
		else if (input > randomNumber)
		{
			// Display message that the guess is too high
			printf(TOO_HIGH);
			nrOfGuesses++; 	// Number of guesses increases by 1 by each guess
		}

		// While will happen when:
		// 1. It's the first round or the user wants to play again after one round
		// 2. Max number of guesses is smaller as max number
	} while (play == 1 && nrOfGuesses < MAX_TRIES);
}

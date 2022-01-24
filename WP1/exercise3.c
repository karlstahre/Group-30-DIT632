// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 1
// Exercise 3
#include <stdio.h>
#include <stdlib.h> // library to use rand() and get pseudo-random number
#include<time.h>    // used for srand()

// define macros
#define MAX_NUMBER 100
#define TOO_LOW "Your guess is too low \n"
#define TOO_HIGH "Your guess is too high \n"
#define PLAY_AGAIN "Do you want to play again? Press 1 for yes \n"
#define GUESS "Guess a number from 1-100 \n"

int main(void)
{
	// Creates a new seed so that the number suite isn't the same as last time when running the program again
	srand(time(0));

	// Question: Is it fine with pseudo-random? Is it a problem that it seems to give a number from low to high?
	int randomNumber = rand() % MAX_NUMBER + 1; // rand() gives a pseudo-random number, remainder of 100 + 1 to get a number between 1 and 100
	int input;			 // User input from scanf
	int nrOfGuesses = 0; // How many times the user has guessed, default 0
	int play = 1;		 // As long as play is 1 the game will play, default 1

	do
	{
		printf("%s", GUESS);
		printf("%d", randomNumber);
		scanf("%d", &input);

		nrOfGuesses++; 	// Number of guesses increases by 1 by each guess

		// Handles case when user input is a correct guess
		if (input == randomNumber)
		{
			printf("%s %d %s", "You have guessed", nrOfGuesses, "times and your guess is correct \n");
			printf(PLAY_AGAIN);
			scanf("%d", &input);

			// Handles case when the user wants to play again
			if (input == 1)
			{
				// Creates new random numbers for the next game
				randomNumber = rand() % MAX_NUMBER + 1;
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
			printf(TOO_LOW);
		}
		// Handles case when user input guess is higher than correct answer
		else if (input > randomNumber)
		{
			printf(TOO_HIGH);
		}

		// While will happen when:
		// 1. It's the first round or the user wants to play again after one round
		// 2. Max number of guesses is smaller as max number
		// 3. User input is between 1 to 100
	} while (play == 1 && MAX_NUMBER > nrOfGuesses && input >= 0 && input <= 100);

	// TODO OPTIONAL: secure that the program does not fail (crashes) if a user by accident inputs a 
	//				  number outside of the range or a character / string
}
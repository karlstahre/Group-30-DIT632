// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 1
// Exercise 1
#include <stdio.h>

/* These lines are existing sentences that will be printed by the program once the user
	enters a number between 1 and 5. Define are defined as macros on top of the rest of
	the code to be referenced further down. */
#define SENTENCE1 "Hejsan morsan\n"
#define SENTENCE2 "Hejsan stabben\n"
#define SENTENCE3 "Här är brev från älsklingsgrabben\n"
#define SENTENCE4 "Det är bra här i kolonien\n"
#define SENTENCE5 "Vi är 28 gangstergrabbar i en stor barrack\n"
#define WELCOME "Please enter a number between 1 - 5\n"

/* This program urges the user to enter a number between 1 and 5, which it stores in an
int variable and then prints any of the five sentences defined as macros above, dependent
on which number the user enters. Entered in order the program prints the first verse of a
famous Swedish folk song. */
void main(void) {

	/* This is the variable to store the user input */
	int input;

	/* The do-while loop executes the code inside its scope once and then over and over
	until the user provides an input that does not fulfil the condition of being an integer
	between 1 and 5 */
	do {

		/* This print method urges the user to enter a number between 1 and 5 */
		printf("%s\n", WELCOME);

		/* This method reads the user input and stores it in the input variable defined
		above */
		scanf_s("%d", &input);

		/* This if statement checks if the input variable satisfies any of the conditions,
		i.e. if the user entered any of the numbers between 1 and 5 allowed */
		if (input == 1) {
			/* If the input is 1 the program prints the first sentence to the user */
			printf("%s\n", SENTENCE1);
		}
		else if (input == 2) {
			/* If the input is 2 the program prints the second sentence to the user */
			printf("%s\n", SENTENCE2);
		}
		else if (input == 3) {
			/* If the input is 3 the program prints the third sentence to the user */
			printf("%s\n", SENTENCE3);
		}
		else if (input == 4) {
			/* If the input is 4 the program prints the fourth sentence to the user */
			printf("%s\n", SENTENCE4);
		}
		else if (input == 5) {
			/* If the input is 5 the program prints the fifth sentence to the user */
			printf("%s\n", SENTENCE5);
		}

	/* If the condition that the input should be a number between 1 and 5 is not satisfied,
	then the loop is exited and the program terminates */
	} while (input > 0 && input < 6);
}

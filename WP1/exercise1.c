#include <stdio.h>

//defines macros
#define SENTENCE1 "Hejsan morsan\n\n"
#define SENTENCE2 "Hejsan stabben\n\n"
#define SENTENCE3 "Här är brev från älsklingsgrabben\n\n"
#define SENTENCE4 "Det är bra här i kolonien\n\n"
#define SENTENCE5 "Vi är 28 gangstergrabbar i en stor barrack\n\n"

void main(void) {

	int input;

	//loops over the following print statement as long as user input is a number between 1 and 5
	do {

		printf("Please enter a number between 1 - 5\n\n");

		//handles user input and stores it in global variable "input"
		scanf("%d", &input);

		//if statement to return different sentences based on different user input
		if (input == 1) {
			printf(SENTENCE1);
		}
		else if (input == 2) {
			printf(SENTENCE2);
		}
		else if (input == 3) {
			printf(SENTENCE3);
		}
		else if (input == 4) {
			printf(SENTENCE4);
		}
		else if (input == 5) {
			printf(SENTENCE5);
		}

		//exits program if user input does not satisfy condition
	} while (input > 0 && input < 6);
}

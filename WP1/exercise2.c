/*

	Run program with encryption key argument
	User enters a text
	Program read text input
	Encrypt text using the encryption parameter
	Loop over letters in text, if alphabet character, then ROT13
	Return encrypted text to user
	Repeat until EOF

*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void rotate(char letter, int encryptionKey, char outputChar)
{
	int number = (int)letter;

	if (isupper(number))
	{
		outputChar = (char)((number - 65 + encryptionKey) % 26) + 65;
	}
	else if (islower(number))
	{
		outputChar = (char)((number - 97 + encryptionKey) % 26) + 97;
	}
}

//return type here???
void encrypt(char* input, int encryptionKey, char* output)
{
	for (int i = 0; i < sizeof input; i++)
	{
		//printf("%d\n", sizeof input);
		rotate(input[i], encryptionKey, output[i]);
	}
}

void main(int argc, char* argv[])
{
	int boolean = 1;
	printf("%s %s", "program started", argv[1]);

//while(boolean){

	char input[10];
	char output[1000];
	scanf_s("%s\n", input);
	int encryptionKey = atoi(argv[1]);
	encrypt(input, encryptionKey, output);
	printf("%s\n", output);
	//}
	/*for (int i = 0; i <10; i++)
		printf("%s\n", output[i]);
	*/
	
}
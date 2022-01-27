// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 1
// Exercise 5
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Library used for generating random numbers
#define MAX 100 // Defines the maximum number of the values in the table
#define MAXNUMBER 20 // Defines the maximum value of random numbers

// ------ Function declarations ----------

// This function generates a set of random numbers
// and fills the table *tab with these numbers
void create_random(int* tab);

// This function takes the *tab of random numbers
// and fills the freq array with the frequency counts for these numbers
// freq[number] will hold how many times the number occurred
// Example: if 0 occurred 7 times: freq[0] = 7
void count_frequency(int* tab, int* freq);

// This function takes the frequency count table
// and draws a histogram of the values in that frequency table
void draw_histogram(int* freq);

// ------ Function definitions ----------

// ------ Main --------------------------
// The main entry point for the program
int main(void)
{
	// Declaration of arrays with size of the array according to macros
	int table[MAX];
	int frequency[MAXNUMBER];

	create_random(table);
	count_frequency(table, frequency);
	draw_histogram(frequency);
}

// ------ create_random --------------------------
void create_random(int* tab)
{
	// Use current time as seed for random generator
	srand(time(0));

	// Iterate through the table
	for (int i = 0; i < MAX; i++)
	{
		// Generate random number between 0 - MAXNUMBER
		int aNumber = rand() % MAXNUMBER;
		// Store generated number in the table
		tab[i] = aNumber;
	}
}

// ------ count_frequency --------------------------
void count_frequency(int* tab, int* freq)
{
	// Iterate through the array of frequency setting all occurrencies at 0
	for (int i = 0; i < MAXNUMBER; i++)
	{
		freq[i] = 0;
	}
	// Iterate through the table of generated numbers
	for (int i = 0; i < MAX; i++)
	{
		// Store the number in the table at position i, temporarily
		int aNumber = tab[i];
		// Increase by 1 the content of frequency at position of the current number
		freq[aNumber] += 1;
	}
	//return freq;
}

// ------ draw_histogram --------------------------
void draw_histogram(int* freq)
{
	// Iterate through freq array
	for (int i = 0; i < MAXNUMBER; i++)
	{
		// Handles case if number has occurred at least once
		if (freq[i] > 0)
		{
			// Prints out the current number and a tab for spacing
			printf("%d\t", i);
			// Prints out one x for each occurrency of that number
			for (int j = 0; j < freq[i]; j++)
			{
				printf("%s", "x");
			}
			printf("\n");

		}
	}
}

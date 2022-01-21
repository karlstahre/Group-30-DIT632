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
int* create_random(int* tab);

// This function takes the *tab of random numbers
// and creates a table with the frequency counts for these numbers
// freq[number] will hold how many times the number occurred
// Example: if 0 occurred 7 times: freq[0] = 7
int* count_frequency(int* tab, int* freq);

// This function takes the frequency count table
// and draws a histogram of the values in that frequency table
void draw_histogram(int* freq);

// ------ Function definitions ----------

// ------ Main --------------------------
// The main entry point for the program
int main(void) {
	int table[MAX], n; // Question: what is n?
	int frequency[MAXNUMBER];
	// table = create_random(table); // Question: why doesn't this work?
	//int* tab = create_random(table);
	//int* freq = count_frequency(tab, frequency);
	draw_histogram(count_frequency(create_random(table), frequency));
}

// ------ create_random --------------------------
int* create_random(int* tab) 
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
	return tab;
}

// ------ count_frequency --------------------------
int* count_frequency(int* tab, int* freq)
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
	return freq;
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
			// Prints out histogram bar for that number
			printf("%d\t", i);
			for (int j = 0; j < freq[i]; j++)
			{
				printf("%s", "x");
			}
			printf("\n");
			
		}
	}
}

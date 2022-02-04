// (C) Maja Linder, Karl Stahre, Gianmarco Iachella group: 30 (2022)
// Work package 2
// Exercise 3
// Submission code: 960059

#include <stdio.h>
#include <string.h> // Library used for strcmp and strcpy

// define macros
// The user is prompt with different strings depending on the situation
#define INSTRUCTIONS "Choose one option: \n 1 Create a new and delete the old file \n 2 Add a new person to the file \n 3 Search for a person in the file \n 4 Print out all in the file \n 5 Exit the program \n" // The user is prompt with 5 choices to choose from
#define SEARCH "Search for a person in the file by firstname or lastname\n"
#define ENTER_DATA "Enter firstname, lastname and personal number\n"
#define INVALID "Invalid choice, choose a number from 1 to 5\n"
#define ERROR "Something went wrong\n"
#define NO_FILE "File does not exist, please create file before\n"
#define EMPTY_FILE "File is empty\n"
#define NO_MATCH "There are no persons with this name in the file\n"


// ----- Typedefs ----------------------
typedef struct {
    char firstname[20];
    char famname[20];
    char pers_number[13]; // yyyymmddnnnc
} PERSON;

// ----- Global variables ---------------
FILE *database; // Stream to the file

// ------ Function declarations ---------
PERSON input_record(void);              // Reads a person’s record
void write_new_file(PERSON *inrecord);  // Creates a file and writes the first record
void print_file(void);                  // Prints out all persons in the file
void search_by_name(char *name);        // Prints out the persons if in list
void append_file(PERSON *inrecord);     // Appends a new person to the file

// ------ Function definitions ----------

// ------ Main --------------------------
int main(void)
{
    PERSON ppost = {"Test", "Testy", "198001012323"}; // Default record
    PERSON newEntry; // Declares new person that the user can insert in the file

    int choice; // Variable that stores user input for the switch, which should be a number from 1 to 5
    char name[20]; // Variable that stores user input firstname or lastname to be able to search for a specific person

    do
    {
        // User is prompted with different choices from 1 to 5
        printf("%s", INSTRUCTIONS);
        // Scans user input for integer to choose
        scanf("%d", &choice);

        // Switch that handles 5 different options
        switch(choice) {
            case 1 :
                // The user want to create a new file and insert a dummy record
                // Function call, passes default record
                write_new_file(&ppost);
                break;
            case 2 :
                // The user wants to create a new entry in the file
                // Function call, returns a new person from user input
                newEntry = input_record();
                // Function call, passes the newly made person
                append_file(&newEntry);
                break;
            case 3 :
                // The user wants to search for a person in the file by first or last name
                // User is asked to enter firstname or lastname to search for in the file
                printf("%s", SEARCH);
                // Scans user input for firstname or lastname
                scanf("%s", &name);
                // Function call
                search_by_name(name);
                break;
            case 4 :
                // The user wants to print out the entire file
                // Function call
                print_file();
                break;
            case 5 :
                // The user wants to exit
                // Exits the program
                return 0;
            default :
                // Prints when the user provides a wrong number
                printf("%s", INVALID);
        }
        //The program continues until the user inputs a 5
    } while(choice != 5);

    return(0);
}

// ------ input_record --------------------------
PERSON input_record(void)
{
    char fname[20], lname[20], pers_nr[13]; // Variables that store user input to create a new person to insert in the file
    // User is asked to enter person data
    printf("%s", ENTER_DATA);

    // Scans user input when they provide the correct amount of variables, in this case three
    if(scanf("%s %s %s", fname, lname, pers_nr) == 3) {
        // Creates new person from user input and returns it
        PERSON newEntry;
        strcpy( newEntry.firstname, fname);
        strcpy( newEntry.famname, lname);
        strcpy( newEntry.pers_number, pers_nr);
        // Returns the new person
        return newEntry;
    } else {
        // Prints error message when the user doesn't provide the correct amount of variables
        printf("%s", ERROR);
    }
}

// ------ write_new_file ------------------------
void write_new_file(PERSON *inrecord)
{
    // Opens database file in mode wb, which truncuates the file if there is existing data
    // or creates a new binary file
    database = fopen("database.bin", "wb");

    // Checks if the file exists
    if (database == NULL)
    {
        // Prints if file cannot open
        printf("%s", ERROR);
    }
    else
    {
        // Creates a new record in the file
        fwrite(inrecord, sizeof(PERSON), 1, database);
    }
    // Closes file
    fclose(database);
}

// ------ print_file ----------------------------
void print_file(void)
{
    // Opens binary file in read mode
    database = fopen ("database.bin", "rb");

    // Checks if the file exists
    if (database == NULL)
    {
        // Prints if file cannot open
        printf("%s", ERROR);
    }
    else
    {
        // Checks if file is empty
        fseek(database, 0, SEEK_END); // Set position to the end of the file
        int size = ftell(database); // ftell contains current value of the file position
        // Handles case if file is empty, if ftell is 0 it means that the file is empty
        if (size == 0) {
            printf("%s", EMPTY_FILE);
        }
        // Handles case if there is data in the file
        else
        {
            fseek(database, 0, SEEK_SET); // Set position to the beginning of the file
            PERSON ppost;
            // Reads all records and prints them
            while(fread(&ppost, sizeof(PERSON), 1, database))
            {
                printf ("%s %s %s\n", ppost.pers_number,
                        ppost.firstname, ppost.famname);
            }
        }
    }
    // Closes file
    fclose(database);
}

// ------ search_by_name -------------------
void search_by_name(char *name)
{
    // Opens binary file in read mode
    database = fopen ("database.bin", "rb");

    // Checks if the file exists
    if (database == NULL)
    {
        // Prints if file cannot open
        printf("%s", ERROR);
    }
    else
    {
        int record = 0; // Initializes variable to store how many records were found in the file

        // Checks if file is empty
        fseek(database, 0, SEEK_END); // Set position to the end of the file
        int size = ftell(database); // ftell contains current value of the file position
        // Handles case if file is empty, if ftell is 0 it means that the file is empty
        if (size == 0) {
            printf("%s", EMPTY_FILE);
        }
        else
        {
            fseek(database, 0, SEEK_SET); // Set position to the beginning of the file
            PERSON ppost;
            // Reads all records
            while(fread(&ppost, sizeof(PERSON), 1, database))
            {
                // Handles case when firstname or lastname in the file matches the user input
                if(strcmp(ppost.firstname,name)==0 || strcmp(ppost.famname,name)==0)
                {
                    // Prints all records that match the condition
                    printf ("%s %s %s\n", ppost.pers_number,
                            ppost.firstname, ppost.famname);
                    record ++; // Increases variable record
                }
            }
            // Handles case when no records where found with the condition and the user is prompt with a no match message
            if (record == 0)
            {
                printf("%s", NO_MATCH);
            }
        }
    }
    // Closes file
    fclose(database);
}

// ------ append_file ---------------------------
void append_file(PERSON *inrecord)
{
    // Opens binary file in append mode to add record at the end of the file
    database = fopen("database.bin", "ab");

    // Checks if the file exists
    if (database == NULL)
    {
        printf("%s", NO_FILE);
    }
    else
    {
        // Writes record
        fwrite(inrecord, sizeof(PERSON), 1, database);

        // Closes file
        fclose(database);
    }
}

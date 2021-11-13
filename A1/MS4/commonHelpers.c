/*
	==================================================
	Assignment #1 (Milestone #4):
	==================================================
	Name   : Zander Maitland
	ID     : 112303219
	Email  : zmaitland@myseneca.ca
	Section: NCC
*/

// Macros
#define _CRT_SECURE_NO_WARNINGS

// Library Imports
#include <stdio.h>
#include <time.h>
#include "commonHelpers.h"

// Uses the time.h library to obtain current year information
// Get the current 4-digit year from the system
int currentYear(void){
    time_t currentTime = time(NULL);
    return localtime(&currentTime) -> tm_year + 1900;
}

// As demonstrated in the course notes: https://ict.senecacollege.ca//~ipc144/pages/content/formi.html#buf
// Empty the standard input buffer
void clearStandardInputBuffer(void)
{
    while (getchar() != '\n') {
        // On purpose: do nothing
    }
}

// Get an integer value from the keyboard.
int getInteger (void)
{
    // Variable Declarations
    int intVal;
    char charVal;
    int correct = 0; // Used for keeping track of validation.

    // Begin validation loop
    while (!correct) {
        scanf("%d%c", &intVal, &charVal); // Get the user's input

        // Check if a valid integer was received (newline check)
        if (charVal == '\n') {
            correct = 1; // A valid integer was received, end the loop.
        } else {
            // An invalid value was received.
            clearStandardInputBuffer();  // Clear the input buffer to prevent issues.
            printf("ERROR: Value must be an integer: ");  // Show error
            correct = 0;  // The loop continues.
        }
    }

    return intVal; // Valid value has been reached, return the value.
}

// Get a positive integer value from the keyboard.
int getPositiveInteger (void)
{
    // Variable Declarations
    int intVal;
    int correct = 0; // Used for keeping track of validation

    // Begin validation loop
    while (!correct) {
        intVal = getInteger(); // Get the user's input as an integer

        // Check if the integer is positive.
        if (intVal > 0) {
            correct = 1; // A positive integer was received, end the loop.
        } else {
            // An invalid value was received.
            printf("ERROR: Value must be a positive integer greater than zero: ");  // Show error
            correct = 0;  // The loop continues.
        }
    }

    return intVal; // Valid value has been reached, return the value.
}

// Get a double (long float) value from the keyboard.
double getDouble (void)
{
    // Variable Declarations
    double doubleVal;
    char charVal;
    int correct = 0; // Used for keeping track of validation.

    // Begin validation loop
    while (!correct) {
        scanf("%lf%c", &doubleVal, &charVal); // Get the user's input

        // Check if a valid double (long float) was received (newline check)
        if (charVal == '\n') {
            correct = 1; // A valid double was received, end the loop.
        } else {
            // An invalid value was received.
            clearStandardInputBuffer();  // Clear the input buffer to prevent issues.
            printf("ERROR: Value must be a double floating-point number: ");  // Show error
            correct = 0;  // The loop continues.
        }
    }

    return doubleVal; // Valid value has been reached, return the value.
}

// Get a positive double (long float) value from the keyboard.
double getPositiveDouble (void)
{
    // Variable Declarations
    double doubleVal;
    int correct = 0; // Used for keeping track of validation

    // Begin validation loop
    while (!correct) {
        doubleVal = getDouble(); // Get the user's input as a double (long float)

        // Check if the double is positive.
        if (doubleVal > 0) {
            correct = 1; // A positive double was received, end the loop.
        } else {
            // An invalid value was received.
            printf("ERROR: Value must be a positive double floating-point number: ");  // Show error
            correct = 0;  // The loop continues.
        }
    }

    return doubleVal; // Valid value has been reached, return the value.
}

// Get an integer within a certain range.
// low  - lower limit of range
// high - upper limit of range
int getIntFromRange (int low, int high)
{
    // Variable Declarations
    int intVal;
    int correct = 0; // Used for keeping track of validation

    // Begin validation loop.
    while (!correct) {
        intVal = getInteger(); // Get the user's input as an integer

        // Check if the integer is within the range.
        if ((intVal >= low) && (intVal <= high)) {
            correct = 1;  // A correct value was received, end the loop.
        } else {
            // An invalid value was received.
            printf("ERROR: Value must be between %d and %d inclusive: ", low, high); // Show error
            correct = 0;  // The loop continues.
        }
    }

    return intVal; // Valid value has been reached, return the value.
}

// Get a single character, validated.
// validChars - valid character options
char getCharOption (const char* validChars)
{
    // Variable Declarations
    char charVal;
    char charCheckVal;
    int correct = 0; // Used for keeping track of validation

    // Begin validation loop.
    while (!correct) {
        scanf("%c%c", &charVal, &charCheckVal); // Get the user's input

        if (charCheckVal == '\n') {
            // The value entered was a single character. Now check if it matches validChars
            int i; // Declared outside of loop for backwards-compatibility with older versions of C.
            for (i = 0; (validChars[i] != '\0'); i++) {
                // Iterate through all validChars until null terminator is reached.
                if (charVal == validChars[i]) {
                    // The given character is a member of validChars. End loop.
                    correct = 1;
                }
            }

            // Return an error if the value provided was not found in validChars.
            if (correct != 1) {
                printf("ERROR: Character must be one of [%s]: ", validChars);

                correct = 0; // Continue loop
            }
        } else {
            // An invalid value was received.
            clearStandardInputBuffer();  // Clear the input buffer to prevent issues.
            printf("ERROR: Character must be one of [%s]: ", validChars);  // Show error
            correct = 0;  // The loop continues.
        }
    }

    return charVal; // Valid value has been reached, return the value.
}

// Get a C-string value from the keyboard (char array null-terminated).
// stringVar - pointer to string variable
// minChars  - minimum string length
// maxChars  - maximum string length
void getCString (char *stringVar, int minChars, int maxChars)
{
    // Variable Declarations
    char string[61];
    int correct = 0; // Used for keeping track of validation

    // Begin validation loop
    while (!correct) {
        scanf("%60[^\n]", string);

        int strLength;
        for (strLength = 0; string[strLength] != '\0'; strLength++);

        // Validate response
        if ((strLength >= minChars) && (strLength <= maxChars)) {
            // Input is the valid length. Return the string length.
            int i;
            for (i = 0; i < strLength; i++) {
                stringVar[i] = string[i];
            }
            stringVar[i] = '\0'; // Add null pointer to end of string.
            clearStandardInputBuffer();  // Clear the input buffer to prevent issues.
            correct = 1;
        } else if (minChars == maxChars) {
            // The length is not correct and must match an exact length.
            clearStandardInputBuffer();  // Clear the input buffer to prevent issues.
            printf("ERROR: String length must be exactly %d chars: ", minChars);
            correct = 0;
        } else if (strLength > maxChars) {
            // The length surpasses maxChars.
            clearStandardInputBuffer();  // Clear the input buffer to prevent issues.
            printf("ERROR: String length must be no more than %d chars: ", maxChars);
            correct = 0;
        } else {
            // The length is not valid.
            clearStandardInputBuffer();  // Clear the input buffer to prevent issues.
            printf("ERROR: String length must be between %d and %d chars: ", minChars, maxChars);
            correct = 0;
        }
    }
}
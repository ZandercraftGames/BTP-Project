/*
	==================================================
	Assignment #2 (Milestone #1):
	==================================================
	Name   : Zander Maitland
	ID     : 112303219
	Email  : zmaitland@myseneca.ca
	Section: NCC
*/

#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

// Get the current 4-digit year.
int currentYear (void);

// Clear anything remaining in the stdin buffer.
void clearStandardInputBuffer (void);

// Get an integer value from the keyboard.
int getInteger (void);

// Get a positive integer value from the keyboard.
int getPositiveInteger (void);

// Get a double (long float) value from the keyboard.
double getDouble (void);

// Get a positive double (long float) value from the keyboard.
double getPositiveDouble (void);

// Get an integer within a certain range.
// low  - lower limit of range
// high - upper limit of range
int getIntFromRange (int low, int high);

// Get a single character, validated.
// validChars - valid character options
char getCharOption (const char* validChars);

// Get a C-string value from the keyboard (char array null-terminated).
// stringVar - pointer to string variable
// minChars  - minimum string length
// maxChars  - maximum string length
void getCString (char *stringVar, int minChars, int maxChars);

// Convert a C-string to uppercase.
// stringVar - pointer to string variable
void strToUpper (char *stringVar);

#endif // !COMMON_HELPERS_H_

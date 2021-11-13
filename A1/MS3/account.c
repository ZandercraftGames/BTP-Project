/*
	==================================================
	Assignment #1 (Milestone #3):
	==================================================
	Name   : Zander Maitland
	ID     : 112303219
	Email  : zmaitland@myseneca.ca
	Section: NCC
*/

// Library Imports
#include <stdio.h>
#include "commonHelpers.h"
#include "account.h"

// Global Variable Declarations
const int min_age = 18;           // Minimum age to open an account
const int max_age = 110;          // Maximum age to open an account

// Get the details of an account from the user.
void getAccount (struct Account *account)
{
    // Print Information header
    printf("Account Data: New Record\n"
           "----------------------------------------\n");

    // Prompt for account number
    printf("Enter the account number: ");
    account->ID = getInteger();  // Get the user's input and set it to the account ID

    // Prompt for account type
    printf("Enter the account type (A=Agent | C=Customer): ");
    account->type = getCharOption("AC"); // Get the user's input and set it to the account type

    printf("\n"); // newline
}

// Get the details of a person from the user.
void getPerson (struct Person *person)
{
    // Print Information Header
    printf("Person Data Input\n"
    "----------------------------------------\n");

    // Prompt for full name
    printf("Enter the person's full name (30 chars max): ");
    getCString(person->fullName, 1, 30);  // Get the user's input and store the data.

    // Prompt for birth year
    printf("Enter birth year (current age must be between %d and %d): ", min_age, max_age);
    person->birthYear = getIntFromRange((currentYear() - max_age), (currentYear() - min_age));  // Get year in range of age.

    // Prompt for household income
    printf("Enter the household Income: $");
    person->householdIncome = getPositiveDouble();  // Get the user's input and store the data.

    // Prompt for the country of residence
    printf("Enter the country (30 chars max.): ");
    getCString(person->country, 1, 30);

    printf("\n"); // newline
}

// Get an account's login details from the user.
void getUserLogin (struct UserLogin *login)
{
    // Print Information Header
    printf("User Login Data Input\n"
           "----------------------------------------\n");

    // Prompt for username
    printf("Enter user login (10 chars max): ");
    getCString(login->username, 1, 10); // Get the user's input and store the data.

    // Prompt for password
    printf("Enter the password (must be 8 chars in length): ");
    getCString(login->password, 8, 8);

    printf("\n"); // newline
}

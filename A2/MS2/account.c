/*
	==================================================
	Assignment #2 (Milestone #2):
	==================================================
	Name   : Zander Maitland
	ID     : 112303219
	Email  : zmaitland@myseneca.ca
	Section: NCC
*/

#define _CRT_SECURE_NO_WARNINGS

// Library Imports
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "commonHelpers.h"
#include "account.h"

// Global Variable Declarations
const int min_age = 18;           // Minimum age to open an account
const int max_age = 110;          // Maximum age to open an account

// Validate a password to have a certain number of char types.
// stringVar - pointer to string to check
// digits - number of digits to validate
// upper - number of uppercase to validate
// lower - number of lowercase to validate
// symbols - number of symbols to validate
int hasValidChars(char *stringVar, int digits, int upper, int lower, int symbols) {
    // Password Validation Variables
    int correct;
    int digit = 0;
    int uppercase = 0;
    int lowercase = 0;
    int symbol = 0;
    int i;

    // Loop through characters
    for (i = 0; stringVar[i] != '\0'; i++) {
        if (isdigit(stringVar[i])) {
            digit  += 1;
        } else if (isupper(stringVar[i])) {
            uppercase += 1;
        } else if (islower(stringVar[i])) {
            lowercase += 1;
        } else {
            switch (stringVar[i]) {
                case '!': case '@': case '#': case '$': case '%': case '^': case '&': case '*':
                    symbol += 1;
                    break;
            }
        }
    }

    if (digit >= digits && uppercase >= upper && lowercase >= lower && symbol >= symbols) {
        // Value is correct
        correct = 1;
    } else {
        // Value is incorrect
        correct = 0;
        printf("%d %d %d %d\n", digit, uppercase, lowercase, symbol);
    }

    return correct;
}

// Get the details of an account from the user.
void getAccount (struct Account *account) {
    // Prompt for account type
    printf("Enter the account type (A=Agent | C=Customer): ");
    account->type = getCharOption("AC"); // Get the user's input and set it to the account type

    printf("\n"); // newline

    getPerson(&account->person);   // Call function to get user input for a new "Person"

    // Prompt for login info if agent
    if (account->type == 'A') {
        getUserLogin(&account->login);   // Call function to get user input for a new "UserLogin"
        putchar('\n'); // newline
    }

    // Confirmation
    printf("*** New account added! ***\n\n");
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
    strToUpper(person->country);  // Convert to uppercase.

    printf("\n"); // newline
}

// Get an account's login details from the user.
void getUserLogin (struct UserLogin *login)
{
    int correct = 0;
    int i;

    // Print Information Header
    printf("User Login Data Input\n"
           "----------------------------------------\n");

    // Get username (with validation to guarantee no spaces)
    while (!correct) {
        // Prompt for username
        printf("Enter user login (10 chars max): ");
        getCString(login->username, 1, 10); // Get the user's input and store the data.
        for (i = 0; login->username[i] != '\0'; i++) {
            if (isspace(login->username[i])) {
                correct = 0;
                printf("ERROR:  The user login must NOT contain whitespace characters.\n");
                break;
            } else if (i == strlen(login->username) - 1) {
                // If last char and not space, then correct.
                correct = 1;
            }
        }

    }
    correct = 0; // reset for next use

    // Get password (with validation of proper chars)
    while (!correct) {
        // Prompt for password
        printf("Enter the password (must be 8 chars in length): ");
        getCString(login->password, 8, 8);

        if (hasValidChars(login->password, 2, 2, 2, 2)) {
            correct = 1;
        } else {
            // Not correct chars. Print error and prompt again.
            printf("SECURITY: Password must contain 2 of each:\n"
                   "          Digit: 0-9\n"
                   "          UPPERCASE character\n"
                   "          lowercase character\n"
                   "          symbol character: !@#$%%^&*\n");
            correct = 0;
        }
    }
}

// Update an account's information
void updateAccount (struct Account *account)
{
    int user_choice;
    int done = 0;

    while (!done) {
        // Print header with prompt
        printf("Update Account: %d (%s)\n"
               "----------------------------------------\n"
               "1) Update account type (current value: %c)\n"
               "2) Person\n"
               "3) Login\n"
               "0) Done\n"
               "Selection: ", account->ID, account->person.fullName, account->type);
        user_choice = getIntFromRange(0, 3); // Get the user's input

        printf("\n"); // newline

        switch (user_choice) {
            case 1:
                // The user wishes to change the account type
                printf("Enter the account type (A=Agent | C=Customer): ");
                account->type = getCharOption("AC");

                if (account->type == 'A') {
                    // Prompt for login information for agent account
                    printf("\nAgent type accounts require a user login.  Please enter this information now:\n\n");
                    getUserLogin(&account->login);
                } else {
                    // Changed to customer, so clear login and password
                    strcpy(account->login.username, "");
                    strcpy(account->login.password, "");
                }
                putchar('\n'); // newline
                break;
            case 2:
                // The user wishes to update the person values
                updatePerson(&account->person);
                break;
            case 3:
                // The user wishes to update the login values
                if (account->type == 'C') {
                    // Customer account. Should not have login info
                    printf("ERROR:  Customer account types don't have user logins!\n\n");
                } else {
                    // Agent account, call update login function
                    updateUserLogin(&account->login);
                }
                break;
            case 0:
                done = 1;
        }
    }
}

// Update a person's information
void updatePerson (struct Person *person)
{
    int done = 0;
    int user_choice;

    while (!done) {
        printf("Person Update Options\n"
               "----------------------------------------\n"
               "1) Full name (current value: %s)\n"
               "2) Household Income (current value: $%.2lf)\n"
               "3) Country (current value: %s)\n"
               "0) Done\n"
               "Selection: ", person->fullName, person->householdIncome, person->country);

        user_choice = getIntFromRange(0, 3); // Get the user's input

        printf("\n"); // newline

        switch (user_choice) {
            case 1:
                // The user wishes to change the person name
                printf("Enter the person's full name (30 chars max): ");
                getCString(person->fullName, 1, 30);
                putchar('\n'); // newline
                break;
            case 2:
                // The user wishes to update the person income
                printf("Enter the household Income: $");
                person->householdIncome = getPositiveDouble();
                putchar('\n'); // newline
                break;
            case 3:
                // The user wishes to update the person country
                printf("Enter the country (30 chars max.): ");
                getCString(person->country, 1, 30);
                strToUpper(person->country);  // Convert to uppercase

                putchar('\n'); // newline
                break;
            case 0:
                done = 1;
        }
    }
}

// Update a user's login
void updateUserLogin (struct UserLogin *login)
{
    int done = 0;
    int correct = 0;
    int user_choice;

    while (!done) {
        printf("User Login: %s - Update Options\n"
               "----------------------------------------\n"
               "1) Password\n"
               "0) Done\n"
               "Selection: ", login->username);

        user_choice = getIntFromRange(0, 1); // Get the user's input

        printf("\n"); // newline

        switch (user_choice) {
            case 1:
                // The user wishes to change the password

                // Get password (with validation of proper chars)
                while (!correct) {
                    // Prompt for password
                    printf("Enter the password (must be 8 chars in length): ");
                    getCString(login->password, 8, 8);

                    if (hasValidChars(login->password, 2, 2, 2, 2)) {
                        correct = 1;
                    } else {
                        // Not correct chars. Print error and prompt again.
                        printf("SECURITY: Password must contain 2 of each:\n"
                               "          Digit: 0-9\n"
                               "          UPPERCASE character\n"
                               "          lowercase character\n"
                               "          symbol character: !@#$%%^&*\n");
                        correct = 0;
                    }
                }

                putchar('\n'); // newline
                break;
            case 0:
                done = 1;
        }
    }
}
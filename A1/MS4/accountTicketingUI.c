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
#include <string.h>
#include "commonHelpers.h"
#include "account.h"

// Display the account detail table header
void displayAccountDetailHeader (void)
{
    // Print the table header
    printf(""
           "Acct# Acct.Type Full Name       Birth Income      Country    Login      Password\n"
           "----- --------- --------------- ----- ----------- ---------- ---------- --------\n");
}

// Display the records within the account detail table
void displayAccountDetailRecord (const struct Account *account)
{
    // Create obfuscated password variable as copy of password.
    char obf_password[9];
    strcpy(obf_password, account->login.password);

    // Iterate through, replacing every other value with an asterisk.
    int i;
    for (i = 0; i < strlen(obf_password); i++) {
        if (i % 2 == 1) {
            obf_password[i] = '*'; // Replace the value with an asterisk.
        }
    }

    // Print the account's detail record
    printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s\n",
           account->ID, (account->type == 'A') ? "AGENT" : "CUSTOMER", account->person.fullName,
           account->person.birthYear, account->person.householdIncome, account->person.country,
           account->login.username, obf_password);
}

// Pause the execution of the program
void pauseExecution (void)
{
    printf("<< ENTER key to Continue... >>");
    clearStandardInputBuffer();
    putchar('\n');
}

// Get an account's index based on its account number.
int findAccountIndexByAcctNum (int account_num, const struct Account accounts[], int max_accounts, int prompt_for_num)
{
    // Variable Declarations
    int account_num_index = -1;
    int return_value = -1; // By default, set to -1

    // Is the function supposed to prompt for the account number?
    if (prompt_for_num) {
        // get the account number from the user to search for
        printf("Enter the account#: ");
        account_num = getPositiveInteger(); // overwrite the account number to search for
    }

    // Check if account number exists in values
    int i;
    for (i = 0; i < max_accounts; i++) {
        if (account_num == accounts[i].ID) {
            // found the account number
            account_num_index = i;

        }
    }

    return account_num_index; // -1 if not found, positive if found
}

// Display all accounts in a table
void displayAllAccountDetailRecords (const struct Account accounts[], int max_accounts)
{
    // Print the header
    displayAccountDetailHeader();
    // Loop through all values
    int i;
    for (i = 0; i < max_accounts; i++) {
        // Print the record in the table
        displayAccountDetailRecord(&accounts[i]);
    }
}

// Display the login menu
int menuLogin (const struct Account accounts[], int max_accounts)
{
    // Variable Declaration
    int correct = 0;
    int loginSelection;
    char exitSelection;
    int account_num;
    int account_index;

    // Being application loop
    while (!correct) {
        // Print login menu header
        printf("==============================================\n"
               "Account Ticketing System - Login\n"
               "==============================================\n"
               "1) Login to the system\n"
               "0) Exit application\n"
               "----------------------------------------------\n"
               "\n");

        // Prompt user for selection
        printf("Selection: ");
        loginSelection = getIntFromRange(0, 1); // Get a binary value from the user.

        // Check selection for exit option
        if (loginSelection == 0) {
            // Check if the user is sure of their selection
            printf("\n"
                   "Are you sure you want to exit? ([Y]es|[N]o): ");
            exitSelection = getCharOption("yYnN");
            if (exitSelection == 'Y' || exitSelection == 'y') {
                return -1;
            } else {
                printf("\n"); // newline
                continue; // Go back to top of loop.
            }
        }

        printf("\n"); // newline

        // User selected to log in, prompt for credentials
        printf("Enter your account#: ");
        account_num = getPositiveInteger();  // Get the account number

        // Check if account number exists in values
        account_index = findAccountIndexByAcctNum(account_num, accounts, max_accounts, 0);

        // Check if the user's provided account number was found.
        if ((account_index != -1) && accounts[account_index].type == 'A') {
            correct = 1;
            return account_index;
        } else {
            // Return ERROR then continue
            printf("ERROR:  Login failed!\n\n");
            pauseExecution();
        }
        correct = 0;
    }
}

void menuAgent (struct Account accounts[], int max_accounts, const struct Account user)
{
    // Variable Declarations
    int done = 0;
    int user_choice;

    // Display the logged-in user
    printf("\n"
           "%s: %s (%d)\n", (user.type == 'A') ? "AGENT" : "CUSTOMER", user.person.fullName, user.ID);

    while (!done) {
        // Display main menu system
        printf("==============================================\n"
               "Account Ticketing System - Agent Menu\n"
               "==============================================\n"
               "1) Add a new account\n"
               "2) Modify an existing account\n"
               "3) Remove an account\n"
               "4) List accounts: detailed view\n"
               "----------------------------------------------\n"
               "0) Logout\n"
               "\n"
               "Selection: ");

        user_choice = getIntFromRange(0, 4); // Get the user's input

        printf("\n"); // newline

        switch (user_choice) {
            case 1:
                // The user wishes to add a new account

                // Find an empty index
                int i;
                for (i = 0; i < max_accounts; i++) {
                    if (accounts[i].)
                }

                getAccount();
                break;
            case 2:
                // The user wishes to modify an existing account

                break;
            case 3:
                // The user wishes to remove an account

                break;
            case 4:
                // The user wishes to list all accounts

                break;
            case 0:
                // The user wishes to log out
                done = 1;
        }
    }
}



// Entry point to application
void applicationStartup (struct Account accounts[], int num_accounts)
{
    int account_index;
    account_index = menuLogin(accounts, num_accounts);  // Call the login and get the account index of the logged-in user

    // Call main menu
    menuAgent(accounts, num_accounts, accounts[account_index]);

}


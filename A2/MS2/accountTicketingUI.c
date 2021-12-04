/*
	==================================================
	Assignment #2 (Milestone #2):
	==================================================
	Name   : Zander Maitland
	ID     : 112303219
	Email  : zmaitland@myseneca.ca
	Section: NCC
*/

// Macros
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LOGIN_ATTEMPTS 3 // The maximum amount of times someone can attempt to log in.

// Library Imports
#include <stdio.h>
#include <string.h>
#include "commonHelpers.h"
#include "account.h"
#include "ticket.h"

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
        // Print the record in the table if the account exists
        if (accounts[i].ID != 0) {
            displayAccountDetailRecord(&accounts[i]);
        }
    }
}

// Display the login menu
int menuLogin (const struct Account accounts[], int max_accounts)
{
    // Variable Declaration
    int correct = 0;
    int loginSelection;
    char exitSelection;

    // Login-related
    int attempts = MAX_LOGIN_ATTEMPTS;
    int account_num;
    int account_index;
    char login[51];
    char password[51];


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
                correct = -1;
                break;
            } else {
                printf("\n"); // newline
                continue; // Go back to top of loop.
            }
        }

        printf("\n"); // newline

        while (attempts > 0) {
            // User selected to log in, prompt for credentials
            printf("Enter the account#: ");
            account_num = getPositiveInteger();  // Get the account number
            printf("User Login        : ");
            getCString(login, 1, 50);
            printf("Password          : ");
            getCString(password, 0, 50);

            // Check if account number exists in values
            account_index = findAccountIndexByAcctNum(account_num, accounts, max_accounts, 0);

            // Check if the user's provided account number was found.
            if ((account_index != -1) && accounts[account_index].type == 'A' &&
                !strcmp(login, accounts[account_index].login.username) && !strcmp(password, accounts[account_index].login.password)
                && attempts > 0) {
                correct = account_index;
                break;
            } else {
                // Return ERROR then continue
                attempts -= 1;
                printf("INVALID user login/password combination! [attempts remaining:%d]\n\n", attempts);
            }
            correct = 0;
            if (attempts == 0) {
                // Too many login attempts.
                printf("ERROR:  Access Denied.\n"
                       "\n");
                correct = 0;
                pauseExecution();
            }
        }
        attempts = MAX_LOGIN_ATTEMPTS;
    }
    return correct;
}

void menuAgent (struct AccountTicketingData *account_data, const struct Account user)
{
    // Variable Declarations
    int done = 0;
    int user_choice;            // The choice that the user has selected in the menu
    int new_account_index = -1; // keeps track of an empty index for use in making new accounts
    int modify_account_ID;      // The account ID entered by the user when modifying an account
    int modify_account_index;   // The index of the aforementioned account id
    int remove_account_ID;      // The account ID entered by the user when removing an account
    int remove_account_index;   // The index of the aforementioned account ID
    char confirmation;          // Keeps track of answer by user for account removal confirmation
    int i;                      // Iteration variable (moved here because of an annoying compiler error)
    int highest_account_num = 0;    // Keeps track of the highest account number to allow for the addition of it automatically.
    int zero_not_found = 1;         // Keeps track of if the index of where the account array isn't populated has been found.
    int tickets_removed; // The number of tickets removed during account deletion.
    int new_ticket_index = -1; // keeps track of an empty index for use in making new tickets
    int highest_ticket_num = 0;  // Keeps track of the highest ticket number to allow for the addition of it automatically.
    int ticket_account_index;  // Used or keeping track of the account index of the new ticket.
    char ticket_account_confirmation_sel; // Used for tracking the confirmation selection by the user when making a new ticket
    int modify_ticket_num; // Used for keeping track what ticket the user wants to edit.
    int modify_ticket_index; // Used for keeping track of the index of the ticket the user wants to edit.

    putchar('\n'); // newline

    while (!done) {
        // Display the logged-in user
        printf("%s: %s (%d)\n", (user.type == 'A') ? "AGENT" : "CUSTOMER", user.person.fullName, user.ID);

        // Display main menu system
        printf("==============================================\n"
               "Account Ticketing System - Agent Menu\n"
               "==============================================\n"
               "1) Add a new account\n"
               "2) Modify an existing account\n"
               "3) Remove an account\n"
               "4) List accounts: detailed view\n"
               "----------------------------------------------\n"
               "5) List new tickets\n"
               "6) List active tickets\n"
               "7) List closed tickets\n"
               "8) Add a new ticket\n"
               "9) Manage a ticket\n"
               "----------------------------------------------\n"
               "0) Logout\n"
               "\n"
               "Selection: ");

        user_choice = getIntFromRange(0, 9); // Get the user's input

        printf("\n"); // newline
        zero_not_found = 1;  // Reset zero_not_found to 1
        switch (user_choice) {
            case 1:
                // The user wishes to add a new account
                // Find an empty index
                for (i = 0; i < account_data->ACCOUNT_MAX_SIZE; i++) {
                    // Check if record is populated by checking if account type exists and ID is 0.
                    if (account_data->accounts[i].ID == 0 && zero_not_found) {
                        new_account_index = i; // Found record, save index.
                        zero_not_found = 0;
                    }
                    if (account_data->accounts[i].ID >= highest_account_num) {
                        highest_account_num = account_data->accounts[i].ID;
                    }
                }

                // Check if a blank record was found
                if (new_account_index != -1) {
                    account_data->accounts[new_account_index].ID = highest_account_num + 1; // Set the account ID

                    printf("New Account Data (Account#:%d)\n"
                           "----------------------------------------\n", account_data->accounts[new_account_index].ID);
                    getAccount(&account_data->accounts[new_account_index]); // Make the account at the index.

                    // Pause execution after account made.
                    pauseExecution();
                } else {
                    printf("ERROR: Account listing is FULL, call ITS Support!\n");
                    putchar('\n');
                    pauseExecution();
                }
                break;
            case 2:
                // The user wishes to modify an existing account
                // Prompt user for account number
                printf("Enter the account#: ");
                modify_account_ID = getPositiveInteger();

                // Get the account with the number
                modify_account_index = findAccountIndexByAcctNum(modify_account_ID, account_data->accounts, account_data->ACCOUNT_MAX_SIZE, 0);

                putchar('\n'); // newline

                // If the number exists
                if (modify_account_index != -1) {
                    updateAccount(&account_data->accounts[modify_account_index]);
                } else {
                    printf("ERROR: This account does not exist!\n"); // NOTE: Sample output does not contain the error, so made up one.
                }

                break;
            case 3:
                // The user wishes to remove an account
                // Prompt user for account number
                printf("Enter the account#: ");
                remove_account_ID = getPositiveInteger();

                // Check if is user's ID
                if (remove_account_ID == user.ID) {
                    printf("\nERROR: You can't remove your own account!\n");
                    putchar('\n');
                } else {
                    // Get the account with the number
                    remove_account_index = findAccountIndexByAcctNum(remove_account_ID, account_data->accounts, account_data->ACCOUNT_MAX_SIZE, 0);

                    if (remove_account_index != -1) {
                        // Account exists, print table header and record
                        displayAccountDetailHeader();
                        displayAccountDetailRecord(&account_data->accounts[remove_account_index]);
                        putchar('\n'); // newline

                        // Prompt user for confirmation
                        printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
                        confirmation = getCharOption("yYnN");

                        if (confirmation == 'Y') {
                            // Remove the account by setting the ID to zero
                            account_data->accounts[remove_account_index].ID = 0;
                            tickets_removed = removeTickets(account_data, remove_account_ID);
                            putchar('\n'); // newline
                            printf("*** Account Removed! (%d ticket(s) removed) ***\n", tickets_removed);
                        }
                        putchar('\n'); // newline


                    } else {
                        printf("\nERROR: This account does not exist!\n");
                        putchar('\n'); // newline
                    }
                }
                pauseExecution();

                break;
            case 4:
                // The user wishes to list all accounts
                displayAllAccountDetailRecords(account_data->accounts, account_data->ACCOUNT_MAX_SIZE);
                putchar('\n'); // newline
                pauseExecution();
                break;
            case 5:
                // The user wishes to list all new tickets
                listTickets(account_data, 2);
                break;
            case 6:
                // The user wishes to list all open tickets
                listTickets(account_data, 1);
                break;
            case 7:
                // The user wishes to list all closed tickets
                listTickets(account_data, 0);
                break;
            case 8:
                // The user wishes to add a ticket

                // Scan for new ticket ID and index
                for (i = 0; i < account_data->TICKET_MAX_SIZE; i++) {
                    // Check if record is populated by checking if ticket exists and ID is 0.
                    if (account_data->tickets[i].UID == 0 && zero_not_found) {
                        new_ticket_index = i; // Found record, save index.
                        zero_not_found = 0;
                    }
                    if (account_data->tickets[i].UID >= highest_ticket_num) {
                        highest_ticket_num = account_data->tickets[i].UID;
                    }
                }

                // Check if a blank record was found
                if (new_ticket_index != -1) {
                    // Get the account number
                    printf("Enter the account#: ");
                    account_data->tickets[i].customer_acc_num = getPositiveInteger(); // Get the account ID from the user.

                    ticket_account_index = findAccountIndexByAcctNum(account_data->tickets[i].customer_acc_num, account_data->accounts, account_data->ACCOUNT_MAX_SIZE, 0);

                    if (account_data->accounts[ticket_account_index].type == 'C' && account_data->accounts[ticket_account_index].ID != 0) {
                        // The account is a customer and exists. Confirm customer with user.
                        putchar('\n');
                        displayAccountDetailHeader();
                        displayAccountDetailRecord(&account_data->accounts[ticket_account_index]); // Print the account details

                        // Prompt user for confirmation:
                        printf("\nAdd a new ticket for this customer? ([Y]es|[N]o): ");
                        ticket_account_confirmation_sel = getCharOption("YyNn");

                        if (ticket_account_confirmation_sel == 'Y') {
                            // The user confirms that this is the correct customer.
                            account_data->tickets[new_ticket_index].UID = highest_ticket_num + 1; // Set the account ID
                            strcpy(account_data->tickets[new_ticket_index].messages[0].display_name, account_data->accounts[ticket_account_index].person.fullName);  // Copy display name.
                            createTicket(&account_data->tickets[new_ticket_index]); // Make the account at the index.
                        } else {
                            // This is the incorrect selection.
                            putchar('\n');
                        }
                    } else if (account_data->accounts[ticket_account_index].type == 'A') {
                        // The account is an agent, agents cannot have tickets
                        printf("\nERROR: Agent accounts can't have tickets!\n\n");
                    } else {
                        printf("\nERROR: Invalid account.\n\n");
                    }
                    // Pause execution after account made.
                    pauseExecution();
                } else {
                    printf("\nERROR: Ticket listing is FULL, call ITS Support!\n");
                    putchar('\n');
                    pauseExecution();
                }
                break;
            case 9:
                // TODO: Manage a ticket function

                // Get the ticket number of the ticket the user wants to change
                printf("Enter ticket number: ");
                modify_ticket_num = getPositiveInteger();
                modify_ticket_index = findTicketIndexByUID(account_data, modify_ticket_num, 0);

                // Validate that is actual ticket.
                if (modify_ticket_index != -1 && modify_ticket_num != 0) {
                    // The ticket exists, send the user to the ticket manager.
                    manageTicket(&account_data->tickets[modify_ticket_index], user);
                } else {
                    // The ticket doesn't exist
                    printf("ERROR: Ticket not found.\n");
                }

                putchar('\n'); // newline
                pauseExecution();
                break;
            case 0:
                // The user wishes to log out
                printf("### LOGGED OUT ###\n");
                putchar('\n'); // newline
                done = 1;
        }
    }
}

// Entry point to application
void applicationStartup (struct AccountTicketingData *account_data)
{
    int account_index;
    int done = 0;

    while (!done) {
        account_index = menuLogin(account_data->accounts,
                                  account_data->ACCOUNT_MAX_SIZE);  // Call the login and get the account index of the logged-in user

        // Was a user logged in? Or did the user select to exit the program?
        if (account_index != -1) {
            // Call main menu
            menuAgent(account_data, account_data->accounts[account_index]);
            done = 0;
        } else {
            // User logged out. Terminate
            printf("\n==============================================\n"
                   "Account Ticketing System - Terminated\n"
                   "==============================================\n");
            done = 1;
        }
    }
}


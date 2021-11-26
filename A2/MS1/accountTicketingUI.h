/*
	==================================================
	Assignment #2 (Milestone #1):
	==================================================
	Name   : Zander Maitland
	ID     : 112303219
	Email  : zmaitland@myseneca.ca
	Section: NCC
*/

#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

// ===================
// Function Prototypes
// ===================

// Display the account detail table header
void displayAccountDetailHeader (void);

// Display the records within the account detail table
void displayAccountDetailRecord (const struct Account *account);

// Pause the execution of the program
void pauseExecution (void);

// Get an account's index based on its account number.
int findAccountIndexByAcctNum (int account_num, const struct Account accounts[], int max_accounts, int prompt_for_num);

// Display all accounts in a table
void displayAllAccountDetailRecords (const struct Account accounts[], int max_accounts);

// Display the login menu
int menuLogin (const struct Account accounts[], int max_accounts);

// Display the main menu
void menuAgent (struct Account accounts[], int max_accounts, const struct Account user);


// Entry point to application
void applicationStartup (struct Account accounts[], int max_accounts);

#endif // !ACCOUNT_TICKETING_UI_H_

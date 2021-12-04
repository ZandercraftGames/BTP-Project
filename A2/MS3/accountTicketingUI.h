/*
	==================================================
	Assignment #2 (Milestone #2):
	==================================================
	Name   : Zander Maitland
	ID     : 112303219
	Email  : zmaitland@myseneca.ca
	Section: NCC
*/
#include "account.h"
#include "ticket.h"

#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

// ===================
// Function Prototypes
// ===================

// Loads account data from accounts.txt into the specified Account array
int loadAccounts (struct Account *accounts, int max_account_size);

// Loads ticket data from tickets.txt into the specified Ticket array
int loadTickets (struct Ticket *tickets, int max_ticket_size);

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
void menuAgent (struct AccountTicketingData *account_data, const struct Account user);


// Entry point to application
void applicationStartup (struct AccountTicketingData *account_data);

#endif // !ACCOUNT_TICKETING_UI_H_

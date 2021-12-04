/*
	==================================================
	Assignment #2 (Milestone #3):
	==================================================
	Name   : Zander Maitland
	ID     : 112303219
	Email  : zmaitland@myseneca.ca
	Section: NCC
*/

// Macros
#define _CRT_SECURE_NO_WARNINGS

// Imports
#include <stdio.h>
#include <string.h>
#include "ticket.h"
#include "account.h"
#include "accountTicketingUI.h"
#include "commonHelpers.h"

// Get the index of a ticket from its UID.
// account_data - pointer to array of accounts and tickets
// UID - the unique ID number of the ticket
// prompt_for_num - should the system prompt for the ticket number?
int findTicketIndexByUID (struct AccountTicketingData *account_data, int UID, int prompt_for_num)
{
    // Variable Declarations
    int ticket_num_index = -1;

    // Is the function supposed to prompt for the account number?
    if (prompt_for_num) {
        // get the account number from the user to search for
        printf("Enter the ticket#: ");
        UID = getPositiveInteger(); // overwrite the account number to search for
    }

    // Check if account number exists in values
    int i;
    for (i = 0; i < account_data->TICKET_MAX_SIZE; i++) {
        if (UID == account_data->tickets[i].UID) {
            // found the ticket number
            ticket_num_index = i;
        }
    }

    return ticket_num_index; // -1 if not found, positive if found
}

// Get the details of and create a new ticket.
// ticket_data - pointer to array of ticket
void createTicket (struct Ticket *ticket_data)
{
    // Print header
    printf("\nNew Ticket (Ticket#:%06d)\n"
           "----------------------------------------\n", ticket_data->UID);

    // Get ticket subject
    printf("Enter the ticket SUBJECT (30 chars. maximum): ");
    getCString(ticket_data->subject, 1, 30);

    putchar('\n');

    // Get the initial ticket message
    printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit: \n");
    getCString(ticket_data->messages[0].message_details, 1, 150);

    // Set additional required data
    ticket_data->status = 1; // Set ticket status to open
    ticket_data->num_messages = 1; // Set the number of messages to 1
    ticket_data->messages[0].type = 'C'; // Set message type to customer

    // Print confirmation
    printf("\n*** New ticket created! ***\n\n");
}

// Delete the tickets associated with an account, returning number removed
// account_data - pointer to array of accounts and tickets
// account_num - the number of the account to remove the tickets from
int removeTickets (struct AccountTicketingData *account_data, int account_num)
{
    // Variable Declarations
    int i;
    int removed = 0; // Track amount removed

    for (i = 0; i < account_data->TICKET_MAX_SIZE; i++) {
        // Delete each ticket that matches the given account number.
        if (account_data->tickets[i].customer_acc_num == account_num) {
            account_data->tickets[i].UID = 0; // Set UID to zero to allow for data to be overwritten
            removed++;
        }
    }

    return removed;
}

// Change the details of an existing ticket
// ticket_data - pointer to ticket
void manageTicket (struct Ticket *ticket_data, struct Account logged_in_user)
{
    // Variable Declarations
    int done = 0; // Used for tracking if the menu is done.
    int selection; // Keeps track of the menu option the user selects.
    char confirmation; // Keeps track of Y/N confirmation selections.

    // Begin menu iteration
    while (!done) {
        // Print header
        printf("\n----------------------------------------\n"
               "Ticket %06d - Update Options\n"
               "----------------------------------------\n", ticket_data->UID);

        // Print Details
        printf("Status  : %s\n"
               "Subject : %s\n"
               "Acct#   : %d\n"
               "Customer: %s\n"
               "----------------------------------------\n",
               ticket_data->status ? "ACTIVE" : "CLOSED", ticket_data->subject, ticket_data->customer_acc_num,
               ticket_data->messages[0].display_name);

        // Print Options
        printf("1) Add CUSTOMER message\n"
               "2) Add AGENT message\n"
               "3) Close ticket\n"
               "4) Re-activate ticket\n"
               "0) Done\n");

        // Prompt user for selection
        printf("Selection: ");
        selection = getIntFromRange(0, 4);

        switch (selection) {
            case 1:
                // The user wants to add a customer message, check if message slots available
                if (ticket_data->num_messages <= 20) {
                    // Message slots available, prompt for message details.
                    printf("\n"
                           "Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit: \n");
                    // Save the input to the num_messages (since messages start at 0, num_messages is index of next new message)
                    getCString(ticket_data->messages[ticket_data->num_messages].message_details, 1, 150);
                    strcpy(ticket_data->messages[ticket_data->num_messages].display_name, ticket_data->messages[0].display_name); // Set the display name to the customer
                    ticket_data->messages[ticket_data->num_messages].type = 'C';

                    // Increment number of messages
                    ticket_data->num_messages++;
                } else {
                    printf("\n"
                           "ERROR: Message limit has been reached, call ITS Support!\n");
                }
                break;
            case 2:
                // The user wants to add an agent message, check if message slots available
                if (ticket_data->num_messages <= 20) {
                    // Message slots available, prompt for message details
                    printf("\n"
                           "Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit: \n");
                    // Save the input to the num_messages (since messages start at 0, num_messages is index of next new message)
                    getCString(ticket_data->messages[ticket_data->num_messages].message_details, 1, 150);
                    strcpy(ticket_data->messages[ticket_data->num_messages].display_name, logged_in_user.person.fullName); // Set the display name to the agent's name
                    ticket_data->messages[ticket_data->num_messages].type = 'A';

                    // Increment number of messages
                    ticket_data->num_messages++;
                } else {
                    printf("\n"
                           "ERROR: Message limit has been reached, call ITS Support!\n");
                }
                break;
            case 3:
                // The user wants to close the ticket, check if ticket is already closed
                if (ticket_data->status == 1) {
                    // Ticket is open, prompt for confirmation
                    printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
                    confirmation = getCharOption("YyNn");

                    // Check input
                    if (confirmation == 'Y') {
                        // User wants to close the ticket
                        ticket_data->status = 0; // set status to closed

                        printf("\n*** Ticket closed! ***\n");
                    } else {
                        // The user does not want to close the ticket. do nothing.
                    }
                } else {
                    // Ticket is already closed
                    printf("\nERROR: Ticket is already closed!\n");
                }
                break;
            case 4:
                // The user wants to reopen the ticket, check if ticket is already open
                if (ticket_data->status == 0) {
                    // Ticket is closed, prompt for confirmation
                    printf("Are you sure you want to RE-ACTIVATE this closed ticket? ([Y]es|[N]o): ");
                    confirmation = getCharOption("YyNn");

                    // Check input
                    if (confirmation == 'Y') {
                        // User wants to open the ticket
                        ticket_data->status = 1; // set status to open

                        printf("\n*** Ticket closed! ***\n");
                    } else {
                        // The user does not want to open the ticket. do nothing.
                    }
                } else {
                    // Ticket is already open
                    printf("\nERROR: Ticket is already active!\n");
                }
                break;
            case 0:
                // The user wants to exit the menu
                done = 1;
                break;
        }
    }
}

void printTicket (struct AccountTicketingData *account_data, int ticket_num)
{
    int ticket_index = findTicketIndexByUID(account_data, ticket_num, 0);
    printf("================================================================================\n"
           "%06d (%s) Re: %s\n"
           "================================================================================\n",
           ticket_num, account_data->tickets[ticket_index].status ? "ACTIVE" : "CLOSED", account_data->tickets[ticket_index].subject);

    // Print messages
    int i;
    for (i = 0; i < account_data->tickets[ticket_index].num_messages; i++) {
        printf("%s (%s):\n"
               "   %s\n\n", account_data->tickets[ticket_index].messages[i].type == 'A' ? "AGENT" : "CUSTOMER",
               account_data->tickets[ticket_index].messages[i].display_name, account_data->tickets[ticket_index].messages[i].message_details);
    }
}

// List all tickets with a specific status
// account_data - pointer to array of accounts and tickets
// ticket_status - 0 (closed), 1 (open), 2 (new)
void listTickets (struct AccountTicketingData *account_data, int ticket_status)
{
    // Variable declarations
    int i;
    int selection; // Menu selection
    int exit = 0;   // Used for checking when the user wishes to exit
    int ticket_index; // Keeps track of the index of the ticket the user has selected.
    int ticket_status_strict; // The 0 or 1 value for ticket status

    while (!exit) {
        // Display header
        printf("------ ----- --------------- ------ ------------------------------ --------\n"
               "Ticket Acct# Full Name       Status Subject                        Messages\n"
               "------ ----- --------------- ------ ------------------------------ --------\n");

        switch (ticket_status) {
            case 0:
                ticket_status_strict = 0;
                // Print all closed tickets
                for (i = 0; i < account_data->TICKET_MAX_SIZE; i++) {
                    int customer_account_index = findAccountIndexByAcctNum(account_data->tickets[i].customer_acc_num, account_data->accounts, account_data->ACCOUNT_MAX_SIZE, 0);
                    // Is UID populated and ticket status closed?
                    if (account_data->tickets[i].UID != 0 && account_data->tickets[i].status == 0) {
                        printf("%06d %-5d %-15s %-6s %-30s %5d\n", account_data->tickets[i].UID,
                               account_data->tickets[i].customer_acc_num, account_data->accounts[customer_account_index].person.fullName,
                               "CLOSED", account_data->tickets[i].subject, account_data->tickets[i].num_messages);
                    }
                }
                break;
            case 1:
                ticket_status_strict = 1;
                // Print all open tickets
                for (i = 0; i < account_data->TICKET_MAX_SIZE; i++) {
                    int customer_account_index = findAccountIndexByAcctNum(account_data->tickets[i].customer_acc_num, account_data->accounts, account_data->ACCOUNT_MAX_SIZE, 0);
                    // Is UID populated and ticket status open?
                    if (account_data->tickets[i].UID != 0 && account_data->tickets[i].status == 1) {
                        printf("%06d %-5d %-15s %-6s %-30s %5d\n", account_data->tickets[i].UID,
                               account_data->tickets[i].customer_acc_num, account_data->accounts[customer_account_index].person.fullName,
                               "ACTIVE", account_data->tickets[i].subject, account_data->tickets[i].num_messages);
                    }
                }
                break;
            case 2:
                ticket_status_strict = 1;
                // Print all new tickets (open with only 1 message)
                for (i = 0; i < account_data->TICKET_MAX_SIZE; i++) {
                    int customer_account_index = findAccountIndexByAcctNum(account_data->tickets[i].customer_acc_num, account_data->accounts, account_data->ACCOUNT_MAX_SIZE, 0);
                    // Is UID populated, status open and number of messages only one?
                    if (account_data->tickets[i].UID != 0 && account_data->tickets[i].status == 1 && account_data->tickets[i].num_messages == 1) {
                        printf("%06d %-5d %-15s %-6s %-30s %5d\n", account_data->tickets[i].UID,
                               account_data->tickets[i].customer_acc_num, account_data->accounts[customer_account_index].person.fullName,
                               "ACTIVE", account_data->tickets[i].subject, account_data->tickets[i].num_messages);
                    }
                }
                break;
        }

        // Print closing dashes
        printf("------ ----- --------------- ------ ------------------------------ --------\n\n");


        // Prompt user for ticket number
        printf("Enter the ticket number to view the messages or\n"
               "0 to return to previous menu: ");
        selection = getInteger();

        putchar('\n');

        ticket_index = findTicketIndexByUID(account_data, selection, 0);

        // Validate response
        if (selection == 0) {
            // User wishes to exit.
            exit = 1;
        } else if (ticket_index != -1 && account_data->tickets[ticket_index].status == ticket_status_strict) {
            // Ticket exists, print the ticket
            printTicket(account_data, selection);
            exit = 0;
            pauseExecution();
        } else {
            // Invalid ticket
            printf("ERROR: Invalid ticket number.\n");
            exit = 0;
            putchar('\n');
            pauseExecution();
        }
    }
}


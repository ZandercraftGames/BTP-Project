/*
	==================================================
	Assignment #2 (Milestone #2):
	==================================================
	Name   : Zander Maitland
	ID     : 112303219
	Email  : zmaitland@myseneca.ca
	Section: NCC
*/

// Imports
#include <stdio.h>
#include "ticket.h"
#include "account.h"
#include "accountTicketingUI.h"

// Get the details of and create a new ticket.
// account_data - pointer to array of accounts and tickets
// ticket_num - the number of the new ticket
void createTicket (struct AccountTicketingData *account_data, int ticket_num)
{

}

// Delete the contents of a ticket
// account_data - pointer to array of accounts and tickets
// ticket_num - the number of the new ticket
void removeTicket (struct AccountTicketingData *account_data, int ticket_num)
{

}

// Change the details of an existing ticket
// account_data - pointer to array of accounts and tickets
// ticket_num - the number of the new ticket
void manageTicket (struct AccountTicketingData *account_data, int ticket_num)
{

}

// List all tickets with a specific status
// account_data - pointer to array of accounts and tickets
// ticket_status - 0 (closed), 1 (open), 2 (new)
void listTickets (struct AccountTicketingData *account_data, int ticket_status)
{
    // Variable declarations
    int i;

    // Display header
    printf("------ ----- --------------- ------ ------------------------------ --------\n"
           "Ticket Acct# Full Name       Status Subject                        Messages\n"
           "------ ----- --------------- ------ ------------------------------ --------\n");

    switch (ticket_status) {
        case 0:
            // Print all closed tickets
            for (i = 0; i < account_data->TICKET_MAX_SIZE; i++) {
                int customer_account_index = findAccountIndexByAcctNum(account_data->tickets[i].customer_acc_num, account_data->accounts, account_data->ACCOUNT_MAX_SIZE, 0);
                // Is UID populated and ticket status closed?
                if (account_data->tickets[i].UID != 0 && account_data->tickets[i].status == 0) {
                    printf("%-6d %-5d %-15s %-6s %-30s     %d\n", account_data->tickets[i].UID,
                           account_data->tickets[i].customer_acc_num, account_data->accounts[customer_account_index].person.fullName,
                           "CLOSED", account_data->tickets[i].subject, account_data->tickets[i].num_messages);
                }
            }
            break;
        case 1:
            // Print all open tickets
            for (i = 0; i < account_data->TICKET_MAX_SIZE; i++) {
                int customer_account_index = findAccountIndexByAcctNum(account_data->tickets[i].customer_acc_num, account_data->accounts, account_data->ACCOUNT_MAX_SIZE, 0);
                // Is UID populated and ticket status open?
                if (account_data->tickets[i].UID != 0 && account_data->tickets[i].status == 1) {
                    printf("%-6d %-5d %-15s %-6s %-30s     %d\n", account_data->tickets[i].UID,
                           account_data->tickets[i].customer_acc_num, account_data->accounts[customer_account_index].person.fullName,
                           "OPEN", account_data->tickets[i].subject, account_data->tickets[i].num_messages);
                }
            }
            break;
        case 2:
            // Print all new tickets (open with only 1 message)
            for (i = 0; i < account_data->TICKET_MAX_SIZE; i++) {
                int customer_account_index = findAccountIndexByAcctNum(account_data->tickets[i].customer_acc_num, account_data->accounts, account_data->ACCOUNT_MAX_SIZE, 0);
                // Is UID populated, status open and number of messages only one?
                if (account_data->tickets[i].UID != 0 && account_data->tickets[i].status == 1 && account_data->tickets[i].num_messages == 1) {
                    printf("%-6d %-5d %-15s %-6s %-30s     %d\n", account_data->tickets[i].UID,
                           account_data->tickets[i].customer_acc_num, account_data->accounts[customer_account_index].person.fullName,
                           "OPEN", account_data->tickets[i].subject, account_data->tickets[i].num_messages);
                }
            }
            break;
    }

    // Print closing dashes
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
}


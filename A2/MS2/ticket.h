/*
	==================================================
	Assignment #2 (Milestone #2):
	==================================================
	Name   : Zander Maitland
	ID     : 112303219
	Email  : zmaitland@myseneca.ca
	Section: NCC
*/

#ifndef BTP_PROJECT_TICKET_H
#define BTP_PROJECT_TICKET_H

// =====================
// Structure Definitions
// =====================

// Message data storage type
struct Message {
    char type;                 // the account type of the author
    char display_name[31];     // customer's display name
    char message_details[151]; // details of the message

};

// Data regarding a ticket
struct Ticket {
    int UID;              // unique ticket ID
    int customer_acc_num; // customer's account number associated with ticket
    int status;           // ticket's status (0 = closed, 1 = active/open)
    char subject[31];     // ticket's subject line
    int num_messages;     // number of messages in ticket
    struct Message messages[20]; // messages associated with the ticket
};

// Contains account and ticket data, helping to more easily pass data between functions.
struct AccountTicketingData {
    struct Account* accounts;   // array of accounts
    const int ACCOUNT_MAX_SIZE; // maximum elements for account array
    struct Ticket* tickets;      // array of tickets
    const int TICKET_MAX_SIZE;  // maximum elements for ticket array
};

// Get the details of and create a new ticket.
// account_data - pointer to array of accounts and tickets
// ticket_num - the number of the new ticket
void createTicket (struct AccountTicketingData *account_data, int ticket_num);

// Delete the contents of a ticket
// account_data - pointer to array of accounts and tickets
// ticket_num - the number of the new ticket
void removeTicket (struct AccountTicketingData *account_data, int ticket_num);

// Change the details of an existing ticket
// account_data - pointer to array of accounts and tickets
// ticket_num - the number of the new ticket
void manageTicket (struct AccountTicketingData *account_data, int ticket_num);

// List all tickets with a specific status
// account_data - pointer to array of accounts and tickets
// ticket_status - 0 (closed), 1 (open), 2 (new)
void listTickets (struct AccountTicketingData *account_data, int ticket_status);

#endif //BTP_PROJECT_TICKET_H

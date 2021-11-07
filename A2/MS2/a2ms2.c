// ===================================================================================
//
//  Assignment:  2 
//  Milestone:   2
//  Description: Main
//
// +---------------------------------------------------------+
// | *** The contents of this file is NOT to be modified *** |    
// +---------------------------------------------------------+
//
// ===================================================================================

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "accountTicketingUI.h"

// -----------------------------------------------------------------------------------
// System Data Array sizes
// -----------------------------------------------------------------------------------
#define ACCOUNT_SIZE 5
#define TICKET_SIZE 20

// -----------------------------------------------------------------------------------
// Function Prototypes
// -----------------------------------------------------------------------------------
void populateAccounts(struct Account accounts[], int arrSize);
void populateTickets(struct Ticket tickets[], int arrSize);

// -----------------------------------------------------------------------------------
// Main: Entry-point to the application
// -----------------------------------------------------------------------------------
int main(void)
{
    //----------------------------------------------
    // Variables
    //----------------------------------------------
    struct Account accounts[ACCOUNT_SIZE] = { {0} };
    struct Ticket tickets[TICKET_SIZE] = { {0} };
    struct AccountTicketingData data = { accounts, ACCOUNT_SIZE, tickets, TICKET_SIZE };

    //----------------------------------------------
    // Populate the data arrays...
    //----------------------------------------------

    // setup some test accounts:
    populateAccounts(data.accounts, data.ACCOUNT_MAX_SIZE);

    // setup some test tickets:
    populateTickets(data.tickets, data.TICKET_MAX_SIZE);

    //----------------------------------------------
    // launch application logic
    //----------------------------------------------
    applicationStartup(&data);

    return 0;
}

// -----------------------------------------------------------------------------------
// Function Definitions
// -----------------------------------------------------------------------------------

void populateAccounts(struct Account accounts[], int arrSize)
{
    int i, max = arrSize < 5 ? arrSize : 5;
    struct Account tmp[5] = {
        { 30001, 'C', {"Silly Sally", 1990, 150000.10, "CANADA"}, {"", ""} },
        { 50599, 'A', {"Fred Flintstone", 1972, 2250400.22, "AFRICA"}, {"agent1", "yAb1#a@B"} },
        { 30004, 'C', {"Betty Boop", 1978, 250800.74, "INDIA"}, {"", ""} },
        { 50008, 'A', {"Will Smith", 1952, 2350600.82, "U.S.A."}, {"agentJ", "TT*&21tt"} },
        { 30020, 'C', {"Shrimpy Shrimp", 2000, 350500.35, "KOREA"}, {"", ""} }
    };

    // Copy test records
    for (i = 0; i < max; i++)
    {
        accounts[i] = tmp[i];
    }
}

void populateTickets(struct Ticket tickets[], int arrSize)
{
    int i, max = arrSize < 5 ? arrSize : 5;
    struct Ticket tmp[5] = {
        // Ticket Test Record 1
        { 60001, 30004, 1, "Frequent Disconnects", 5, 
            // Ticket messages:
            {   {'C', "Betty Boop", "Every time I go near the microwave the unit disconnects."}, 
                {'A', "Will Smith", "Don't go near the microwave."},
                {'C', "Betty Boop", "Well... that makes sense."},
                {'A', "Will Smith", "Yup! :)"},
                {'C', "Betty Boop", "Thanks - works now."}
            }
        },
        // Ticket Test Record 2
        { 80599, 30001, 1, "No power/does not turn on", 1,
            // Ticket messages:
            {   {'C', "Silly Sally", "The unit won't turn on - please help."} }
        },
        // Ticket Test Record 3
        { 80004, 30020, 1, "My head hurts!", 3,
            // Ticket messages:
            {   {'C', "Shrimpy Shrimp", "When the unit is placed on my head it hurts."},
                {'A', "Will Smith", "Don't place it on your head."},
                {'C', "Shrimpy Shrimp", "I don't understand - why not?"}
            }
        },
        // Ticket Test Record 4
        { 70533, 30004, 0, "Nothing happens...", 1,
            // Ticket messages:
            {   {'C', "Betty Boop", "Instructions state to 'say yes' to the prompts - but nothing happens."} }
        },
        // Ticket Test Record 5
        { 80020, 30020, 1, "It's broken/does not work", 5,
            // Ticket messages:
            {   {'C', "Shrimpy Shrimp", "When I took it out of the box, it's in pieces."},
                {'A', "Fred Flintstone", "You have to assemble it - read the instructions."},
                {'C', "Shrimpy Shrimp", "What are instructions?"},
                {'A', "Fred Flintstone", "Well Shrimpy, I think you just made my day - that's funny!"},
                {'C', "Shrimpy Shrimp", "Cool... but seriously what are instructions?"}
            }
        }
    };

    // Copy test records
    for (i = 0; i < max; i++)
    {
        tickets[i] = tmp[i];
    }
}

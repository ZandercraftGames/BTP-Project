// ===================================================================================
//
//  Assignment:  2 
//  Milestone:   1
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
#define ACCOUNT_SIZE 50
#define TICKET_SIZE 50

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
    // Note Ticket data will not used in Milestone 1 but this needs to be created
    // for the new type "AccountTicketingData" which will help make data more portable
    // between functions
    struct Ticket tickets[TICKET_SIZE] = { {0} };

    // New data type defined in accountTicketingUI.h to help with sending data between functions
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
    int i, max = 5 < arrSize ? 5 : arrSize;
    struct Account tmp[5] = {
        { 30001, 'C', {"Silly Sally", 1990, 150000.10, "CANADA"}, {"", ""} },
        { 50599, 'A', {"Fred Flintstone", 1972, 2250400.22, "AFRICA"}, {"agent1", "yAb1#a@B"} },
        { 30004, 'C', {"Betty Boop", 1978, 250800.74, "INDIA"}, {"", ""} },
        { 50008, 'A', {"Will Smith", 1952, 2350600.82, "U.S.A."}, {"agentJ", "TT*&21tt"} },
        { 20020, 'C', {"Shrimpy Shrimp", 2000, 350500.35, "KOREA"}, {"", ""} }
    };

    // Copy test records
    for (i = 0; i < max ; i++)
    {
        accounts[i] = tmp[i];
    }
}

// This data will not be used in Milestone 1; however, you should review the data layout
// which will help you with the construction of the new data types ("Message" and "Ticket")
void populateTickets(struct Ticket tickets[], int arrSize)
{
    int i, max = arrSize < 5 ? arrSize : 5;
    struct Ticket tmp[5] = {
        // Ticket Test Record 1
        { 60001, 30004, 1, "Frequent Disconnects", 2,
            // Ticket messages:
            {   {'C', "Betty Boop", "Every time I go near the microwave the unit disconnects."},
                {'A', "Will Smith", "Don't go near the microwave."}
            }
        },
        // Ticket Test Record 2
        { 80599, 30001, 1, "No power/does not turn on", 1,
            // Ticket messages:
            {   {'C', "Silly Sally", "The unit won't turn on - please help."} }
        },
        // Ticket Test Record 3
        { 80004, 20020, 1, "My head hurts!", 3,
            // Ticket messages:
            {   {'C', "Shrimpy Shrimp", "When the unit is placed on my head it hurts."},
                {'A', "Will Smith", "Don't place it on your head."},
                {'C', "Shrimpy Shrimp", "I don't understand - why not?"}
            }
        },
        // Ticket Test Record 4
        { 80599, 30004, 0, "Nothing happens...", 7,
            // Ticket messages:
            {   {'C', "Betty Boop", "Instructions state to 'say yes' to the prompts - but nothing happens."},
                {'A', "Fred Flintstone", "Is this when setting up the unit for the first time?"},
                {'C', "Betty Boop", "Yes - it keeps asking if I'm ready to start and I tell it 'yes' nothing happens."},
                {'A', "Fred Flintstone", "Are you pressing the 'yes' button on the unit?"},
                {'C', "Betty Boop", "No, instructions state to say yes - not press any buttons."},
                {'A', "Will Smith", "'say' was meant to be interpretted as press the 'yes' button."},
                {'C', "Betty Boop", "Oh I get it now - thanks!"}
            }
        },
        // Ticket Test Record 5
        { 80020, 20020, 1, "It's broken/does not work", 3,
            // Ticket messages:
            {   {'C', "Shrimpy Shrimp", "When I took it out of the box, it's in pieces."},
                {'A', "Fred Flintstone", "You have to assemble it - read the instructions."},
                {'C', "Shrimpy Shrimp", "What are instructions?"}
            }
        }
    };

    // Copy test records
    for (i = 0; i < max; i++)
    {
        tickets[i] = tmp[i];
    }
}

// #############################################################################################
//  Assignment: 1 
//  Milestone : 3
// #############################################################################################
//  Student Name  : Zander Maitland
//  Student ID    : 112303219
//  Student Email : zmaitland@myseneca.ca
//  Course Section: NCC
// #############################################################################################

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "account.h"
#include "accountTicketingUI.h"

// ------------------------------------------------------------------
// Main entry point to application:

int main(void)
{
    // *** NOTE: No other variables are allowed to be declared ***
    struct Account account = { 0 };                             // *** DO NOT MODIFY THIS LINE ***

    printf("Assignment 1 Milestone 3 - Tester\n");              // *** DO NOT MODIFY THIS LINE ***
    printf("=============================================\n");  // *** DO NOT MODIFY THIS LINE ***

    // ---------------------------------------------------------
    // Account Data
    // ---------------------------------------------------------
    // Input (new record)
    getAccount(&account);   // Call function to get user input for a new "Account"

    // ---------------------------------------------------------
    // Person Data
    // ---------------------------------------------------------
    // Input (new record)
    getPerson(&account.person);   // Call function to get user input for a new "Person"

    // ---------------------------------------------------------
    // UserLogin Data
    // ---------------------------------------------------------
    // Input (new record)
    getUserLogin(&account.login);   // Call function to get user input for a new "UserLogin"

    // ---------------------------------------------------------
    // Display formatted Account details
    // ---------------------------------------------------------
    displayAccountDetailHeader();         // Call function to display the account detail header
    displayAccountDetailRecord(&account);   // Call function to display an account detail record

    putchar('\n');
    printf("Account, Person, and User Login test completed!\n");  // *** DO NOT MODIFY THIS LINE ***

    return 0;       // *** DO NOT MODIFY THIS LINE ***
}

/*
	==================================================
	Assignment #1 (Milestone #3):
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


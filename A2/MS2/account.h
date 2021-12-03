/*
	==================================================
	Assignment #2 (Milestone #2):
	==================================================
	Name   : Zander Maitland
	ID     : 112303219
	Email  : zmaitland@myseneca.ca
	Section: NCC
*/

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

// =====================
// Structure Definitions
// =====================

// Personal information about a customer.
struct Person {
    char fullName[31];      // first, middle (if applicable), and surname of customer
    int birthYear;          // birth year of customer
    double householdIncome; // customer's household income
    char country[31];       // customer's country of residence
};

// Login details of a customer.
struct UserLogin {
    char username[11];      // customer's login name
    char password[9];       // customer's password
};

// Account-specific data.
struct Account {
    int ID;                 // customer's account number
    char type;              // the account's type
    struct Person person;   // person data of the customer
    struct UserLogin login; // login data of the customer
};

// ===================
// Function Prototypes
// ===================

// Get the details of an account from the user.
void getAccount (struct Account *account);

// Get the details of a person from the user.
void getPerson (struct Person *person);

// Get an account's login details from the user.
void getUserLogin (struct UserLogin *login);

// Update an account's information
void updateAccount (struct Account *account);

// Update a person's information
void updatePerson (struct Person *person);

// Update a user's login
void updateUserLogin (struct UserLogin *login);

// Validate a password to have a certain number of char types.
// stringVar - pointer to string to check
// digits - number of digits to validate
// upper - number of uppercase to validate
// lower - number of lowercase to validate
// symbols - number of symbols to validate
int hasValidChars(char *stringVar, int digits, int upper, int lower, int symbols);

#endif // !ACCOUNT_H_

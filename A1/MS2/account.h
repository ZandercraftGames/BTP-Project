/*
	==================================================
	Assignment #1 (Milestone #2):
	==================================================
	Name   : Zander Maitland
	ID     : 112303219
	Email  : zmaitland@myseneca.ca
	Section: NCC
*/

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
};
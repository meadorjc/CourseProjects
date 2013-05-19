/******************************
   Caleb Meador
   2/27/2013
   Lab1-C3-P17.cpp
   Monthly Payments
********************************/

// Headers
#include <iostream>
#include <iomanip> //include to use formatting functions
#include <cmath>  //include cmath to use power function
using namespace std;

int main()
{
    //Declare variables
    double loanAmount;           // Total value of original loan.
    double annualInterestRate;   // the annual interest rate of the loan
    double mIntRate;             // the monthly interest rate (annual interest
                                 //     rate divided by 12.
    double numPayments;          // The number of payment periods on the loan.
    double monthlyPayment;       // The dollar value of each monthly 
                                 //     period payments.
 
    // To display the program title and instructions
    cout << endl << endl;
    cout << "******Loan Information Worksheet******";
    cout << endl << endl;
    cout << "Please enter the following information: " << endl;
    cout << endl << endl;
    
    //Get amount of loan from user and assign to loanAmount
    cout << "Total Loan Amount: $";
    cin >> loanAmount; 
    
    //Get annual interst rate from user and assign to annualInterestRate
    cout << "Annual Interest Rate: %";
    cin >> annualInterestRate; 
    
    // Get number of payments and assign to numPayments
    cout << "Number of Payments: ";
    cin >> numPayments;
    cout << "----------------------------------------------" << endl << endl;
    
    // To display total loan amount in column formation with dollar sign,
    // precision of two, fixed point and showpoint format.
    cout << setw(25) << left << "Loan Amount: ";
    cout << "$" << setw(9) << right << setprecision(2) << fixed
         << showpoint << loanAmount << endl;
    
    //To Calculate monthly interest rate
    mIntRate = (annualInterestRate / 12);
    
    // To display the monthly interest rate in column format with
    // percent sign; resetioflags(ios: fixed) is to reset fixed and noshowpoint
    // used to format as per instructions.   
    cout << setw(25) << left << "Monthly Interest Rate: ";
    cout << setw(9) << right << setprecision(2) << resetiosflags(ios::fixed)
         << noshowpoint << mIntRate << "%" << endl;
         
    // To display the number of payments in column format without 
    // a decimal point or places of precision as per instructions.
    cout << setw(25) << left << "Number of Payments: ";
    cout << setw(10) << right << numPayments << endl;
    
    // Convert monthly interest rate to decimal form before calculation 
    mIntRate /= 100;     
    
    //To calculate the monthly payment:
    // [Monthly Interest Rate * (1 + Monthly Interest Rate)^ Number of payments]
    // divided by {[(1 + Monthly Interest Rate)^ Number of payments] - 1}
    // multiplied by the original loan amount.
    monthlyPayment = ((mIntRate * pow((1 + mIntRate), numPayments))
                   / (pow((1 + mIntRate), numPayments)-1)) 
                   * loanAmount; 
    
    //To display the monthly payment amount using 2 places of precision
    //fixed and showpoint notation for two decimal places.  
    cout << setw(25) << left << "Monthly Payment: ";
    cout << "$" << setw(9) << right << setprecision(2) << fixed
         << showpoint << monthlyPayment << endl;
    
    //To display total amount paid back over course of the loan
    cout << setw(25) << left << "Amount Paid Back: ";
    cout << "$" << setw(9) << right << setprecision(2) << fixed
         << showpoint << (monthlyPayment * numPayments) << endl;
    
    //To display and calculate total amount of interest paid over the loan.
    // Interest Paid is Monthly Payment times Number of Payments minus 
    // Loan Amount         
    cout << setw(25) << left << "Interest Paid: ";
    cout << "$" << setw(9) << right << setprecision(2) << fixed
         << showpoint << (monthlyPayment * numPayments) - loanAmount;
    
    // To format
    cout << endl << endl;
    
    // To Pause the system before close of program
    system("PAUSE");


    return 0;
}

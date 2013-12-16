/******************************
   Caleb Meador
   2/25/2013
   Lab1-C3-P9.cpp
   Automobile Costs
********************************/

// Headers
#include <iostream>
#include <iomanip> //include to use formatting functions
using namespace std;

int main()
{
    
    //Declare variables
    double loanPaymentCost;      // monthly cost of loan payment
    double insuranceCost;        // monthly cost of insurance
    double gasCost;              // monthly gas cost
    double oilCost;              // monthly oil cost
    double tireCost;             // monthly tire cost
    double maintainCost;         // monthly maintenance cost
    double totalCost;            // total monthly cost
  
    // Ask user for input and give directions
    cout << endl << endl << "***Monthly Expense Report***";
    cout << endl << endl << "Please enter your monthly costs below. ";
    cout << endl << endl << "***Example*** ";
    cout << endl << "Loan Payment:  21.23 [ENTER]" << endl << endl;
    
    // Pause to allow user to read the instructions
    system("Pause");
    
    // Ask user for loan payment cost and assign to variable.    
    cout << endl << left;     
    cout << setw(20) << "Loan Payment: ";
    cin >> loanPaymentCost;
    
    // Ask user for insurance cost and assign to variable.    
    cout << setw(20) << "Insurance Cost: ";
    cin >> insuranceCost;
         
    // Ask user for gas cost and assign to variable.
    cout << setw(20) << "Gas Cost: ";
    cin >> gasCost;

    // Ask user for oil cost and assign to variable.
    cout << setw(20) << "Oil Cost: ";
    cin >> oilCost;

    // Ask user for tire cost and assign to variable.
    cout << setw(20) << "Tire Cost: ";
    cin >> tireCost;

    // Ask user for maintenance cost and assign to variable.
    cout << setw(20) << "Maintenance Cost: ";
    cin >> maintainCost;
    // Formatting
    cout << endl << "------------------------------------------------";
       
    // Calculate the total costs by summing all variabls and assign to variable 
    totalCost = loanPaymentCost + insuranceCost + gasCost + oilCost + tireCost
              + maintainCost;
    
    // Format output and totalCost variable    
    cout << endl << left << setw(22) << "Total Monthly Costs:" << "$"
         << right << setw(8) << setprecision(2) << fixed << showpoint
         << totalCost;
    cout << endl << "------------------------------------------------";    
    
    // Format output and display totalCost variable multiplied by 12
    cout << endl << left << setw(22) << "Total Annual Costs:" << "$"
         << right << setw(8) << setprecision(2) << fixed << showpoint
         << totalCost * 12;
    cout << endl << "================================================";
    cout << endl << endl;
    
    
	// Pause the system before the end of the program
    system("PAUSE");


    return 0;
}

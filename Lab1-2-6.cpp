/******************************
   Caleb Meador
   2/25/2013
   Lab1-C2-P6.cpp
   Annual Pay
********************************/

// Headers
#include <iostream>
#include <iomanip> //include to use formatting functions
using namespace std;

int main()
{

    //Declare & initialize variable to hold amount of 
    //pay employee earns each pay period.
    double payAmount = 1700.0;     // amount earned each pay period
    double payPeriods = 26.;       // number of pay periods
    double annualPay;              // value of annual pay    
    
    annualPay = payAmount * payPeriods;    
    
    //To output the annual pay for the employee.
    cout << endl << endl;
    cout << "The employee's total annual pay is $";
    cout << left << setw(10) << setprecision(2) << fixed << showpoint
         << annualPay << endl << endl;




	// To pause system before ending program.
    system("PAUSE");


    return 0;
}

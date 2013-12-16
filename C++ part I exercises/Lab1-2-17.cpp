/******************************
   Caleb Meador
   2/25/2013
   Lab1-C2-P17.cpp
   Stock Commission
********************************/
// Headers
#include <iostream>
#include <iomanip> //include to use formatting functions
using namespace std;

int main()
{
          //Declare variables
        double  numberShares = 600;     // the number of shares purchased
        double  sharePrice = 21.77;     // the price of each share
        double  commission = .02;       // the commission rate, 2%
        double  sharesValue;            // to store the total share value
        double  commissionValue;        // to store the total commission value

       // Multiply numberShares by sharePrice and assign to sharesValue.
       sharesValue = numberShares * sharePrice;

       // Display sharesValue, which is the price of the total amount of shares
       cout << endl << endl;
       cout << "The total price of the shares before commission is $";
       cout << setprecision(2) << fixed << showpoint << sharesValue; 
       
       // Multiply sharesValue by commission and assign to commissionValue
       // To find the value of the commission alone.
       commissionValue = sharesValue * commission;
       
       // Display commissionValue.
       cout << endl;
       cout << "The price of commission on the shares is $";
       cout << setprecision(2) << fixed << showpoint << commissionValue;
       
       // Display the sum of sharesValue and comissionValue.
       cout << endl;
       cout << "The sum of the value of shares and commission is $";
       cout << setprecision(2) << fixed << showpoint     
            << sharesValue + commissionValue;           
       cout << endl << endl;
       
       
    	// To pause the system before ending the program.
        system("PAUSE");


        return 0;
}

/******************************
   Caleb Meador
   2/25/2013
   Lab1-C3-P14.cpp
   Senior Citizen Property Tax
********************************/

// Headers
#include <iostream>
#include <iomanip> //include to use formatting functions
using namespace std;

int main()
{
        //Declare variables
       double propertyValue;                // Actual property value
       double taxRate100;                   // Tax rate per 100 dollars
       double assessValue;                  // Assessed value of property
       double taxableValue;                 // Taxable value of property
       double annualPropTax;                // Annual property tax
       const double ASSESS_RATE = .6;       // Constant, assess rate of property
                                            // value is 60%
       const double SENIOR_EXEMPT = 5000;   // Constant, Senior Exemption.
       
       // Display text asking user for actual property value.
       cout << endl << endl
            << "******Senior Citizen Property Tax Worksheet******";
       cout << endl << endl;
       cout << "Please input the following dollar amounts." << endl << endl;
       cout << setw(24) << left << "Actual Property Value: $" << setw(6);
       
       // Get value of actual property value and assign to propertyValue.
       cin >> propertyValue;
            
       // Display text asking user for tax rate per 100 dollars of assessed 
       // property value.
       
       cout << setw(19) << left << "Tax Rate per $100: " << right 
       << "$" << setw(6);
       
       // Get value of tax rate and assign to taxRate100.
       cin >> taxRate100;
       
       cout << endl << "---------------------------------------------------";
       
       //Multiply propertyValue by ASSESS_RATE and assign to assessValue.
       assessValue = propertyValue * ASSESS_RATE;
       
       //Display assessValue.
       cout << endl << setw(35) << left << "Assessment Value (60% of Actual):" 
            << setw(6) << right << "$" << setw(8);
       cout << setprecision(2) << fixed << showpoint << assessValue;
       
       
       
       //Subtract SENIOR_EXEMPT from assessValue and assign to taxableValue.
       taxableValue = assessValue - SENIOR_EXEMPT;
       
       // Test taxableValue for being negative. If negative, set to 0 to avoid 
       // a negative tax bill.
       if (taxableValue < 0)
       {       
               taxableValue = 0;
       }
       
       //Display senior exemption on screen.
       cout << endl << setw(35) << left << "Less: Senior Exemption:"
            << setw(6) << right << "$" << setw(8)
            << SENIOR_EXEMPT;
       cout << endl << "---------------------------------------------------";
      
       // Display taxable value of property.
       cout << endl << setw(35) << left << "Taxable Value:" 
            << setw(6) << right << "$" << setw(8)
            <<  setprecision(2) << fixed << showpoint << taxableValue;
       cout << endl << "===================================================";
       cout << endl; 
       
       // Multiply taxableValue by taxRate100 and assign to annualPropTax.
       // Note that because taxRate100 is entered as a dollar amount, it must
       // be divided by 100 to convert it to a fractional number for calculation
       annualPropTax = taxableValue * (taxRate100 / 100); 
       
       // Display annualPropTax.
       cout << endl << setw(35) << left << "Annual Property Tax:" 
            << setw(6) << right << "$" << setw(8)
            << setprecision(2) << fixed << showpoint << annualPropTax;
       
       // Divide annualPropTax by 4 to find the quarterly tax bill 
       // and display as Quarterly Tax Bill
       cout << endl << setw(35) << left << "Quarterly Tax Bill:" 
            << setw(6) << right << "$" << setw(8)
            <<  setprecision(2) << fixed << showpoint << annualPropTax / 4;
       cout << endl << endl;
       

	   // This pauses the system before continuing 
       system("PAUSE");


       return 0;
}

/******************************
   Caleb Meador
   4/2/2013
   L2-5-26.cpp
   Savings Account Balance sheet
********************************/


#include <iostream> 	
#include <iomanip>
#include <fstream>     // to get info from file.
#include  <string>       // to use strings 
using namespace std;

int main()
{
    //Declare and initialize 
    double apr = -1, acctBal = -1, begBal = -1;
    double deposits, withdrawals, interest; 
    double totalDeposits = 0, totalWithdrawals = 0, 
           totalInterest = 0, endBal;
    int monthsPassed = -1, x;
    
    //Declare outFile to output to file
    ofstream outFile;
    
    //Open text file to write to.
    outFile.open("savings.txt");
    
    //Output title and prompt for APR
    cout << "Savings Account Balance Sheet";
    outFile << "Savings Account Balance Sheet";
    cout << endl << "Enter the APR for the savings account: ";
    outFile << endl << "APR for the savings account: ";
    
    //Input validation for APR
    while (apr < 0)
    {
          cin >> apr;
    
        if (apr < 0)
        cout << endl << "Please input a valid APR: ";
    }
    
    //Write APR to file
    outFile << apr << "%";
    
    //Prompt for stating balance
    cout <<  "Enter the starting balance: ";
    outFile << "\nStarting Balance: " ;
    
    //Input validation for starting balance
    while (begBal < 0)
    {
          cin >> begBal;
          
          if (begBal < 0)
          cout << endl << "Please input a valid starting balance: ";
    }
    
    //Write starting balance to file
    outFile << begBal;
    
    //Prompt for the number of months to update
    cout <<  "Enter the number of months to update: ";
    outFile << "\nNumber of months to update: ";
    
    //Months to update validation
    while (monthsPassed < 0)
    {
          cin >> monthsPassed;
          
          if (monthsPassed < 0)
          cout << endl << "Please input a valid number of months: ";
    }
    
    
    //Output months passed to file
    outFile << monthsPassed;
    
    
    //Prime acctBal using begBal
    acctBal = begBal;
    
    //Display number of months to be updated.
    cout << "\n\nMonths on this Balance Sheet: " << monthsPassed;
    outFile << "\n\nMonths on this Balance Sheet: " << monthsPassed;
 
    cout << "\n************************************************\n";
    outFile << "\n************************************************\n";
  
    //Increment loop by 1 for each pass while less or equal to monthsPassed val.
    for (x = 1; x <= monthsPassed; ++x)
    {
        //prompt for deposits
        cout << "\nMonth " << x;
        cout << "\n******\n";
        cout << "Deposits:      $";
        
        //file output
        outFile << "\nMonth " << x;
        outFile << "\n******\n";
        outFile << "Deposits:      $";
        
        //reset deposits and withdrawals for each loop pass
        deposits = -1;
        withdrawals = -1;
        
        //validate input for deposits
        while (deposits < 0)
        {
              //get user input and assign to deposits
              cin >> deposits;
              
              if(deposits < 0)
              {
                     cout << "\nPlease enter a valid deposit amount: $";
        
              }   
        }
        
        //Output to file
        outFile << deposits << endl;
        
        //Prompt for withdrawals
        cout << "Withdrawals:   $";
        outFile << "Withdrawals:   $";
        
        //withdrawls input validation  
        while (withdrawals < 0)
        {
              //assign user input to withdrawals
              cin >> withdrawals;
              
              if(withdrawals < 0)
              {
                    cout << "\nPlease enter a valid withdrawal amount: $";
              }
        }
        //output withdrawals to file
        outFile << withdrawals << endl;
        
        //To update account balance
        acctBal = acctBal + deposits - withdrawals;
        
        //Calculate the monthly interest amount
        interest = (( apr / 12) / 100) * acctBal;
        
        //Interest calculation validation: cannot be less than 0
        if (interest >= 0)
        {
           //Output interest amount
           cout << "Interest:           $" << fixed << right << setprecision(2)
           << setw(8) << interest << endl;
        
           outFile << "Interest:           $" << fixed << right 
                   << setprecision(2) << setw(8) << interest << endl;
        }
        // Account closure in case of negative value.
        else 
        {  cout << "\n********************************************************";
           cout << "\nAccount cannot hold a negative number. " 
                << "The account has been closed."
                << "\n********************************************************";
           //Break out of loop
           break;  
        }
        
        //To update account balance again
        acctBal += interest;
        
        //Acct balance calculation validation: cannot be less than 0
        if (acctBal >= 0)
        {
          cout << "Ending Balance:     $" << fixed << right << setprecision(2)
               << setw(8) << acctBal << endl; 
          cout << "\n****************************************************\n\n";

          outFile << "Ending Balance:     $" << fixed << right 
                  << setprecision(2) << setw(8) << acctBal << endl; 
          outFile << "\n*************************************************\n\n";

        }
        //Account closure in case of neg. value
        else 
        {  cout << "\n********************************************************";
           cout << "\nAccount cannot hold a negative number. " 
                << "The account has been closed."
                << "********************************************************";
           //break out of loop 
           break;  
        }
        
        //To update total deposits
        totalDeposits += deposits;
        
        //To update total withdrawals
        totalWithdrawals += withdrawals;
        
        //To update total interest earned
        totalInterest += interest;
    }
    //Total summary value data validation: account closure if < 0
    if ( (monthsPassed >= 0) && (begBal >= 0) && (totalDeposits >= 0)
    && (totalWithdrawals >= 0) && (totalInterest >= 0) && (acctBal >= 0))
    {
        cout << "\nActivity for " << monthsPassed << " months.";
        cout << "\nStarting Balance:  $ " << right << setw(8) << begBal;
        cout << "\nTotal Deposits:    $ " << right << setw(8) << totalDeposits;
        cout << "\nTotal Withdrawals: $ " << right << setw(8) << totalWithdrawals;
        cout << "\nTotal Interest:    $ " << right << setw(8) << totalInterest;
        cout << "\nEnding Balance :   $ " << right << setw(8) << acctBal; 
    
        outFile << "\nActivity for " << monthsPassed << " months.";
        outFile << "\nStarting Balance:  $ " << right << setw(8) << begBal;
        outFile << "\nTotal Deposits:    $ " << right << setw(8) << totalDeposits;
        outFile << "\nTotal Withdrawals: $ " << right << setw(8) << totalWithdrawals;
        outFile << "\nTotal Interest:    $ " << right << setw(8) << totalInterest;
        outFile << "\nEnding Balance :   $ " << right << setw(8) << acctBal; 
    }
    else
        cout << "\n\nAccount is now closed.\n\n";
    
    //Close output file
    outFile.close();
    
    cout << endl << endl;
      
    system("Pause");
	
    return 0;
}


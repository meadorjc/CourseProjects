/******************************
   Caleb Meador
   4/2/2013
   L2-5-21.cpp
   Random Number Guessing Game Enhancement
********************************/


#include <iostream> 	
#include <iomanip>     // to manipulate ouput
#include <cstdlib>     // to get a random number
#include  <ctime>       // to get time 
using namespace std;

int main()
{
    int guess = -1, guessCount = 0, var1;
      
    //to seed random number generator
    srand(time(0));
    
    //generate random number
    var1 = (rand() % 10) + 1;
  
    
    //Display welcome message.
    cout << "Guess the random number between 1 and 10!" << endl;
    cout << "Your guess: ";    
    
    
    while (guess != var1)
    {    
        cin >> guess;
        
        ++guessCount;
        
        //Test user-input to see if higher than random number.
        if (guess > var1)
        {
                  cout << "\nYour guess is too high. Try again! ";
        
        }
        //Otherwise, test to see if lower than the random number
        else if (guess < var1)
        {
             cout << "\nYour guess it too low. Try again! ";
        }
     
     }  
     // Output congratulatory message and display correct number.        
     cout << "\nCongratulations! The correct number was " << var1 << ".";
     
     // Output the number of times it took the user to guess the number. 
     cout << "\nIt took " << guessCount; 
     
     // If count is greater than one, output guesses.
     (guessCount > 1) ? cout << " guesses" : cout << " guess";
     cout << " to find the correct number.";
        
    
      cout << endl << endl;
      
      system("Pause");
	
    return 0;
}


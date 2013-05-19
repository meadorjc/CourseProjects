/**************************
    Caleb Meador
    COSC 1436
    4/23/2013
    L3-6-23
    Rock, Paper, Scissors Game
***************************/

#include <iostream>
#include <cstdlib> //included for time() & rand number generation
#include <cstring> //to output computer and player choices
using namespace std;

// Function prototype for computerChoice; used to determine computer's choice 
// between rock, scissors, paper, chosen as 1, 2, or 3.
// Parameter: integer variable, number, will pass the value from main.
int computerChoice(); 

// Function Prototype for playerChoice; accepts the player's choice
// between rock, scissors, and paper, chosen as 1, 2, or 3.
// Parameter: integer variable, 
int playerChoice();

// Function Prototype for winEngine; used to determine the winner of the game.
// Rock beats scissors. Scissors beats paper. Paper beats rock. Equal choices
// must play a 2nd game.
void winEngine(int pChoice, int cChoice);

//Function prototype for choiceDisplay; used to determine the output string of 
// the player and computer chocies. 1 outputs rock, 2 outputs scissors, 3
// outputs paper.  The integer passes the integer pChoice to the function 
// choiceDisplay when called, and returns a string.
string choiceDisplay(int pChoice);

//Function prototype for playAgain(), which is used to display a menu, process 
// a user's input and output concerning the option to play again.
// When called, the function displays a message and returns an integer value
// which is tested in int main().
int playAgain();


const int CHOICE_MAX = 4;  //3 game choices, and 1 option to quit.
const int COMP_CHOICE_MAX = 3; //Computer may choose 3 game choices; can't quit.
const int CHOICE_MIN = 1;       //The user must choices start from 1.


int main()
{
    //Declare integer value pChoice and cChoice to pass between functions.
    // pChoice is initialized to 0 in order determine when to quit program.
    int pChoice = 0, cChoice;
    
    cout << "********* Welcome to Rock, Scissors, Paper *********\n"
         << "----------------------------------------------------\n";
    
    
    //While-loop tests to see if pChoice is NOT equal to -1, which is a sentinal
    // for quitting. 
    while (pChoice != -1)
    {
        //Call computerChoice to get a random number and assign it to cChoice.
        cChoice = computerChoice();
                
        //Call playerChoice to get the user's game options and assign it to 
        // pChoice.
        pChoice = playerChoice();
        
        
        //If-statement tests pChoice; if greater than 0, proceed with game.
        if (pChoice > 0)
        {        
            //Call winEngine function passing pChoice and cChoice to the
            // the function to determine the winner or loser and appropriate
            // display message.
            winEngine(pChoice, cChoice); 
        
        
            // After winEngine runs, playAgain is called to allow the user the 
            // option to playAgain. The value of the user's choice is assigned
            // to pChoice to test that its not -1.
            pChoice = playAgain();
        }
        
        //If pChoice is not greater than 0, then output goodbye message, as 
        // program ends.
        else
            cout << "Thank you for playing! Goodbye!\n\n";
    }
    
    
    
    //Pause system before ending program.
    system("PAUSE");
    
    return 0;
}

// Function definition for computerChoice; used to determine computer's choice 
// between rock, scissors, paper, chosen as 1, 2, or 3.
// Parameter: integer variable, number, will pass the value from main.
int computerChoice()
{
    srand(time(NULL));     //seeds random number
    
    return rand() % COMP_CHOICE_MAX + 1; //rand modulus max chooses a number
                                         //between 0 and 2, plus one for (1-3)
}    
    
// Function definition for playerChoice ; used to process input and output
// of the player's menu choices.

int playerChoice()
{
    //Prime variable choice, initialized to 0. This holds the player's input.
    int choice = 0;
    
    // Use a while loop to validate input; if input is less than CHOICE_MIN
    // or greater than CHOICE_MAX then continue to display menu.   
    while (choice < CHOICE_MIN || choice > CHOICE_MAX)
    {
        
        //Output the options for the player
        cout << "\n\nPlease select from the following choices:\n"
         << "\t1. Rock\n"
         << "\t2. Scissors\n"
         << "\t3. Paper\n\t-or-"
         << "\n\t4. Quit\n";       
        
        // Assign the players choice to variable choice.
        cin >> choice;
          
        
        // Test the input to see if they want to quit and return -1 to
        // int main(), where -1 quits the program.
        if (choice == 4)
            return -1;
        
        //Otherwise, if choice is greater than the min and less than the max
        // return the integer value to int main()
        else if (choice >= CHOICE_MIN && choice <= CHOICE_MAX)
            return choice;  
        
        // Otherwise, output an error message to allow user to re-input choice.    
        else 
            cout << "\nPlease input a valid choice (1-4). \n";
    }
}    

// Function definition for winEngine; used to determine the winner of the game.
// Rock beats scissors. Scissors beats paper. Paper beats rock. Equal choices
// must play a 2nd game. pChoice and cChoice are passed from int main, an
// integer value is returned to int main 
void winEngine(int pChoice, int cChoice)
{
    // declare and initialize integer variable gameResult as 0 to prime for 
    // if-statements and swtich statements. 
    int gameResult = 0;

    // If the choices are the same, then its a draw. Assign 2 to gameResult.
    if (pChoice == cChoice)
        gameResult = 2;
    
    // Otherwise, if the player picked scissors, computer picked paper. 
    // Player wins; assign 1 to gameResult.        
    else if (pChoice == 2 && cChoice == 3)
        gameResult = 1;
    
    // Otherwise, if the player picked rock, Computer picked 2.
    // Player wins;; assign 1 to gameResult.
    else if (pChoice == 1 && cChoice == 2)
        gameResult = 1;
    
    // Otherwise, if the player picked paper and the computer picked rock
    // Player wins; assign 1 to gameResult.
    else if (pChoice == 3 && cChoice == 1)
        gameResult = 1;
    
    // Otherwise, the computer wins and the player loses.
    // Assign 0 to gameResult.
    else
        gameResult = 0;     
            
    // Switch statement accepts the value of gameResult and tests for the win
    // or lose flags to output the appropriate messages.
    // Function choiceDisplay() is called to determine the appropriate string 
    // to display in place of integer values pChoice and cChoice. 
    switch(gameResult)
    {
        // If gameResult is 2, then output draw message and declare a rematch.
        // Call winEngine with playerChoice() and computerChoice() as the 
        // argument functions to display draw and declare a rematch.
        case 2 : 
        {
                cout << "You picked " << choiceDisplay(pChoice) << "." << endl
                     << "The computer picked " << choiceDisplay(cChoice)
                     << " too! \nIt's a draw! You must have a rematch!\n"
                     << "\n****REMATCH*****\n";
                winEngine(playerChoice(), computerChoice());
                break;
        }
        //If gameResult is 1, then output win message and break out.
        case 1 : 
        {        
                cout << "\nYou picked " << choiceDisplay(pChoice)<< "." << endl 
                     << "The computer picked " << choiceDisplay(cChoice) << "."
                     << "\nYou won! Great job!\n";
                break;
        }
        //If gameResult is 0, then output lose message and break out.
        case 0 : 
        {
                cout << "\nYou picked " << choiceDisplay(pChoice) << "." << endl
                     << "The computer picked " << choiceDisplay(cChoice)
                     << ". \nSorry, you lost! Try again.\n";
                break;
        }
    }
    
}

// Function definition for choiceDisplay; used to determine the output string of 
// the player and computer choices. 1 outputs rock, 2 outputs scissors, 3
// outputs paper.  The integer passes the integer pChoice to the function 
// choiceDisplay when called, and returns a string.
string choiceDisplay(int choice)
{
    switch(choice)
    {
        //If the value passed to choice is 3, return "paper" as a string.
        case 3:                  
                return "paper";
                break;
        //If the value passed to choice is 2, return "scissors" as a string.
        case 2: 
                return "scissors";
                break;
        //If the value passed to choice is 1, return "rock" as a string.
        case 1: 
                return "rock";
                break;
    }
}


// Function prototype for playAgain(), which is used to display a menu, process 
// a user's input and output concerning the option to play again.
// When called, the function displays a message and returns an integer value
// which is tested in int main().
int playAgain()
{
    
    // Declare char variable choice to hold value of user choice to play again.
    char choice;
    
    // Display choice message.
    cout << "\n\nWould you like to play again (Y/N)? ";
    
    // While statement validates input to limite to 'Y', 'y', 'N', & 'n'.
    while (choice != 'Y' || choice != 'y' || choice != 'N' || choice != 'n')
    {
        // Accept user input and assign to choice.
        cin >> choice;
        
        // If statement to test if user input is 'Y' or 'y' and return 0 to
        // trigger while statement to continue in int main.        
        if (choice == 'Y' || choice == 'y')
            return 0;
        
        // Otherwise, if the user selects 'N' or 'n', output good bye message
        // and return -1 to trigger sentinal to end program.
        else if (choice == 'N' || choice == 'n')
        {    
            cout << "\nThank you for playing! Goodbye!\n\n";
            return -1;
        }
        
        // Otherwise, ask the user to input a valid choice, Y, y, N, or n.
        else 
            cout << "\nPlease type in a valid choice (Y/N): ";
    }
}        
        
        
        
        
        
        
        

/*****************
    Caleb Meador
    COSC 1436
    Programming Lab 3
    L3-7-15.cpp
    Tic-Tac-Toe Game
*******************/


#include <iostream>
#include <iomanip> // included to format output
#include <cstring> // included to use strings
using namespace std;

//Constant integer for the maximum number of rows
const int ROW_MAX = 3;

//Constant integer for the maximum number of columns.
const int COL_MAX = 3;

//The value of three '0's is 237
const int O_WIN = 237;

//The value of three 'X's is 264
const int X_WIN  = 264;

//The value of draw is set to 0 for winDisplay testing.
const int DRAW_WIN = 0;

//The minumum value of a full game board is 711.
const int MIN_SUM_BOARD = 711;

//playerOneInput() prototype - function gets playerOne input and assigns an 'X'
//to the board and updates the gameBoard array
void playerOneInput(char gameBoard[][COL_MAX], int rows);

//displayBoard() prototype - function displays the board each time a player
//makes a move or must retype a move.
void displayBoard(char gameBoard[][COL_MAX], int rows);

//playerTwoInput() prototype - this gets playerTwo's input and assign an 0 to 
//board and updates the gameBoard array
void playerTwoInput(char gameBoard[][COL_MAX], int rows);

//checkWin() prototype - checks all possible winning combinations to see if 
//a player has won or if a draw has occurred. Called after each move made by 
//players 1 and 2. Returns an integer to main to determine if the game 
//should continue.
int checkWin(char gameBoard[][COL_MAX], int winner, int rows);

//winDisplay prototype - takes arguments winner and gameBoard to display the
//appropriate winner, or draw after the checkWin has detected an ending.
void winDisplay(char gameBoard[][COL_MAX], int winner, int rows);

int main()
{
    //Char holds the game board in a 3x3 array initialized with '*' to indicate
    //a blank space. Later, will be populated with 'X' or 'O'
    char gameBoard[ROW_MAX][COL_MAX] = { {'*','*','*'},
                                         {'*','*','*'}, 
                                         {'*','*','*'} };
                         
    //Sentinal variable to test for end of game in while loop. When this changes
    //to a number besides 0, the while loops for the game ends.
    int endSent = 0;                         
    
    //The game tests winner for who will win; output message changes depending 
    //on the integer returned. 
    int winner;
    
    //While-loop continues while endSent is equal to 0; endSent is changed
    //within int main depending the values returned from checkWin and serves
    //as a sentinal to continue or end the program.    
    while (endSent == 0)
    {
        
        //Winner is set to 0 at the beginning of each loop to avoid potential
        //memory value conflicts.
        winner = 0;
        
        //system clear screen allows board to be cleared at each turn for a
        //cleaner looking game.
        system("cls");
        
        //Function displayBoard passes gameBoard function and ROW_MAX to run a 
        //loop to display the gameBoard.
        displayBoard(gameBoard, ROW_MAX);
        
        //Function playerOneInput passes gameBoard function and ROW_MAX to 
        //get player one's input, validates it, and stores an 'X' to 
        //the appropriate  array storage location.
        playerOneInput(gameBoard, ROW_MAX);
    
        //If statement runs checkWin function , which checks all possible win  
        //combinations and returns a value which indicates if there is a winner.
        //If a checkWin finds and returns a win-combination, then assign 
        //the value to winner and increment endSent to signal the end of the 
        //game.
        if (checkWin(gameBoard, winner, ROW_MAX) == O_WIN || 
            checkWin(gameBoard, winner, ROW_MAX) == X_WIN ||
            checkWin(gameBoard, winner, ROW_MAX) == DRAW_WIN)
        {
            
            winner = checkWin(gameBoard, winner, ROW_MAX);
            endSent++;
            
        }
    
        
        
        //If statement checks that endSent is not equal to one (i.e. player one 
        // hasn't won yet). If true,continue to player two's turn.
        if (endSent != 1)
        {
            //Clear the screen to display the updated game board.
            system("cls");
                    
            //Function displayBoard passes gameBoard function and ROW_MAX to run  
            //loop to display the gameBoard.
            displayBoard(gameBoard, ROW_MAX);
            
            
            //Function playerTwoInput passes gameBoard function and ROW_MAX to 
            //get player one's input, validates it, and stores an 'X' to 
            //the appropriate  array storage location.
            playerTwoInput(gameBoard, ROW_MAX);
            
            //If statement runs checkWin function , which checks all possible win  
            //combinations and returns a value which indicates if there is a 
            //winner. If a checkWin finds and returns a win-combination, then 
            //assign the value to winner and increment endSent to signal the end 
            //of the game.
            if (checkWin(gameBoard, winner, ROW_MAX) == O_WIN || 
                checkWin(gameBoard, winner, ROW_MAX) == X_WIN ||
                checkWin(gameBoard, winner, ROW_MAX) == DRAW_WIN)
            {
                winner = checkWin(gameBoard, winner, ROW_MAX);
                
                endSent++;
            } 
        }
    }
    
    //Function winDisplay passes gameBoard, winner, and ROW_MAX in order to
    //display a message declaring a winner, or declaring a draw.
    winDisplay(gameBoard, winner, ROW_MAX);
    
    //Pause the system before ending the program.
    system("PAUSE");
    
    return 0;
    
}

//Function displayBoard uses a for-loop to display the char gameBoard array 
//on the screen  
void displayBoard(char gameBoard[][COL_MAX], int rows)
{
    //Output game board title and column labels.
    cout << "\n----===GAME-BOARD====----\n\n";
    cout << "\t Column\n\t 1 2 3" << endl << endl;
    
    //While i is less than rows(3), then output a row label and run nested 
    //for-loop.
    for (int i = 0; i < rows; ++i)
    {
        
        cout << right << setw(5) << "Row " << i+1 << "\t";
        
        //while j is less than column max(3), then output the value of each
        //array location.
        for(int j = 0; j < COL_MAX; ++j)
        {
            cout << " " << gameBoard[i][j];
        }
        
        
        cout << endl << endl;
    }

}

//Function playerOneInput is passed gameBoard array and rows(3) 
void playerOneInput(char gameBoard[][COL_MAX], int rows)
{
    // integer variable rowChoice initialized to 0; used to hold player's 
    //choice of rows.
    int rowChoice = 0;
    
    //Integer variable columnChoice initialized to 0; used to hold player's 
    //choice of columns
    int columnChoice = 0;
    
    //Output message to user to input choice.
    cout << "Player 1: Place your X! \n\t[ROW]: ";
    
    //Input validation; while user chooses something other than 1,2, or 3, 
    //display an error message and continue to loop. 
    while(rowChoice != 1 && rowChoice != 2 && rowChoice != 3)
    { 
        //store user row choice to rowChoice.
        cin >> rowChoice;
        
        //If the user's choice is something other than 1,2, or 3, display 
        //an error message.
        if (rowChoice != 1 && rowChoice != 2 && rowChoice != 3)
        {
            cout << "\nPlease input a valid row (1-3): ";
        }
    
    }
    
    //Output column input prompt.
    cout << "\t[COLUMN]: ";
    
    //Input validation; while user chooses something other than 1,2, or 3, 
    //display an error message and continue to loop. 
    while(columnChoice != 1 && columnChoice != 2 && columnChoice != 3)
    { 
        //store user column choice to columnChoice.
        cin >> columnChoice;

        //If the user's choice is something other than 1,2, or 3, display 
        //an error message.
        if (columnChoice != 1 && columnChoice != 2 && columnChoice != 3)
        {
            cout << "\nPlease input a valid column (1-3): ";
        }
    
    } 
    
    //If the location in array gameBoard has '*' stored, then replace it with 
    // 'X'
    if(gameBoard[rowChoice-1][columnChoice-1] == '*')
    {
        gameBoard[rowChoice-1][columnChoice-1] = 'X';
    }
    //Otherwise, clear the screen and re-display the board, asking for a new
    //input in a spot that is  not already occupied, calling playerOneInput 
    //again.
    else
    {
        system("cls");
        displayBoard(gameBoard, rows);
        cout << "\n***This space is already marked!***"
             << "\n***Please choose another.***\n\n";
        playerOneInput(gameBoard, rows);
        
    }
}

//Function playerOneInput is passed gameBoard array and rows(3) 
void playerTwoInput(char gameBoard[][COL_MAX], int rows)
{
     // integer variable rowChoice initialized to 0; used to hold player's 
    //choice of rows.
    int rowChoice = 0;
    
    //Integer variable columnChoice initialized to 0; used to hold player's 
    //choice of columns
    int columnChoice = 0;
    
    //Output message to user to input choice.
    cout << "Player 2: Place your O! \n\t[ROW]: ";


    //Input validation; while user chooses something other than 1,2, or 3, 
    //display an error message and continue to loop.
    while(rowChoice != 1 && rowChoice != 2 && rowChoice != 3)
    { 
        //store user row choice to rowChoice.
        cin >> rowChoice;

        //If the user's choice is something other than 1,2, or 3, display 
        //an error message.
        if (rowChoice != 1 && rowChoice != 2 && rowChoice != 3)
        {
            cout << "\nPlease input a valid row (1-3): ";
        }
    
    }

    cout << "\t[COLUMN]: ";

    //Input validation; while user chooses something other than 1,2, or 3, 
    //display an error message and continue to loop.
    while(columnChoice != 1 && columnChoice != 2 && columnChoice != 3)
    { 

        //store user column choice to columnChoice
        cin >> columnChoice;

        //If the user's choice is something other than 1,2, or 3, display 
        //an error message.
        if (columnChoice != 1 && columnChoice != 2 && columnChoice != 3)
        {
            cout << "\nPlease input a valid column (1-3): ";
        }
    
    }


    //If the location in array gameBoard has '*' stored, then replace it with 
    // 'O'
    if(gameBoard[rowChoice-1][columnChoice-1] == '*')
    {
        gameBoard[rowChoice-1][columnChoice-1] = 'O';
    }
    
    //Otherwise, clear the screen and re-display the board, asking for a new
    //input in a spot that is  not already occupied, calling playerTwoInput 
    //again.    
    else
    {
        system("cls");
        displayBoard(gameBoard, rows);
        cout << "\n***This space is already marked!***\n***"
             << "Please choose another.***\n\n";
        playerTwoInput(gameBoard, rows);
    }
}


//Function checkWin is passed the array gameBoard, winner, and rows; used to 
//check if there is a winner. 
int checkWin(char gameBoard[][COL_MAX], int winner, int rows)
{
   
   //integer variable sumGameBoard is initialized as 0; used to hold the summed
   //values of the locations of winning positions from the game board.
   int sumGameBoard = 0;
   
   //Each time checkWin is called, this for-loop runs through array gameBoard
   //and adds each value to sumGameBoard in order to see the current total of 
   //the values on the board.
   for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < COL_MAX; ++j)
        {
            sumGameBoard += gameBoard[i][j];
        }
    }
   
    //If sumGameBoard is greater than MIN_SUM_BOARD (711), then there are too
    // too many characters on the board with no winner, indicating a draw.
    //If this is true, then assign the value of DRAW_WIN to winner (0) and
    //return the value to main.
    if(sumGameBoard > MIN_SUM_BOARD)
    {
        winner = DRAW_WIN;
        return winner;
    }
   
   //Otherwise, test each possible win-scenario to check if a player has won.
   else
   {
       //sum across the top; if the sum is equal to the value of 3 '0's or 
       // 3 'X's, then assign the value to winner and return winner to
       // main.
       if(gameBoard[0][0] + gameBoard[0][1] + gameBoard[0][2] == O_WIN ||
            gameBoard[0][0] + gameBoard[0][1] + gameBoard[0][2] == X_WIN)
        {
            
            winner = gameBoard[0][0] + gameBoard[0][1] + gameBoard[0][2];
            return winner;
        }
        
        //sum across the middle row; if the sum is equal to the value of 3 
        // '0's or 3 'X's, then assign the value to winner and return winner to
        // main.
        if(gameBoard[1][0] + gameBoard[1][1] + gameBoard[1][2] == O_WIN ||
            gameBoard[1][0] + gameBoard[1][1] + gameBoard[1][2] == X_WIN)
        {
            
            winner = gameBoard[1][0] + gameBoard[1][1] + gameBoard[1][2];
            //cout << endl << winner << endl;
            return winner;
        }
    
        //sum across the bottom row; if the sum is equal to the value of 3 
        // '0's or 3 'X's, then assign the value to winner and return winner to
        // main.
        if(gameBoard[2][0] + gameBoard[2][1] + gameBoard[2][2] == O_WIN ||
            gameBoard[2][0] + gameBoard[2][1] + gameBoard[2][2] == X_WIN)
        {
            
            winner = gameBoard[2][0] + gameBoard[2][1] + gameBoard[2][2];
            return winner;
        }
    
        // sum from top left to bottom right diagonal; if the sum is equal 
        // to the value of 3 '0's or 3 'X's, then assign the value to winner 
        // and return winner to main.
        if(gameBoard[0][0] + gameBoard[1][1] + gameBoard[2][2] == O_WIN ||
            gameBoard[0][0] + gameBoard[1][1] + gameBoard[2][2] == X_WIN)
        {
            
            winner = gameBoard[0][0] + gameBoard[1][1] + gameBoard[2][2];
            return winner;
        }
    
        
        // sum from top right to bottom left diagonal; if the sum is equal to 
        // the value of 3 '0's or 3 'X's, then assign the value to winner 
        //and return winner to main.
        if(gameBoard[0][2] + gameBoard[1][1] + gameBoard[2][0] == O_WIN ||
            gameBoard[0][2] + gameBoard[1][1] + gameBoard[2][0] == X_WIN)
        {
            
            winner = gameBoard[0][2] + gameBoard[1][1] + gameBoard[2][0];
            return winner;
        }
        // sum from top left to bottom left column; ; if the sum is equal to 
        // the value of 3 '0's or 3 'X's, then assign the value to winner and 
        // return winner to main.
        if(gameBoard[0][0] + gameBoard[1][0] + gameBoard[2][0] == O_WIN ||
            gameBoard[0][0] + gameBoard[1][0] + gameBoard[2][0] == X_WIN)
        {
            
            winner = gameBoard[0][0] + gameBoard[1][0] + gameBoard[2][0];
            return winner;
        }
        
        //sum from top middle to bottom middle column
        // if the sum is equal to the value of 3 
        // '0's or 3 'X's, then assign the value to winner and return winner to
        // main.
        if(gameBoard[0][1] + gameBoard[1][1] + gameBoard[2][1] == O_WIN ||
            gameBoard[0][1] + gameBoard[1][1] + gameBoard[2][1] == X_WIN)
        {
            
            winner = gameBoard[0][1] + gameBoard[1][1] + gameBoard[2][1];
            return winner;
        }
        
        //sum from top right to bottom right column
        // if the sum is equal to the value of 3 
        // '0's or 3 'X's, then assign the value to winner and return winner to
        // main.
        if(gameBoard[0][2] + gameBoard[1][2] + gameBoard[2][2] == O_WIN ||
            gameBoard[0][2] + gameBoard[1][2] + gameBoard[2][2] == X_WIN)
        {
            
            winner = gameBoard[0][2] + gameBoard[1][2] + gameBoard[2][2];
            return winner;
        }
        
    } 
       
}

//Function winDisplay is passed the array gameBoard, winner, and rows to test
//from int main in order to test the value and determine an appropriate display
//message.
void winDisplay(char gameBoard[][COL_MAX], int winner, int rows)
{
    
    //If winner is equal to 237, then O won; redisplay the gameBoard and output
    //congratulations message.
    if (winner == O_WIN)
    {
        system("cls");
        displayBoard(gameBoard, rows);
        cout << endl << endl << "The winner is O! Congratulations!\n";
    }

    //If winner is equal to 264, then X won; redisplay the gameBoard and output
    //congratulations message.
    else if (winner == X_WIN)    
    {
        system("cls");
        displayBoard(gameBoard, rows);
        cout << endl << endl << "The winner is X! Congratulations!\n";
    }    
        
    //Otherwise, if winner is equal to 0, then re-display the gameBoard and
    //output congratulations message.   
    else if (winner == DRAW_WIN)
    {
        system("cls");
        displayBoard(gameBoard, rows);
        cout << endl << endl << "Its a DRAW!!\n";
    } 
}

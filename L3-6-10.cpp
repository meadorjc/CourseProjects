/*****************
    Caleb Meador
    COSC 1436
    Programming Lab 3
    L3-6-10.cpp
    Lowest Score Drop
*******************/


#include <iostream>
#include <iomanip> //to format output
using namespace std;

//Declare function prototype for void getScore(); function will be passed a 
//double reference variable.
void getScore(double &);

//Declare function prototype void calcAverage(); parameters are 4 double
//variables. 
void calcAverage(double, double, double, double);


//Declare function prototype void findLowest(); parameters are 4 double
//variables.
double findLowest(double, double, double, double);



int main()
{
    //Delcare double variable storedValn; will store the value of the user input 
    //when called by the input when called by the getScore() function.
    double storedVal1, storedVal2, storedVal3, storedVal4;
    
    //Output welcome message and instructions for user.    
    cout << "*****Lowest Score Drop Program*****";
    cout << "\nPlease input 4 test scores.\n";
    
        
    //Call the getScore() function 4 times, once for each value, passing it the
    //reference variable, storedVal1;
    cout << "\nScore 1: ";
    getScore (storedVal1);
    cout << "\nScore 2: ";
    getScore (storedVal2);        
    cout << "\nScore 3: ";
    getScore (storedVal3);        
    cout << "\nScore 4: ";
    getScore (storedVal4);        

  
    //Call the calcAverage() function, passing it storedVal1-4 all at once. 
    calcAverage(storedVal1, storedVal2, storedVal3, storedVal4); 
    
    //Pause the system for the user before closing.
    system("Pause");

    return 0;

}


//getScore() gets a test score, stores it in
//a reference parameter variable testScore, and validates it. */
void getScore(double &testScore)
{
      //Function sets testScore to -1 to start validation while-statement.
      testScore = -1;
      
      //While-statement loops while testScore is less than 0 or greater than 
      //100.  If these conditions are met, output an error message to the user
      //and start from the beginning of loop.
      while (testScore < 0 || testScore > 100)
      {
            
            cin >> testScore;   //testScore is modified as a reference variable.
            
            if (testScore < 0 || testScore > 100)
             cout << "** Must be between 0 and 100:  ";
            
      }
}      
 
//calcAverage() calculates and displays the average of the four
//highest score. The function is called once by main. */
    
void calcAverage(double storeCalc1, double storeCalc2, double storeCalc3,
                 double storeCalc4)
{
    
    //Declare const double NUM_TEST_AVG and initialize to 3.0 in order to use
    //for the calculation of the average score of the top 3 test scores.
    const double NUM_TEST_AVG = 3.0;
    
    //Declare double variable lowestScore to hold lowestValue when finding the
    //lowest value of the series.
    double lowestScore;    
    
    //Declare double variable sumScores and initialize to 0; used to sum the 
    //highest three scores once the lowest value has been identified.
    double sumScores = 0; 
    
    //Call the function findLowest(), passing it all four storeCalc variables, 
    //and assign the return value to lowestScore.
    lowestScore = findLowest(storeCalc1, storeCalc2, storeCalc3, storeCalc4);
    
    //Output message to alert user to the lowest score that is being dropped.
    cout << "\nDropping the lowest score of " << lowestScore << ".\n";
    
    cout << "\nCalculating the average of the three highest scores.\n";
    
    
    //Series of if statements test each value in storeCalc(1-4) to see if it is 
    //the same value that was returned by lowestScore - this tests to see if its
    //the lowest value.  If it is NOT the lowest value, then the value in
    //storeCalc1 is added to sumScores.
    if (storeCalc1 != lowestScore)
        sumScores += storeCalc1;
    if (storeCalc2 != lowestScore)
        sumScores += storeCalc2;
    if (storeCalc3 != lowestScore)
        sumScores += storeCalc3;
    if (storeCalc4 != lowestScore)
        sumScores += storeCalc4;
        
    
    //Output message to user and calculate the average by dividing sumScores
    //by the const double NUM_TEST_AVG, which equals 3.00.
    cout << "\nThe average of the three highest scores is " << setprecision(2)
         << fixed << sumScores / NUM_TEST_AVG << ".\n\n";
    
    
    
    
      
}
//findLowest() finds and returns the lowest of teh five scores passed to it.
//It is called by calcaverage. All four storeCalc variable values are passed to
//findLowest(), where there are stored in double variables low1-4.
double findLowest(double low1, double low2, double low3, double low4)
{
    
    //Declare double variable lowestInt; used to store lowest variables as the
    //function finds lower values. Initilized to low1 to compare the value to
    //the other values.
    double lowestInt = low1;
    
    //If statements compare low1 to each subsequent value and test to see if 
    //lowestInt is greater than low(n). If lowestInt is greater, then low(n) 
    //is assigned to lowestInt.
    if  (lowestInt > low2)
        lowestInt = low2;
        
    if (lowestInt > low3)
        lowestInt = low3;
        
    if (lowestInt > low4)
        lowestInt = low4;

    
    //lowestInt is returned to the function calcAverage().    
    return lowestInt;  
}        
        
    
    
    



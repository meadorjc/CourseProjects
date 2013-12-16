/**********************
    Caleb Meador
    COSC 1436
    4/28/2013
    L3-7-5.cpp
    Rain or Shine
***********************/

#include <iostream>
#include <fstream> //to open and get input from a file.
#include <cstring> //to manipulate strings within file.
using namespace std;


//Declare global const variable integer MONTHS and initialize as 3; only 3
//months in this report.
const int MONTHS = 3;

//Declare global const variable integer DAYS and initialize as 30; only 30
//days in this report.
const int DAYS = 30;

//Declare global const variable integer CONDITION and initialize as 3; only 3
//conditions in this report.
const int CONDITION = 3;

//Protype for getValues(), gets values from the .dat file.
void getValues(int monthDayCondition[][DAYS], int monthRow);

//Protype for calcConditions, which reads the data in monthDayCondition and 
//counts the conditions, storing them in countMonthCondition.
void calcConditions(int monthDayCondition[][DAYS], 
                    int countMonthCondition[][CONDITION], int monthRow);

//Prototype for displayMonthReport, which displays the counted conditions from 
//countMonthCondition.
void displayMonthReport(int countMonthCondition[][CONDITION],
                        int monthRow);

//Prototype for displayTotalReport(); countMonthCondition array, which holds
//the condition totals of each month. This will display the appropriate weather 
//information for the total of 3 months.
void displayTotalReport(int countMonthCondition[][CONDITION], 
                        int monthRow);

//Prototype of displayMostRainy(); countMonthCondition array analyzed.
//Display the month with the most rainy days. 
void displayMostRainy(int countMonthCondition[][CONDITION], 
                      int monthRow);

int main()
{

    //Declare integer variable array with 3 rows(months) and 30 columns (days).
    //This holds the weather condition as an integer.
    int monthDayCondition[MONTHS][DAYS];
    
    //Declare integer variable array with 3 rows(months) and 3 columns
    //for conditions. Intiialize all values to 0. This holds the summed totals
    //of the months.
    int countMonthCondition[MONTHS][CONDITION] ={{0,0,0},
                                                {0,0,0},
                                                {0,0,0}};

    //Output welcome message for user.
    cout << "***Welcome to the Weather Report Program***" << endl << endl;
    
    //Call getValues() function, passing the array monthDayCondition.
    getValues(monthDayCondition, MONTHS);

    //Call calcCondition() function, passing the arrays monthDayCondition and
    //countMonthCondition. This is to analyze the data in the array and
    //calculate monthly totals of weather conditions.
    calcConditions(monthDayCondition, countMonthCondition, MONTHS);
    
    //Call displayMonthReport() and pass countMonthCondition array, which holds
    //the totals of each month. This will display the appropriate weather 
    //information.
    displayMonthReport(countMonthCondition, MONTHS);
    
    //Call displayTotalReport() and pass countMonthCondition array to show the
    //totals of three months    
    displayTotalReport(countMonthCondition, MONTHS);
    
    //call displayMostRainy() and pass countMonthCondition array to analyze
    //the array values and display the month with the most rainy days. 
    displayMostRainy(countMonthCondition, MONTHS);
    
    
    system("Pause");
    

    return 0;


}


//This function gets values from the files and converts them to a 2d array
// called monthDayCondition.    
void getValues(int monthDayCondition[][DAYS], int monthRow)
{
    //declare ifstream inFile to open and use the file. 
    ifstream inFile;
    
    //declare string variable array with (3*30*3) storage locations
    //to hold hold delineated input from input file. Input read is space 
    //delimited so there will be 270 input values.
    string tempFileInput[MONTHS*DAYS*CONDITION];
    
    //declare int variable array with (30*3) locations to hold values to convert
    //weather condition string values to integer values
    int tempConvertString[DAYS*CONDITION];
    
    //open file
    inFile.open("RainOrShine.dat");
    
    //Run for-loop for (3*30*3) iterations store values in temporary array.
    for(int i = 0; i <= monthRow*DAYS*CONDITION; ++i)
        inFile >> tempFileInput[i];

    
    //Declare and initialize integer variable to increment value for 
    //tempConvertString[count]
    int count = 0;
    
    //Run for loop 270 times and look at each value in the tempFileInput array
    //by comparing the values of the strings.  If the test finds a string, 
    //it stores it as integers  1 (C) 2 (R) or 3(S) and increments the count
    //variable to increase the storage location in the array. 
    for (int i = 0; i < monthRow*DAYS*CONDITION; ++i)
    {
                    
        if(tempFileInput[i] == "C")  
        {
            tempConvertString[count] = 1;
            count++;
        }
        else if(tempFileInput[i] == "R")
        {
            tempConvertString[count] = 2;
            count++;
        }
        else if(tempFileInput[i] == "S")
        {
            tempConvertString[count] = 3;
            count++;
        }
    }            
    
    
    //Declare integer variable k and initialize to 0 for use as counter. 
    //Declared outside the for loop so that it can be primed at each call
    //function.               
    int k = 0;
        
    
    //Converts the tempConvertString into a 2d array, as per the instructions
    //K is incremented within the nested loop to provide a counter for 
    //tempConvertString.
    for (int i = 0; i < MONTHS; ++i)
    {
        for (int j = 0; j < DAYS; ++j)
        {
            monthDayCondition[i][j] = tempConvertString[k];
            k++;     
        }
    }
}

//This function uses the arrays monthDayConditions to analyze the values within
//the arrays and calculate the monthly totals of weather values.
void calcConditions(int monthDayCondition[][DAYS], 
                    int countMonthCondition[][CONDITION], int monthRow)
{
    
    
        
    //For statement iterates through the monthDayCondition array and 
    //increments the values within countMonthCondition array depending on
    //what the switch statement reads. 1 increments [i][0], 2 increment [i][1],
    //and 3 increments [i][2]. This way the monthly totals can be counted.
    for (int i = 0; i < monthRow; ++i)
    {
        for (int j = 0; j < DAYS; ++j)
        {
            switch(monthDayCondition[i][j])
            {
                case 1:
                        countMonthCondition[i][0]++;
                        break;
                case 2:
                        countMonthCondition[i][1]++;
                        break;
                case 3:
                        countMonthCondition[i][2]++;
                        break;
                default:
                        cout << "error";
             }            
        }               
        
    }
}

//This function displays the counted weather information in format for 
//each month that is stored in countMonthCondition.
void displayMonthReport(int countMonthCondition[][CONDITION], int monthRow)
{
    
    //For statements iterates through each month and displays the appropriate
    //monthly report header as tested in the if statements. It then iterates
    //through the conditions and displays the summed total of each type of
    //condition type and the total days in that month, as tested in the nested
    //if statements.
    for (int i = 0; i < MONTHS; ++i)
    {
        if (i == 0)
            cout << "\n\t* JUNE: Weather Report\n\n";
        
        else if ( i == 1)
            cout << "\n\t* JULY: Weather Report\n\n";
        
        else if ( i == 2)
            cout << "\n\t* AUGUST: Weather Report\n\n";
        
        for (int j = 0; j < CONDITION; ++j)
        {
            if (j == 0) 
            {
                cout << "\tCloudy Days: " << countMonthCondition[i][j] << " days."
                      << endl;
            }
            else if (j == 1)
            {
                cout << "\tRainy Days: " << countMonthCondition[i][j] << " days."
                      << endl;
            }
            else if (j == 2)
            {
                cout << "\tSunny Days: " << countMonthCondition[i][j] << " days."
                      << endl;
            }
        }
    }
}

//This function displays the total weather conditions for the 3 months in total.
//The array, countMonthCondition is passed.
void displayTotalReport(int countMonthCondition[][CONDITION], 
                        int monthRow)
{
    
    //Declare and intialize three integer variables to 0 to hold the totals
    //for each type of weather condition for the month.
    int totalCloudy = 0, totalRainy = 0, totalSunny = 0;
    
    
    //For-loop iterates through countMonthCondition and stores the each monthly
    //count of weather conditions to the appropriate variable, as tested by the
    //it statment. 
    for (int i = 0; i < monthRow; ++i)
    {
               
        for (int j = 0; j < CONDITION; ++j)
        {
            if (j == 0) 
            
                totalCloudy += countMonthCondition[i][j]; 
            
            else if (j == 1)
            
                totalRainy += countMonthCondition[i][j]; 
            
            else if (j == 2)
            
                totalSunny += countMonthCondition[i][j];
            
        }
     }
    
    //The totals for the 3 months are output to the user.
    cout << "\n* Three Month Summary Report****\n"
         << "\n\t* June, July, and August\n\n"
         << "\tTotal Cloudy Days: " << totalCloudy << endl
         << "\tTotal Rainy Days:  " << totalRainy << endl
         << "\tTotal Sunny Days:  " << totalSunny << endl;

}


//This function displays the month with the most rainy days in it.
//The array countMonthCondition is passed to analyze the information within it.
void displayMostRainy(int countMonthCondition[][CONDITION], int monthRow)
{
    //Declare a local integer variable called mostRainyMonth and initialize it
    //by assigning the value of countMonthCondition[0][1] to compare it to the
    //other locations where rainy day totals are kept (in [1][1] and [2][1].
    int mostRainyMonth = countMonthCondition[0][1];
    
    //Declare a local integer variable called monthID and initialize it to
    //0; this will store the ID of the month for later output testing.     
    int monthID = 0;
    
    //Check to see if mostRainyMonth is less than the other values stored for
    //rainy day totals in each month. If its less, than it will be replaced
    //with the larger number by assignment, and the monthID is set to 1 or 2.
    if (mostRainyMonth < countMonthCondition[1][1])
    {
        mostRainyMonth = countMonthCondition[1][1];
        monthID = 1;
    }
    
     if (mostRainyMonth < countMonthCondition[2][1])
    {
        mostRainyMonth = countMonthCondition[2][1];
        monthID = 2;
    }
    
    //Output for the most rainy month data.
    cout << "\n\t* Most Rainy Month\n";
    
    //If statement tests the monthID and displays the appropriate month and 
    //corresponding number of rainy days.      
    if (monthID == 0)
        cout << "\n\tJUNE: " << mostRainyMonth << " rainy days.\n\n";
    
    else if (monthID == 1)
        cout << "\n\tJULY: " << mostRainyMonth << " rainy days.\n\n";
        
    else if (monthID == 2)
        cout << "\n\tAUGUST: " << mostRainyMonth << " rainy days.\n\n";

    
}

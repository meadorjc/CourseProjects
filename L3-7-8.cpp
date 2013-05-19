/********************
    Caleb Meador
    COSC 1436
    4/29/2013
    L3-7-8.cpp
    Payroll
********************/

#include <iostream>
#include <iomanip> //to format output

using namespace std;

//Declare constant integer NUM_EMPS; there are only 7 employees.
const int NUM_EMPS = 7;

//Function void input() prototype is passed arrays empId, hours, 
//and payRate arrays. 
void input(long int empId[], int hours[], double payRate[], int employees);   

//Function void input() prototype is passed hours, payRate, and wages.
void calcWages( int hours[], double payRate[], 
                double wages[], int employees);

//Function void input() prototype is passed empId, and wages.
void displayEmpWages(long int empId[], double wages[],
                    int employees);

int main()
{
    
    //declare long int array to hold each employee's ID number.
    long int empId[NUM_EMPS] = {5658845, 4520125, 7895122, 8777541, 
                               8451277, 1302850, 7580489};
    
    //Declare integer variable array hours[NUM_EMPS] and initialize to -1 for 
    // later input validation; This will hold the number of hours the 
    //employee worked.
    int hours[NUM_EMPS] = {-1, -1, -1, -1, -1, -1, -1};
    
    //Declare a double variable array payRate[NUM_EMPS] and initialize to 0; 
    //this will hold the pay rate per  hour of each employee.
    double payRate[NUM_EMPS] = {0, 0, 0, 0, 0, 0, 0};
    
    //Declare double variable array wages[NUM_EMPS] to hold the 
    //calculated wages. Initialize to 0.
    double wages[NUM_EMPS] = {0, 0, 0, 0, 0, 0, 0};
    
    
    //Display welcome message to user.
    cout << "\t--===Payroll Time===--" << endl << endl;

    //call function input(), passing empId, hours, and payRate arrays.
    input(empId, hours, payRate, NUM_EMPS);

    //Call function calcWages(), passing hours, payRate, and wages arrays.
    calcWages(hours, payRate, wages, NUM_EMPS);

    //Call function displayEmpWages(), passing the empId and wages arrays.
    displayEmpWages(empId, wages, NUM_EMPS);

    cout << endl;
    
    system("PAUSE");
    
    return 0;
}

//Function void input() is passed arrays empId, hours, and payRate arrays. 
//Input takes the user input, validates it, and then stores it in the
//appropriate arrays.
void input(long int empId[], int hours[], 
            double payRate[], int employees)   
{
    
    //For-statement iterates through the arrays and displays the employee ID,
    //accepts and validates user input for hours and pay rate.
    for(int i = 0; i < employees; ++i)
    {
        
        
        cout << "\n\tEmployee ID: " << empId[i];
        cout << "\n\tHours: ";     
        
        //Input validation; hours must be a positive integer.
        while ( hours[i] < 0)
        {        
            cin >> hours[i];
            
            if (hours[i] < 0)
                cout << "\n\t***Please input a positive number of hours: ";     
        }
        
        
        cout << "\tPay Rate: ";
        
        //input validation; pay rate must be greater than 6.00
        while (payRate[i] < 6.00)
        {
            cin >> payRate[i];
            
            if (payRate[i] < 6.00)
                cout << "\n\t***Please input a pay rate greater than 6.00: ";
        }    
    
    }
}    
    
//Function calcwages() is passed the arrays for hours, payRate, and wages.
//calcWages() iterates through the arrays, assigning the employee hours * payRate
//to wages at each iteration.
void calcWages( int hours[], double payRate[],
                double wages[], int employees)
{
    for(int i = 0; i < employees; ++i)
    {
        wages[i] = hours[i]*payRate[i];
    } 
}    
    
//function displayEmpWages() is passed the arrays for the employee IDs for 
//display and wages for display to the user. A for-loop is used to iterate
//through the arrays in order to display the appropriate information.
void displayEmpWages(long int empId[], double wages[], int employees)
{
    cout << "\n\n * * Total Payroll Report * *\n\n"
         << "\nEmployeeID\tGross Wages\n\n";
    
    for(int i = 0; i < employees; ++i)
    {
        cout << " " << empId[i] << fixed << setprecision(2)
             << "\t$" << wages[i] << endl;
    
    } 
}    
    
    
    
    
    
    
    
    
    
    

/******************************
   Caleb Meador
   4/2/2013
   L2-4-5.cpp
   Body Mass Index
********************************/


#include <iostream> 	
#include <iomanip>     // to manipulate ouput
#include <cmath>       // to use pow() function.
using namespace std;

double bmi, weight = 0, feet, inches = 0;

int main()
{

    cout << "******Body Mass Index Calculator******" << endl;
    
    //To define a valid height range
    while (weight <= 0 || weight >= 1200)
    {     
          cout << "\nWhat's your weight?\n Weight in pounds (1-1200): ";
          cin >> weight; //Get input from user.
    
    
          if (weight <=0 || weight >=1200)
             cout << "\nYou must input a valid weight. Please try again\n"
                  << "-------------------------------------------------\n";
    }        
    
    //To define a valid height range
    while (inches <= 0 || inches >=108)
    {
    
        cout << "\nWhat's your height?" << endl 
             << " Feet(0-8): ";
        cin >> feet; // get input from user.
        
        cout << " Inches(0-11): ";
        cin >> inches; //get input from user.
        
        feet *= 12; // convert feet to inches.
        inches += feet; //add feet in inches to get total inches.
        
        // To test inches for validity and alert user if invalid.
        if (inches <=0 || inches >= 108)
    
           cout << "\nYou must input a valid height. Please try again.\n"
                << "--------------------------------------------------\n";
    }
   
    // to calculate BMI
    bmi = (weight*703)/pow(inches, 2); 
    
    //Display the BMI to user.
    cout << "\nYour BMI is " << setprecision(1) << fixed << bmi << "." << endl;
    
    //Test if BMI is in the optimal range and display if true.
    if (bmi >= 18.5 && bmi <=25)
    {  
       cout << "This falls within the optimal range of 18.5-25.0 and is ";
       cout << "considered healthy.\n" << endl;
    }   
    //Test if BMI falls in the range of underweight category.
    else if (bmi <18.5)
         cout << "A BMI of less than 18.5 is considered underweight.\n" << endl;
    
    //Test is BMI falls in the range of overweight.
    else if (bmi > 25)
         cout << "A BMI of more than 25.0 is considered overweight.\n" << endl;
        
    
    
    system("Pause");
	
    return 0;
}


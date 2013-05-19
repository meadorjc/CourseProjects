/******************************
   Caleb Meador
   2/25/2013
   Lab1-C2-P11.cpp
   Distance per Tank of Gas
********************************/

// Headers
#include <iostream>
#include <iomanip> //include to use formatting functions
using namespace std;


int main()
{
    const double FULL_GALLONS = 20.; //initialize constant, # of gallons full.
    const double MPG_CITY = 21.5;    //initialize constant, miles/gallon city.
    const double MPG_HIGHWAY = 26.8; //initialize constant, miles/gallon highway
    double distanceCity;             //initialize variable, distance in city
    double distanceHighway;          //initialize variable, distance on highway

    
    //Calculate the maximum miles you can drive on a full tank in the city.
    distanceCity = FULL_GALLONS * MPG_CITY ; 
 
    //Calculate the maximum miles you can drive on a full tank on highway.
    distanceHighway = FULL_GALLONS * MPG_HIGHWAY;
    
    //Display number of miles you can drive for both city and highway on a full
    // tank of gas.
    cout << endl << endl;
    cout << "On a full tank of gas, you can drive ";          //Display text
    cout << setw(4) << setprecision(1) << fixed << showpoint  //Format number
         << distanceCity;                                     //Display distance
    cout << " miles in the city, and " << endl;               //Display text
    cout << setw(4) << setprecision(1) << fixed << showpoint  //Format Number
         << distanceHighway;                                  //Display distance
    cout << " miles on the highway.";                         //Display text
    
    cout << endl << endl;     
         



	// Pause system before ending program
    system("PAUSE");


    return 0;
}

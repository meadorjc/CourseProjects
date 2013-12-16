/******************************
   Caleb Meador
   4/2/2013
   L2-4-13.cpp
   Shipping charges
********************************/


#include <iostream> 	
#include <iomanip>     // to manipulate ouput
#include <cmath>       // to use pow() function.
using namespace std;


int main()
{
     
    //declare double weight & distance; initialize to 0 to prime for loop.
    double weight = 0, distance = 0, shippingCharge;
    double distConvert;

    
    
    //output Title
    cout << "******Fast Freight Shipping Charge Calculator******" << endl;
    
        
    //Input loop to test value assigned to weight; input validation.
    while (weight <= 0 || weight > 20)
    {
          cout << "\nPlease input the weight of the package in kilograms.\n";
          cout << "Shipping Weight (0-20): ";
          cin >> weight;  //get user input & assign to weight.
          
          //Input validation to alert user if invalid.
          if (weight <= 0 && weight >= 0)
          {
             cout << "\nPlease input a valid shipping charge.\n"
                  << "-------------------------------------\n"; 
          }
    }
    //Input loop to test value assigned to distance; input validation.
    while (distance < 10 || distance > 3000)
    {
          cout << "\nPlease input the distance to ship the package in miles.\n";
          cout << "Distance to Ship (10-3000) ";
          cin >> distance; //get user input & assign to distance.
       
          //Input validation to alert user if invalid.
          if (distance < 10 && weight >= 3000)
          {
             cout << "\nPlease input a valid shipping distance.\n"
                  << "-------------------------------------\n";
          }
    }
    //Convert km and round up to the nearest 1000
    distConvert = ceil (distance/500.0);
    
    //Classify weight for shipping cost
    if (weight > 10)
    {
       
          shippingCharge = distConvert * 4.80;
          
       cout << "\nYour shipping charge is $" << setprecision(2) << fixed  
            << shippingCharge << ".\n";
       
    }
    
    //Classify weigh for shipping cost   
    else if (weight > 6 && weight <=10)
    {
          shippingCharge = distConvert * 3.70;
       
       cout << "\nYour shipping charge is $" << setprecision(2) << fixed 
            << shippingCharge << ".\n";
    }   
    
    //Classify weight for shipping cost
    else if (weight > 2 && weight <= 6)
    { 
          shippingCharge = distConvert * 2.20;
       
         cout << "\nYour shipping charge is $" << setprecision(2) << fixed 
              << shippingCharge << ".\n";
    }     
            
    //Classify weight for shipping cost
    else
    {     shippingCharge = distConvert * 1.10;
           
    
          cout << "\nYour shipping charge is $" << setprecision(2) << fixed 
               << shippingCharge << ".\n";
    }   
    
    system("Pause");
	
    return 0;
}


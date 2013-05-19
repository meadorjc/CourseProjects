/******************************
   Caleb Meador
   4/2/2013
   L2-4-21.cpp
   Geometry Calculator
********************************/


#include <iostream> 	
#include <iomanip>     // to manipulate ouput
#include <cmath>       // to use pow() function.
using namespace std;

//declare global constant PI
const double PI = 3.14159;

int main()
{
     
    //declare & initialize choice to 0 to prime for loop.
    double choice = 0;
    
    //declare variables for use in calculating areas.
    double circRad, rectL, rectW, triB, triH;
    
    //output Title & Menu
    cout << "******Geometry Calculator******" << endl;
    
    cout << endl << "    1. Calculate the Area of a Circle";
    cout << endl << "    2. Calculate the Area of a Rectangle";
    cout << endl << "    3. Calculate the Area of a Triangle";
    cout << endl << "    4. Quit";
    
    cout << "\n    Please enter your choice (1-4)  ";
    
   
    //Loop is primed to 0 so loop begins as true.    
    while (choice < 1 || choice > 4 )
    {     
          //Get input from user and assign to choice
          cin >> choice;
          
          //Test choice for option 4 and quit if true.      
          if (choice == 4) 
          {
               cout << "\n********************************************"
                    << "\n This program will now terminate. Goodbye."
                    << "\n*******************************************";
          } 
         
          //Otherwise, test for option 3.
          else if (choice == 3)
          {
               cout << "\nCalculating the Area of a Triangle"
                    << "\n----------------------------------";
               cout << "\nPlease input the following information in inches. "
                    << "\nBase: ";
               
               //Get size of base and assign to triB.
               cin >> triB;
               
               cout << "Height: ";
  
               //Get height of triangle and assign to triH
               cin >> triH;
  
               //Calculate and display area of triangle.
               cout << "The area of the triangle is " << setprecision(2)
                    << fixed << triB * triH * .5 << " inches.";
          }
          
          //Otherwise, test for 2
          else if (choice == 2)
          {
               cout << "\nCalculating the Area of a Rectangle"
                    << "\n-----------------------------------";
               cout << "\nPlease input the following information in inches. "
                    << "\nLength: ";
               
               //Get length of rectangle & assign to rectL.
               cin >> rectL;
          
               cout << "Width: ";
               
               //Get width of rectangle and assign to rectW.
               cin >> rectW;
               
               //calculate area and display in message.
               cout << "\nThe area of the rectangle is " << setprecision(2)
                    << fixed << rectL * rectW << " inches.";
          }
          
          // Otherwise, test for 1
          else if (choice == 1)
          {
             cout << "\nCalculating the Area of a Circle\n"
                  << "----------------------------------";
             cout << "\nPlease input the radius of the circle in inches: " ;
             
             //Get radius of circle; assign to circRad
             cin >> circRad;          
             
             //Calculate the area and display
             cout << "\nThe area of the circle is " << setprecision(2)
                  << fixed << PI * pow(circRad, 2) << " inches.";               
                    
          }
          
          //Otherwise test for invalid input & display error message to user.
          else if(choice < 1 || choice > 4 )
            
             cout << "\n\nPlease input a valid choice (1-4)";
    
    
    }      
    
    
      cout << endl << endl;
      system("Pause");
	
    return 0;
}


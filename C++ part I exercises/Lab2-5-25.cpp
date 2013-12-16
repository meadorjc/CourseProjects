/******************************
   Caleb Meador
   4/2/2013
   L2-5-25.cpp
   Using Files - Student Line Up
********************************/


#include <iostream> 	
#include <iomanip>
#include <fstream>     // to get info from file.
#include  <string>       // to use strings 
using namespace std;

int main()
{
    //Declare ifstream variable inputFile
    ifstream inputFile;
    
    //Declare string variables, initialize to prime for loop & testing.
    string stud1, frontStud = "M", backStud ="N";
    
    //Open the inputFile "LineUp.txt".
    inputFile.open("LineUp.txt");
    
    //Output Title
    cout << "Student Line Up\n";
    
    //Test to see if inputFile opened correctly and output error message if not.
    if (!inputFile)
    {
       cout <<"\n********************************************************\n";
       cout << "Please check that LineUp.txt is in the proper folder.\n";
       cout <<"\n********************************************************\n";
    }
    
    //While loop to continue while program reads from text file.
    while (inputFile >> stud1)
    {
          
          
          //Check if stud1 is less than frontStud and assign stud1
          //to frontStud if true.
          if (stud1 <= frontStud)
          {
             frontStud = stud1;
 
          }   
          
          //Otherwise, check if stud1 is greater than backStud and assign stud1
          //to backStud if true.
          else if (stud1 >= backStud)
          {
              backStud = stud1;
          }
          
          /*********************************************************** 
          //For testing purposes only...un-comment to watch flow-through    
          cout << setw(10) << stud1 << " " << setw(10) << frontStud << " " 
               << setw(10) << backStud << " " << setw(10) <<endl;  
          //************************************************************/
    }
    //Output the front student's name and the back student's name in a message.
    cout << "The first student in line is " << frontStud << ".";
    cout << "\nThe last student in line is " << backStud << ".";
    
    //Close the file.
    inputFile.close();
  
    cout << endl << endl;
      
    system("Pause");
	
    return 0;
}


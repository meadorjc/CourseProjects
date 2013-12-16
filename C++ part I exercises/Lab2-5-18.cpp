/******************************
   Caleb Meador
   4/2/2013
   L2-5-18.cpp
   Population Bar Chart
********************************/


#include <iostream> 	
#include <iomanip>     // to manipulate ouput
#include <fstream>     // to access file.
using namespace std;

int main()
{
    //declare ifstream type infile to get input from file.
    ifstream inputFile;
    
    //declare double variable year and population. Initialize year as 1900.
    int year = 1900, population;
      
    //Open the file
    inputFile.open("People.txt");
      
    //output Title
    cout << "Prairieville Population Growth" << endl;
    cout << "(each * represents 1,000 people)\n";
    
    //Test to see if the file was successfully opened and alert user if not.
    if (!inputFile)
       cout << "File open failure! Please make sure the proper file exists.\n";
   
   //Test for read success with while loop.
    while (inputFile >> population)
    {   
        //to round to nearest 1000.  
        if (population % 1000 < .5)
           population /= 1000;
        else 
           population = (population + 500)/1000;
        
        //output year and set boundaries for chart.
        cout << endl << left << setw(6) << year;
        
        //Loop output of chart population marker based on value in population
        for(int i=0; i < population; ++i)
        {
                 cout << "*";
        }
        
        //increase year number.
        year += 20;
            
    }      
    //Close the file
    inputFile.close();
    
      cout << endl << endl;
      
      system("Pause");
	
    return 0;
}


/**************************
    Caleb Meador
    COSC 1436
    4/23/2013
    L3-6-22
    isPrime Function List
***************************/

#include <iostream>
#include <fstream>  //fstream to allow file access.
using namespace std;

// Function prototype for isPrime; used to determine if a number is prime.
// Parameter: integer variable, number, will pass the value from main.
int isPrime(int number); 

// Global constant is used to set the maximum number to which the program will 
// test for prime. Initialized to 100 as per instructions.
const int MAX_NUM = 100;

int main()
{
    // Define outFile variable for use in writing to an output file. 
    ofstream outFile;
    
    // Using outFile to open "prime001.txt" to write to 
    outFile.open("prime001.txt");
    
    
    
    // Outputing information about program to console.
    cout << "********************IsPrime Program***********************";
    cout << endl << endl;
    
    cout << "An integer greater than one is called a prime number if \n"
         << "its only positive divisors (factors) are one and itself. \n\n"
         << "This program calls isPrime() function to determine if a number is"
         << "prime. \nIf the number is prime, it will be written to a file." 
         << "\n\nPlease open 'prime001.txt' in order to view the output file.\n"
         << "\n\nNow calculating prime numbers.\n\n";
    
    // Output infomration about program to prime001.txt
    outFile << "*****************IsPrime Program***********"; 
    outFile << endl << endl;     
    
    outFile << "An integer greater than one is called a prime number if \n"
            << "its only positive divisors are one and itself. \n\n"
            << "This program calls isPrime() to determine if a number is"
            << "prime. \nIf the number is prime, it will be written to a file." 
            << "\n\nNow calculating prime numbers.\n\n";
    
    // For-loop to iterate from 1 to MAX_NUM.
    for( int i = 1; i <= MAX_NUM; ++i)
    {
        // Pass i to isPrime; isPrime uses a series of tests and modulus  
        // operators to test i. Once tested, the value is returned as 0 or 1.
        // If greater than 0, the i is prime; output the number.
        if(isPrime(i) > 0)
        {
            outFile << isPrime(i) << " ";  //write i to prime001.txt
            cout << isPrime(i) << " ";      //write i to console.
        }
    }
    
    // Formatting in file and console
    cout << endl << endl;
    
    outFile << endl;
    
    system("PAUSE");
    
    outFile.close();  //close prime001.txt
    
    return 0;

    
}


// isPrime Function: accepts integer arguments as variable number
// This function takes the value in number and compares it to each integer
// in the sequence from 1 to 100, incrementing integer variable countMod0 for 
// each time the value can be divided evenly. Since all numbers can be divided
// by at least themselves and 1, a countMod0 value of 2 indicates that a number
// is prime.
int isPrime(int number)   
{
    // Set up a variable countMod0 to count the number of integers that evenly
    // divide into number. countMod0 must be initialized to 0 at each iteration
    // of the function to accurately count even divisors.
    int countMod0 = 0;
    
    // For-loop declares and initializes i as a number to cycle through while 
    // i is less than MAX_NUM, incrementing by one at each iteration.
    for(int i = 1;(i < MAX_NUM); ++i)
    {
              
        // If-statement looks at the value of number modulus i and tests it 
        // to see if its equal to 0. If it is equal to 0, then number has been
        // divided evenly by a number, and countMod0 is incremented by 1. 
        if(number % i == 0)
        {
                countMod0++;    
        }
        
    }
     // If-statement looks at the value of countMod0 and if its equal to 2, 
     // then return the value of number to int main(). Otherwise, return 0.
     if(countMod0 == 2)
        return number;
     else
        return 0;
}

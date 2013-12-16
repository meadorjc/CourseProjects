/*****************************************************
*	Caleb Meador
*	COSC1437 GE#1, Fall, 2013
*	Filename:LotteryMJ.CPP
*
********************************************************/
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

//Function headers
void displaySet(int array[], int size);
void populate(int array[], int size);
bool match(int array[], int randNum, int size);
void primeArray(int array[], int size);
bool typeTwoMatch(int arrayOne[], int arrayTwo[], int size);
bool typeOneMatch(int arrayOne[], int arrayTwo[], int size);
void simulation(int firstSet[], int secondSet[], int size, int runs);

//Set constants
const int SET_SIZE = 6;	//set the max size of arrays
const int MAX_RAND = 10; //max (non-inclusive) randomly chosen number (0-9)
const int SIMULATION_RUNS = 10000000; //The number of simulations to run.

//main() function
void main()
{
	//declare original array to hold random numbers.
	int firstSet[SET_SIZE];
	//create simulation array to test against firstSet
	int secondSet[SET_SIZE]; 
	
	//seed random number generator with time null.
    	srand(time(NULL));
	
	//Prime original array to avoid possible value conflicts
    	primeArray(firstSet, SET_SIZE);
    
	//Populate original array with 6 random, unique values 0-9
    	populate(firstSet, SET_SIZE);
    
    	cout << "***********************************************************\n";
    	cout << "*************    Lottery Number Simulation ****************\n";
    	cout << "***********************************************************\n";
    	cout << "\n\nThe original set against which the simulation will run is";
    	cout << " as follows:\n ";
    	displaySet(firstSet, SET_SIZE); 
    	cout << "\nNow running simulation for size: " << SIMULATION_RUNS;
    
    	//Function simulation to run tests against original array.
	simulation(firstSet, secondSet, SET_SIZE, SIMULATION_RUNS);
    
	//Pause system before closing
	system("Pause");
	
		
}// end of main()


/*****************************************************
* Function simulation():
* This function creates a second array of random numbers 
* to conduct tests against the original array.
* 
* During each iteration, the second array is tested against
* the original array in order to determine if there is a 
* type 1 match or a type 2 match; a count is kept of each.
* Returns void.
* Arguments accepted: Original array(first set)
*					  Size of array (size)
*					  Number of simulation runs (runs)
********************************************************/
void simulation(int firstSet[], int secondSet[], int size, int runs) 
{    
     
     double typeOneCount = 0; //declare variable to hold counts of type one.
     double typeTwoCount = 0; //declare variable to hold counts of type two.
     
     //Iterate for const number of runs
     for (int i = 0; i < runs; i++)
     {
		//prime array to avoid value conflicts 
        primeArray(secondSet, size);
	
		//populate array with 6 random numbers, 0-9
        populate(secondSet, size);
        
        //If there is a type one match with new array, increment type1 counter        
		if (typeOneMatch(firstSet, secondSet, size) == true)
			typeOneCount++;
        
		//If there is a type two match with new array, increment type2 counter
		if (typeTwoMatch(firstSet, secondSet, size) == true)
			typeTwoCount++; 
	  
     }//end for loop
     
	//Display the results of the simulation.
	cout << "\n\n********************************************\n";
   	cout << "\nThe simulation has now ended.\n\n";
	cout << "Number of type-one matches: " << typeOneCount << endl;
   	cout << "Number of type-two matches: " << typeTwoCount << endl;
	cout << "Percentage of type-one matches: " << setprecision(2) << (typeOneCount/runs)*100 << "%" << endl;
   	cout << "Percentage of type-two matches: " << setprecision(2) << (typeTwoCount/runs)*100 << "%" << endl;
   	cout << "\n\nEnd of program.\n\n";	 

}//End of function simulation()    


/*****************************************************
* Function primeArray():
* This function primes each array location with -1,
* a value that is outside of the value range of randomly
* selected numbers.  This ensures that when selecting for
* unique numbers to populate the array with, a coincidental
* value match does not occur.
* Returns void.
* Arguments accepted: Generic array (array)
*		      Size of array (size)
*					  
********************************************************/
void primeArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {    
         array[i] = -1;
    }

}//end of function primeArray()


/*****************************************************
* Function displaySet:
* This function display the value within each location 
* of a generic array.
* Returns void.
* Arguments accepted: Generic array (array)
*		      Size of array (size)
*					  
********************************************************/
void displaySet(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "\narray[" << i << "]:" << array[i] << endl;
	}

}//end of function displaySet()


/*****************************************************
* Function randGen():
* This function generates a random number between 0 and
* constant integer MAX_RAND, non-inclusive.
* Returns a value of type integer. 
* Arguments accepted: Generic array (array)
*		      Size of array (size)
*					  
********************************************************/
int randGen()
{
	return rand() % MAX_RAND;

}// end of randGen()


/*****************************************************
* Function populate():
* This function populates an array with unique random
* numbers. 
* Returns void. 
* Arguments accepted: Generic array (array)
*      		  	Size of array (size)
*					  
********************************************************/
void populate(int array[], int size)
{
   int randNum; //to hold generated random number for testing.
  
   //iterate over the array size n
   for (int i = 0; i < size; i++)
   {     
        bool test = true; //variable to test for random-number matches.
        
	//Continue calling random numbers and testing them until it is unique.
        while( test == true )
        { 	
		//store randomly generated number in ranNum
        	 randNum = randGen(); 
         
		//test the randomly generated number against original array
		//and store the yes/no result in test.
        	test = match(array, randNum, size);
		  
       	 }//end while statement
        
	//After validation, store the randNum in the array.
        array[i] = randNum;
   
    }//end for loop
   
}//end function populate()


/*****************************************************
* Function match():
* This function populates an array with unique random
* numbers. 
* Returns boolean value. 
* Arguments accepted: Generic array (array)
*			Random number to test (testNum)
*			Size of array (size)
*					  
********************************************************/
bool match(int array[], int testNum, int size)
{
	//iterate over array size n
	for( int i = 0; i < size; i++)
	{	
		//if value is the same as the test number, return true
        	if (array[i] == testNum)
			return true;
    	}
     
	//otherwise, return false
     	return false;

}//end function match()


/*****************************************************
* Function typeOneMatch():
* This function tests two arrays for a type one match.
* Each set must be the same in numbers and order.
* Returns type bool. 
* Arguments accepted: First generic array (array1)
*			Second generic array (array2)
*			Size of arrays; must be equal size (size)
*					  
********************************************************/
bool typeOneMatch(int arrayOne[], int arrayTwo[], int size)
{
     	//iterate over the array
	for (int i = 0; i < size; i++)
     	{
         	//if any value in location i doesn't match
		// return false.
		 if (arrayOne[i] != arrayTwo[i])
            		return false;
     	}
     
	 //otherwise, return true.
     	return true;

}//end of function typeOneMatch()


/*****************************************************
* Function typeTwoMatch():
* This function tests two arrays for a type-two match.
* The set of values must be the same, though without regard
* to order.
* Returns type bool. 
* Arguments accepted: First generic array (array1)
*					  Second generic array (array2)
*					  Size of arrays; must be equal size (size)
*					  
********************************************************/
bool typeTwoMatch(int arrayOne[], int arrayTwo[], int size)
{	
	//variable to track the number of values that match
     	int matchCount = 0;
	
	//iterate over arrayOne
     	for (int i = 0; i < size; i++)
     	{	 
		//iterate over arrayTwo
         	for (int j = 0; j < size; j++)
         	{
			// if values match, increment the value of counter
			if (arrayOne[i] == arrayTwo[j])
                		matchCount++;
            
         	}//end of nested loop
		 
     	}//end of for loop

	//If the number of matches is the same as the array sizes
	// a type-two match exists.
    	if (matchCount == size)
        	return true;
     	//otherwise, a match does not exist
	else 
        	return false;


}//end of function typeTwoMatch


                
                
                
                

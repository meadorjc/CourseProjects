/*****************************************************
*	Caleb Meador
*	COSC1437 GE#2 part 1, Fall, 2013
*	Filename:GE2part1MJ.cpp
*
********************************************************/
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

//function prototypes
void populate (int array[], int size);
int indexValue(int array[], int size);
int linearSearch(int array[], int size, int searchKey);
void selectionSort(int array[], int size);
int binarySearch(int array[], int size, int value);
void processSearchResults(double array[], int comparisons, int runCount);
void displaySearchResults(double array[]);
void displaySet(int array[], int size);
int randGen();
bool match(int array[], int testNum, int size);

//declare constants
const int SIZE = 1000;		//size of array
const int MAX_RAND = 9999;	//Maximum random number
const int RUNS = 1000;		//number of simulation runs

//for use in lSearchResultsArray() & bSearchResultsArray()
const int MIN = 0; 
const int AVG = 1;		
const int MAX = 2;		
const int TOTAL = 3;	



//main function
void main()
{
	int array[SIZE];
	double lSearchResultsArray[4] = {SIZE, 0, 0, 0};
	double bSearchResultsArray[4] = {SIZE, 0, 0, 0};


	//seed random number generator with time null.
    srand(time(NULL));

	printf("\n*****************Search Benchmarks Program*****************\n");
	printf("  Comparing LINEAR and BINARY search results\n");
	printf("\n\nNow populating array with 1000 elements ranging from 0 to 9999\n");
	printf("Once populated, a random index key will be chosen to find by \n");
	printf("linear and binary search. The program will display the efficiency\n");
	printf("of each one after 1000 simulated runs. \n\n");
	

	//iterate for n number of runs
	for (int i = 0; i < RUNS; i++)
	{
		//to hold results of linear & binary searches
		int lSearchResults, bSearchResults;

		//populate array
		populate(array, SIZE);
		
		//select a random key to search for
		int searchKey = indexValue(array, SIZE);

		//store the number of comparisons done by linear search
		lSearchResults = linearSearch(array, SIZE, searchKey);
		
		//sort the array
		selectionSort(array, SIZE);
		
		//store the number of comparisons done by binary search
		bSearchResults = binarySearch(array, SIZE, searchKey);
		//cout << endl << bSearchResults << endl;
		
		//process the results of both linear and binary search
		processSearchResults(lSearchResultsArray, lSearchResults, i+1);
		processSearchResults(bSearchResultsArray, bSearchResults, i+1);
	} /*end of n simulation runs*/

	//Display the accumulated results of linearSearch
	printf("\nAfter %d tests on %d element arrays, the linear search results were:\n", RUNS, SIZE);
	displaySearchResults(lSearchResultsArray);

	//Display the accumulated results of binarySearch
	printf("\nAfter %d tests on %d element arrays, the binary search results were:\n", RUNS, SIZE);
	displaySearchResults(bSearchResultsArray);

	//pause system to display output
	system("PAUSE");
		
}/* end of main() */

/*****************************************************
* Function randGen():
* This function generates a random number between 0 and
* constant integer MAX_RAND, non-inclusive.
* Returns a value of type integer. 
*
* Returns integer			  
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
* 
* Returns boolean value. 
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
* Function indexValue():
* Chooses a random index and returns the value.
* 
* Returns integer.
********************************************************/
int indexValue(int array[], int size)
{

	int randIndex = rand() % 999;

	return array[randIndex];

}/* end of indexValue() */

/*****************************************************
* Function linearSearch():
* Iterate through the array and test values until 
* a match is found.
* 
* Returns integer value. 
********************************************************/
int linearSearch(int array[], int size, int searchKey)
{
	int count = 0;

	for( int i = 0; i < size; i++)
	{
  		count++;
		if (searchKey == array[i])
			return count;
	}
}/*end of linearSearch() */

/*****************************************************
* Function selectionSort():
* Sort the array in ascending order.
* 
* Returns boolean value. 
********************************************************/
void selectionSort(int array[], int size)
{
	int startScan, minIndex, minValue;
	
	for (startScan = 0; startScan < size; startScan++)
	{
		
		minIndex = startScan;
		minValue = array[startScan];
		
		for(int index = startScan + 1; index < size; index++)
		{
			if (array[index] < minValue)
			{		
				minValue = array[index];
				minIndex = index;
			} //end if
		
		} //end for
	
		array[minIndex] = array[startScan];
		array[startScan] = minValue;
	
	}//end for
}// end selectionSort

/*****************************************************
* Function binarySearch():
* Search over array decreasing search range over each
* iteration
* 
* Returns integer value. 
********************************************************/
int binarySearch(int array[], int size, int value)
{
	int count = 0;

	int first = 0,
		last = size-1,
		middle,
		position = -1;
	bool found = false;

	while(!found && first <= last)
	{
		count++;

		middle = (first+last)/2;	//calc midpoint
		if (array[middle] == value)	//if value found at mid
		{
			found = true;
			position = middle;
			
		}
		else if (array[middle] > value) //if value is in lower half
			last = middle-1;
		else
			first = middle+1;	//if value is in upper half
	}
	
	return count;
}

/*****************************************************
* Function processSearchResults():
* Test for max and min values of search results.
* Accumulate search results for average.
* 
* Returns void. 
********************************************************/
void processSearchResults(double array[], int comparisons, int runCount)
{
	array[TOTAL] += comparisons;
	array[AVG] = array[TOTAL]/runCount;

	if (comparisons > array[MAX])
		array[MAX] = comparisons;

	if (comparisons < array[MIN])
		array[MIN] = comparisons;

}/* end processSearchResults()*/

/*****************************************************
* Function displaySearchResults():
* Display the results of the processed information.
* 
* Returns void. 
********************************************************/
void displaySearchResults(double array[])
{

	printf("\nThe minimum number of comparisons to find the key was: %5.0f", array[MIN]);
	printf("\nThe maximum number of comparisons to find the key was: %5.0f", array[MAX]);
	printf("\nThe average number of comparisons to find the key was: %5.1f\n", array[AVG]);
	
}
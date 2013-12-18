#include <iostream>
#include <string>
using namespace std;

//function prototypes
void processCommandLine(int argc, char * argv[], int &order);
void displayProgramUsageAndQuit(char *argv[]);
void getDataItems(unsigned int &size);
void ascSelectionSort(string** arr, unsigned int size);
void desSelectionSort(string** arr, unsigned int size);
void readDataLineFromCin(string &line);
void displaySizeAndPtrArray(string** ptrArray, unsigned int size);
string** allocateArrayOfStringPointers(unsigned int size);
string** updateArrayOfPointers(string** ptrArray, unsigned int index, string line);
string** sortArrayOfPointers(string** ptrArray, unsigned int size, int order);
void deleteDynamicMemory(string** ptrArray, unsigned int arraySize);


//constant variables
const int BAD_ARG = 0,
		  ASC_NAME = 1,
		  DES_NAME = 2;
const bool DEBUG = true;

//function main()
void main(int argc, char* argv[])
{
	int sortOrder = 0;			//command line argument
	unsigned int arraySize = 0; 		//size of array
	string line;				//name from input
	string* stringArray = NULL; 		//to generate dynamic string array
	string** ptrArray = NULL;   		//pointer to dynamically allocated string array
	
	//Process command-line input
	processCommandLine(argc, argv, sortOrder);
	
	
	
	//Get number of names entries from user or file
	getDataItems(arraySize);
	
	//Allocate an array of string pointers based number of name-entries
	ptrArray = allocateArrayOfStringPointers(arraySize);
	
	//Iterate through the names based on the size of the data set
	for (unsigned int i = 0; i < arraySize; i++){
		
		//Read one line of data (one name) and store in line
		readDataLineFromCin(line); 
		
		//Dynamically allocate memory to store name and assign its address
		//to the pointer array
		ptrArray = updateArrayOfPointers(ptrArray, i, line);
	
	}/* end for loop*/
	
	//Sort the array of pointers as per command-line arguments.
	ptrArray = sortArrayOfPointers(ptrArray, arraySize, sortOrder);

	//output the number of names and the names in the appropriate order
	displaySizeAndPtrArray(ptrArray, arraySize);

	//delete the dynamically allocated memory.
	deleteDynamicMemory(ptrArray, arraySize);
	
		
}/*end of main()*/


/*****************************************************
* Function processCommandLine():
* This function tests the command line arguments and 
* saves the sort order or signals a bad argument
*
* Returns void.
********************************************************/
void processCommandLine(int argc, char *argv[], int &order)
{
	
	if (argc == 2) {			//If there are 2 arguments, test them
		string param = argv[1]; 	//assign to string to test
		
		if (param == "asc")     	//ascending order
			order = ASC_NAME;
		else if (param == "des") 	//descending order
			order = DES_NAME;
		else 
			order = BAD_ARG;   	 //otherwise, its a bad argument
	}
	
	else					//if there are more or less than 2 arguments
		order = BAD_ARG;	    	//its a bad argument

	//Display error message and terminate program if commandline arguments are invalid
	if (order == BAD_ARG)
		displayProgramUsageAndQuit(argv);

	
}/*end processCommandLine() */

/*****************************************************
* Function displayProgramUsageAndQuit():
* This function displays an error function and quits
* the program when a bad argument is encountered.
*
* Returns void.
********************************************************/
void displayProgramUsageAndQuit(char *argv[])
{
			
	std::cerr << "\n********************************************" << std::endl;
	std::cerr << "\nNOTE: Program must be run from command-line\n";
	std::cerr << "\tin order to accept command-line arguments and\n";
	std::cerr << "\tindirection operators\n";
	std::cerr << "\nCOMMAND-LINE USAGE:\nNameDirectory {asc | desc}";
	std::cerr << " < [InputFile].txt > [OutputFile].txt" << std::endl;
	std::cerr << "\n\nProgram accepts intput in the following format: \n";
	std::cerr << "\n\t n names (unsigned integer)";
	std::cerr << "\n\t'name_1'";
	std::cerr << "\n\t'name_2'";
	std::cerr << "\n\t'...'";
	std::cerr << "\n\t'name_n'";
	std::cerr << "\n\n********************************************" << std::endl;

	system("PAUSE");
	
	exit(BAD_ARG);

}/*end displayProgramUsageAndQuit()  */

/*****************************************************
* Function getDataItems():
* This function gets the size of the list of names 
* from an input files or the user and stores it in a
* reference variable.
*
* Returns void.
********************************************************/
void getDataItems(unsigned int &size) 
{
	cin >> size;
	cin.ignore(); //clear extraneous whitespace
	
}/* end getDataItems() */	



/*****************************************************
* Function allocateArrayOfStringPointers():
* Dynamically allocates an array of string pointers of 
* size n to point to file input.
*
* Returns a pointer to a string pointer.
********************************************************/
string** allocateArrayOfStringPointers(unsigned int size)
{
	string** ptrToPtr = NULL;
	
	try {
		ptrToPtr = new string*[size];
	}
	
	catch (bad_alloc &param) {
		return NULL;
	}
	
	return ptrToPtr;

}/*end allocateArrayOfStringPointers() */

/*****************************************************
* Function readDataLineFromCin():
* Read a single line from input and store in string
*
* Returns void.
********************************************************/
void readDataLineFromCin(string &line)
{
	getline(cin, line);
		
}/* end readDataLineFromCin() */

/*****************************************************
* Function updateArrayOfPointers():
* Dynamically allocate a new string pointer
* to hold the value of each name from input.
*
* Returns pointer to a string pointer.
********************************************************/
string** updateArrayOfPointers(string** ptrArray, unsigned int index, string line)
{
	try {
		
		string* newString = new string;		//dynamically allocate memory
		*newString = line;			//store input name
        ptrArray[index] = newString;			//assign name-address to poitner array

		return ptrArray;
	}
	
	catch (bad_alloc &param) {
		cout << "bad_alloc";
		return NULL;
	}

}/*end of updateArrayOfPointers() */

/*****************************************************
* Function sortArrayOfPointers():
* Sort the array of string pointers as per command-line
* arguments of 'asc' for ascending or 'des for desceding.
*
* Returns pointer to a string pointer.
********************************************************/
string** sortArrayOfPointers(string** ptrArray, unsigned int size, int order)
{
	switch (order) {
		case 1 : ascSelectionSort(ptrArray, size); break;
		case 2 : desSelectionSort(ptrArray, size); break;
		default: ascSelectionSort(ptrArray, size); break;	
	}
	return ptrArray;

}/*end of sortArrayOfPointers*/

/*****************************************************
* Function ascSelectionSort():
* Sort the array of string pointers in ascending order
*
* Returns void.
********************************************************/
void ascSelectionSort(string** arr, unsigned int size)
{
	unsigned int startScan, minIndex;
	string* minValue;
	
	for (startScan = 0; startScan < size; startScan++)
	{
		minIndex = startScan;				//track index values
		minValue = &*arr[startScan];			//assign address to minvalue
		
		for(unsigned int index = startScan + 1; index < size; index++)
		{
			if (*arr[index] < *minValue)	 	//if name < min
			{		
				minValue = &*arr[index];	//store new addres in minValue
				minIndex = index;		//update index of minimum.
			} //end if
		
		} //end for
	
		arr[minIndex] = &*arr[startScan];		//switch addresses
		arr[startScan] = &*minValue;
	
	}//end for

}/*end ascSelectionSort() */

/*****************************************************
* Function desSelectionSort():
* Sort the array of string pointers in descending order
*
* Returns void.
********************************************************/
void desSelectionSort(string** arr, unsigned int size)
{
	unsigned int startScan, minIndex;
	string* minValue;
	
	for (startScan = 0; startScan < size; startScan++)
	{
		
		minIndex = startScan;
		minValue = &*arr[startScan];
		
		for(unsigned int index = startScan + 1; index < size; index++)
		{
			if (*arr[index] > *minValue)
			{		
				minValue = &*arr[index];
				minIndex = index;
			} //end if
		
		} //end for
	
		arr[minIndex] = &*arr[startScan];
		arr[startScan] = &*minValue;
	
	}//end for

}/*end desSelectionSort() */

/*****************************************************
* Function displaySizeAndPtrArray():
* Display the values of the array of string pointers
*
* Returns void.
********************************************************/
void displaySizeAndPtrArray(string** ptrArray, unsigned int size)
{
	cout << size;
	for (unsigned int i = 0; i < size; i++)
		cout << endl << **(ptrArray+i);

}/* end of displaySizeAndPtrArray */

/*****************************************************
* Function displaySizeAndPtrArray():
* Delete any dynamically allocated memory.
*
* Returns void.
********************************************************/
void deleteDynamicMemory(string** ptrArray, unsigned int size)
{
	for (unsigned int i = 0; i < size; i++)
		delete *(ptrArray+i);
	
	delete [] ptrArray;

}/* end of deleteDynamicMemory() */

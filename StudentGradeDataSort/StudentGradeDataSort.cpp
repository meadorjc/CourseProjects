/*****************************************************
*    Caleb Meador
*    COSC1437 GE#3 , Fall, 2013
*    Filename:StudentGradeDateSort.cpp
*    10/13/2013
*
********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <iomanip>
using namespace std;

//declare Student structure
struct Student
{
    char * namePtr;
    unsigned int score;
};

//function prototypes
void processCommandLine(int argc, char * argv[], int &order, int & item);
void displayProgramUsageAndQuit(char *argv[]);
void getDataItems(unsigned int &size);
void sortNameAscSelection(Student** arr, unsigned int size);
void sortScoreAscSelection(Student** arr, unsigned int size);
void sortNameDesSelection(Student** arr, unsigned int size);
void sortScoreDesSelection(Student** arr, unsigned int size);
void readDataLineFromCin(string &line);
void displaySizeAndPtrArrayName(Student** ptrArrayOfStructPtrs, unsigned int size);
Student** allocateArrayOfStructPointers(unsigned int size);
Student** updateArrayOfPointers(Student** ptrArrayOfStructPtrs, unsigned int index, string line);
Student** sortArrayOfPointersName(Student** ptrArrayOfStructPtrs, unsigned int size, int order);
Student** sortArrayOfPointersScore(Student** ptrArrayOfStructPtrs, unsigned int size, int order);
Student** sortByItem(Student** ptrArrayOfStructPtrs, unsigned int size, int order, int item);
void deleteDynamicMemory(Student** ptrArrayOfStructPtrs, unsigned int arraySize);
Student* processNameAndScore(string &line, Student *newStudent);


//constant variables
const int BAD_ARG = 0,  //bad command line argument
          ASC = 1, //flag for sort name ascending
          DES = 2, //flag for sort name descending
          NAME = 3,     //flag for name sort
          SCORE = 4;    //flag for score sort
const bool DEBUG = 0;   //for debug purposes

//function main()
void main(int argc, char* argv[])
{
    int sortOrder = 0;                  //command line arguments
    int sortItem = 0; 
    unsigned int arraySize = 0;         //size of array
    string line;                        //name from input
    
    Student** ptrArrayOfStructPtrs = NULL;  //pointer to dynamically allocated struct array
    


    //Process command-line input
    processCommandLine(argc, argv, sortOrder, sortItem);
    
    //Get number of names entries from user or file
    getDataItems(arraySize);
    
    //Allocate an array of pointers to struct pointers based number of name-entries
    ptrArrayOfStructPtrs = allocateArrayOfStructPointers(arraySize);
    
    //Iterate through the names based on the size of the data set
    for (unsigned int i = 0; i < arraySize; i++){
        
        //Read one line of data (one name & score) and store in line
        readDataLineFromCin(line); 
        
        //Dynamically allocate memory to store struct instance and assign its address
        //to the pointer array
        ptrArrayOfStructPtrs = updateArrayOfPointers(ptrArrayOfStructPtrs, i, line);
    
    }/* end for loop*/
    
    //Sort the array of pointers as per command-line arguments.
    ptrArrayOfStructPtrs = sortByItem(ptrArrayOfStructPtrs, arraySize, sortOrder, sortItem);

    //output the number of names and the names/score in the appropriate order
    displaySizeAndPtrArrayName(ptrArrayOfStructPtrs, arraySize);

    //delete the dynamically allocated memory.
    deleteDynamicMemory(ptrArrayOfStructPtrs, arraySize);
    
}/*end of main()*/


/*****************************************************
* Function processCommandLine():
* This function tests the command line arguments and 
* saves the sort order and items to sort by, 
* or signals a bad argument
*
* Returns void.
********************************************************/
void processCommandLine(int argc, char *argv[], int &order, int &item)
{
    
    if (argc == 3) {                //If there are 3 arguments, test them
        
        string param;
        
        for (int i = 1; i < argc; i++) {
            param = argv[i];                //convert to string; easier to test
            if (param == "asc")    
                order    = ASC;        //ascending order
            else if (param == "des")    
                order    = DES;        //descending order
            else if (param == "name")
                item    = NAME;             //item sorted by name
            else if (param == "score")    
                item    = SCORE;            //item sorted by score
            else
                order = BAD_ARG;            //otherwise, its a bad argument
            
        }
        //item should not include duplicates or conflicting orders/items
        if (item == order || item+order == 7 || item+order == 1 || item+order == 2)
            order = BAD_ARG;
            
    }
    
    else                    //if there are more or less than 3 arguments
        order = BAD_ARG;            //its a bad argument

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
        std::cerr << "\nNOTE: Program must be run on command-line or batch file" << std::endl;
        std::cerr << "to accept user arguments." << std::endl;
        std::cerr << "\nCOMMAND-LINE USAGE: 'GE3MJ [SORT-ORDER] [ITEM-ORDER]'" << std::endl;
        std::cerr << "\twhere [SORT-ORDER] is 'asc' or 'des'" << std::endl;
        std::cerr << "\tand [ITEM-ORDER] is 'name' or 'score'" << std::endl;
        std::cerr << "\tin any order." << std::endl;
        std::cerr << "\n\nProgram accepts intput in the following format: \n";
        std::cerr << "\n\t n names (unsigned integer)";
        std::cerr << "\n\t\"name_1\" XX";
        std::cerr << "\n\t\"name_2\" XX";
        std::cerr << "\n\t\"...\"";
        std::cerr << "\n\t\"name_n\" XX";
        std::cerr << "\n\n********************************************" << std::endl;

        
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
* Function allocateArrayOfStructPointers():
* Dynamically allocates an array of struct pointers of 
* size n to point to file input.
*
* Returns a pointer to a struct pointer.
********************************************************/
Student** allocateArrayOfStructPointers(unsigned int size)
{
    Student** ptrToStruct = NULL;
    

    try {
        ptrToStruct = new Student*[size]();
    }
    
    catch (bad_alloc &param) {
        cout << "MEMORY ALLOCATION ERROR!";
        return NULL;
    }
    
    return ptrToStruct;

}/*end allocateArrayOfStructPointers() */

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

/******************************************************
* Function processNameAndScore():
* Process line from input file into an array of characters 
* holding a name and unsigned int holding score.
* The array of characters is dynamically allocated and is
* pointed to by namePtr in structure instance
* Returns a pointer to a student.
*******************************************************/
Student* processNameAndScore(string &line, Student *newStudent)
{
    int lineSize = line.length();

    char* tempName = NULL;
    char* tempScore = NULL;

    try { 
        tempName = new char[lineSize]();   //temporary input holder     
        tempScore = new char[lineSize]();
    }
    catch (bad_alloc &param) {
        cout << "\nMEMORY ALLOCATION ERROR!\n";
        return NULL;
    }

    int count = 0;
    int index = 1;                              //skip first char '"'
        
        //store chars in temp array until " encountered
        while (line[index] != 34) {             //34 is ascii code for '"'
            tempName[index-1] = line[index];    //start @ tempName[0]; 
            index++;                            //increment after assignment
        }
            
        tempName[index] = NULL;                //set final position to null
        
        if(DEBUG) cout << "\nLength of name: " << index;
        
        //collect score after name
        while (index < lineSize) {               //continue through string.
            if (isdigit(line[index]))
                tempScore[count++] = line[index];
            index++;
        }

    //pointer to student name
    char* dynamicChar;
        
    try {
        dynamicChar = new char[strlen(tempName)+2]();    //copy # of chars + null space
        
    }
    catch (bad_alloc &param) {
        cout << "Bad alloc";
        return NULL;
    }

    strncpy(dynamicChar, tempName, strlen(tempName));    //copy only the chars to new space
    
    //store name in student struct
    newStudent->namePtr = dynamicChar;                            
    
    //set final position to NULL char
    newStudent->namePtr[strlen(tempName)] = NULL;

    if(DEBUG) cout << "\nLength of dynamic char: " << strlen(dynamicChar);
    
    //convert score to integer and store in struct
    newStudent->score = atoi(tempScore);
    
    
    delete [] tempName, tempScore;

    return newStudent;
}


/*****************************************************
* Function updateArrayOfPointers():
* Dynamically allocate a new struct pointer
* to hold the value of each name and score from input.
*
* Returns pointer to a struct pointer.
********************************************************/
Student** updateArrayOfPointers(Student** ptrArrayOfStructPtrs, unsigned int index, string line)
{
    try {
        //dynamically allocate new struct memory
        Student *newStudent = new Student;    
        
        //process name and score and return address of processed struct to array
        ptrArrayOfStructPtrs[index] = processNameAndScore(line, newStudent);
    }
    
    catch (bad_alloc &param) {
        cout << "ERROR IN MEMORY ALLOCATION!";
        return NULL;
    }
    
    return ptrArrayOfStructPtrs;

}/*end of updateArrayOfPointers() */

/*********************************************************************************
* sortByItem()
* Determine whether to sort by name or score based on command-line arguments.
*
*Returns pointer to student pointer
*********************************************************************************/
Student** sortByItem(Student** ptrArrayOfStructPtrs, unsigned int size, int order, int item)
{   
    //Sort name or item as per user's command-line args.
    switch(item) {
    case NAME : { sortArrayOfPointersName(ptrArrayOfStructPtrs, size, order); break; }
    case SCORE : { sortArrayOfPointersScore(ptrArrayOfStructPtrs, size, order); break;}
    default: { sortArrayOfPointersName(ptrArrayOfStructPtrs, size, order); break; }
    }

    return ptrArrayOfStructPtrs;
}//end sortByItem()

/*****************************************************
* Function sortArrayOfPointersName():
* Sort the array of string pointers as per command-line
* arguments of 'asc' for ascending or 'des for desceding
* for names.
*
* Returns pointer to a struct pointer.
********************************************************/
Student** sortArrayOfPointersName(Student** ptrArrayOfStructPtrs, unsigned int size, int order)
{   
    //Sort name in ascending or descending order according to user's command-line args.
    switch (order) {
        case ASC : sortNameAscSelection(ptrArrayOfStructPtrs, size); break;
        case DES : sortNameDesSelection(ptrArrayOfStructPtrs, size); break;
        default: sortNameAscSelection(ptrArrayOfStructPtrs, size); break;    
    }
    return ptrArrayOfStructPtrs;

}/*end of sortArrayOfPointersName()*/


/*****************************************************
* Function sortArrayOfPointersScore():
* Sort the array of string pointers as per command-line
* arguments of 'asc' for ascending or 'des for desceding
* for scores
* 
* Returns pointer to a struct pointer.
********************************************************/
Student** sortArrayOfPointersScore(Student** ptrArrayOfStructPtrs, unsigned int size, int order)
{
    //Sort score in ascending or descendign order according to user's command-line args.
    switch (order) {
        case ASC : sortScoreAscSelection(ptrArrayOfStructPtrs, size); break;
        case DES : sortScoreDesSelection(ptrArrayOfStructPtrs, size); break;
        default: sortScoreAscSelection(ptrArrayOfStructPtrs, size); break;    
    }
    return ptrArrayOfStructPtrs;

}/*end of sortArrayOfPointersScore()*/

/*****************************************************
* Function sortNameAscSelectionSort():
* Sort the array of struct pointers in ascending order
* by name.
*
* Returns void.
********************************************************/
void sortNameAscSelection(Student** arr, unsigned int size)
{
    unsigned int startScan, minIndex;
    Student* minValue;
        
    for (startScan = 0; startScan < size; startScan++)
    {
        minIndex = startScan;                //track index values
        minValue = &*arr[startScan];         //assign address to minvalue
        
        for(unsigned int index = startScan + 1; index < size; index++)
        {
            if (strcmp(arr[index]->namePtr, minValue->namePtr) < 0)//if name < min
            {        
                minValue = &*arr[index];    //store new addres in minValue
                minIndex = index;           //update index of minimum.
            } //end if
        
        } //end for
    
        arr[minIndex] = &*arr[startScan];        //switch addresses
        arr[startScan] = &*minValue;
    
    }//end for

}/*end ascNameAscSelectionSort() */

/*****************************************************
* Function ascSelectionSortScore():
* Sort the array of string pointers in ascending order
* by score.
*
* Returns void.
********************************************************/
void sortScoreAscSelection(Student** arr, unsigned int size)
{
    unsigned int startScan, minIndex;
    Student* minValue;
    
    for (startScan = 0; startScan < size; startScan++)
    {
        minIndex = startScan;                //track index values
        minValue = &*arr[startScan];         //assign address to minvalue
        
        for(unsigned int index = startScan + 1; index < size; index++)
        {
            if (arr[index]->score < minValue->score)//if score < min
            {        
                minValue = &*arr[index];    //store new addres in minValue
                minIndex = index;           //update index of minimum.
            } //end if
        
        } //end for
    
        arr[minIndex] = &*arr[startScan];        //switch addresses
        arr[startScan] = &*minValue;
    
    }//end for

}/*end ascSelectionSortScore() */


/*****************************************************
* Function sortNameDesSelectionSort():
* Sort the array of string pointers in descending order
* by name.
*
* Returns void.
********************************************************/
void sortNameDesSelection(Student** arr, unsigned int size)
{
    unsigned int startScan, minIndex;
    Student* minValue;
      
    for (startScan = 0; startScan < size; startScan++)
    {
        minIndex = startScan;                //track index values
        minValue = &*arr[startScan];         //assign address to minvalue
        
        for(unsigned int index = startScan + 1; index < size; index++)
        {
            if (strcmp(arr[index]->namePtr, minValue->namePtr) > 0)     //if name < min
            {        
                minValue = &*arr[index];    //store new addres in minValue
                minIndex = index;           //update index of minimum.
            } //end if
        
        } //end for
    
        arr[minIndex] = &*arr[startScan];        //switch addresses
        arr[startScan] = &*minValue;
    
    }//end for

}/*end sortNameDesSelectionSort() */

/*****************************************************
* Function sortScoreDesSelectionSort():
* Sort the array of string pointers in descending order
* by score.
*
* Returns void.
********************************************************/
void sortScoreDesSelection(Student** arr, unsigned int size)
{
    unsigned int startScan, minIndex;
    Student* minValue;
    
    for (startScan = 0; startScan < size; startScan++)
    {
        minIndex = startScan;                        //track index values
        minValue = &*arr[startScan];                 //assign address to minvalue
        
        for(unsigned int index = startScan + 1; index < size; index++)
        {
            if (arr[index]->score > minValue->score)//if score < min
            {        
                minValue = &*arr[index];            //store new addres in minValue
                minIndex = index;                   //update index of minimum.
            } //end if
        
        } //end for
    
        arr[minIndex] = &*arr[startScan];                //switch addresses
        arr[startScan] = &*minValue;
    
    }//end for
}/*end sortScoreDesSelectionSort() */

/*****************************************************
* Function displaySizeAndPtrArrayName():
* Display the processed information in appropriate order.
*
* Returns void.
********************************************************/
void displaySizeAndPtrArrayName(Student **ptrArrayOfStructPtrs, unsigned int size)
{
    cout << size << endl;
    for (unsigned int i = 0; i < size; i++) {
        int length = strlen(ptrArrayOfStructPtrs[i]->namePtr);
        
        ptrArrayOfStructPtrs[i]->namePtr[length] = '\"';
        ptrArrayOfStructPtrs[i]->namePtr[length+1] = NULL;
        
        cout << left << "\"" << setw(30) << ptrArrayOfStructPtrs[i]->namePtr;
        cout << ptrArrayOfStructPtrs[i]->score << endl;
        
        ptrArrayOfStructPtrs[i]->namePtr[length] = NULL;
        
    }//end for
}/* end of displaySizeAndPtrArrayName */


/*****************************************************
* Function deleteDynamicMemory():
* Delete any dynamically allocated memory.
*do
* Returns void.
********************************************************/
void deleteDynamicMemory(Student** ptrArrayOfStructPtrs, unsigned int size)
{
    for(unsigned int i = 0; i < size; i++) {
        delete ptrArrayOfStructPtrs[i]->namePtr;     //delete address of namePtr
        delete ptrArrayOfStructPtrs[i];             //delete address of struct
    }

    delete [] ptrArrayOfStructPtrs;                //delete array of struct pointers

}/* end of deleteDynamicMemory() */

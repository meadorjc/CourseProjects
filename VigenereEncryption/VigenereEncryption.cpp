/*****************************************************
*	Caleb Meador
*	COSC1437 GE#4 , Fall, 2013
*	Filename:VigenereEncryption.cpp
*	10/22/2013
*   Updated 12/17/2013
********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <iomanip>
#include <fstream>

using namespace std;

//potential sources of errors
enum ErrorSource {KEY_FILE, 
                  IN_FILE, 
                  BAD_CMD_LINE, 
                  NO_ERROR}; 

//command line arguments that are allowed
enum AllowedArgumentsType { EXPECT_OPTION, 
                            ENCRYPT, 
                            DECRYPT, 
                            EXPECT_PLAIN_FILE, 
                            EXPECT_CIPHER_FILE, 
                            EXPECT_KEY_FILE};

const int MAX_CHARS = 26;		    //only 26 letters in the alphabet
const int MAX_KEY_LENGTH = 1024;	//password can only be 1024 letters

struct CommandLineInfo {
	ErrorSource error;		//holds error code of first error encountered or noError
	string keyFile;			//name of password-file 
	string plainTextFile;		//name of plain-text file
	string cipherTextFile;		//name of cipher-text file
	char mode;			        //e = encrypt or d = decrypt
};

struct OpenFileInfo {
	ErrorSource error;		//holds error code of first error encountered or noError
	char mode;			    //encrypt or decrypt
	ifstream keyFile;		//password file-object
	ifstream inFile;		//plain text file or cipher text file-object
	ofstream outFile;		//plain text file or cipher text file-object
	int fileLength;

};

void displayProgramUsageAndQuit(char *argv[], int errorElement, CommandLineInfo *cmdLnArgs);
void createVigenereSquare(char alphaArr[][MAX_CHARS]);
void displayVigenereSquare(char alphaArr[][MAX_CHARS]);
void processCommandLine(int argc, char *argv[], CommandLineInfo *cmdLnArgs);
void openFile(CommandLineInfo *cmdLnArgs, OpenFileInfo *file);
void displayFileErrorAndQuit(OpenFileInfo *file, CommandLineInfo* cmdLnArgs);
void deleteMemoryAndCloseFiles(OpenFileInfo *file, char* keyArray);
char* createKeyArray(OpenFileInfo *file, char* keyArray, int &keyLength, CommandLineInfo* cmdLnArgs);
char getCharacterFromFile(OpenFileInfo *file, CommandLineInfo* cmdLnArgs);
char getNextCipherKeyCharacter(char tempRow, char* keyArray, int keyLength, char alphaArr[][MAX_CHARS]);
char getNextKeyCharacter(char* keyArray, int keyLength);
char getNextPlainTextChar(char tempChar, char* keyArray, int keyLength);


void main(int argc, char *argv[]) {

	char alphaArr[MAX_CHARS][MAX_CHARS];    //vigenere 2D array
	char* keyArray = NULL;			        //ptr to array of chars
	int keyLength = 0;			            //length of key
	
	
	//Initialize command-line struct data
	CommandLineInfo commandLineArgs = {NO_ERROR, 
                                       "password.txt", 
                                       "plaintext.txt", 
                                       "ciphertext.txt", 
                                       'x'}; 
	OpenFileInfo file;                  //struct to hold file info
	ErrorSource error = NO_ERROR;       //datatype to hold error info
	
    //process argc and argv arguments from commandline
	processCommandLine(argc, argv, &commandLineArgs);
	
    //open respective input/output files
	openFile(&commandLineArgs, &file);
    
    //create 2D array populated with normal cipher values. See readme.txt
	createVigenereSquare(alphaArr);

	//displayVigenereSquare(alphaArr); /*for testing*/
	
    //Creates a char array to hold the cipher key for translation
	keyArray = createKeyArray(&file, keyArray, keyLength, &commandLineArgs);
	
    char tempChar;  //hold input char for processing
    
	//state function for encryption/decryption
	switch(commandLineArgs.mode) {
		case ENCRYPT: {
			for(int i = 0; i < file.fileLength; i++) {
                
                //get 1 plaintext char
				tempChar = getCharacterFromFile(&file, &commandLineArgs);   
				
                //translate plaintext to encoded char
                tempChar = getNextCipherKeyCharacter(tempChar, keyArray, keyLength, alphaArr); 
				
                //write to file
                file.outFile.write((char*)&tempChar, 1);
			}		
			break;	
		}
		case DECRYPT :{ 
			for(int i = 0; i < file.fileLength; i++) {

                //get 1 encrypted char
                tempChar = getCharacterFromFile(&file, &commandLineArgs);
				
                //translate to plaintext
                tempChar = getNextPlainTextChar(tempChar, keyArray, keyLength);
				
                //write to file
                file.outFile.write((char*)&tempChar, 1);
			}
			break;
		}
	}
    
    //erase dynamically allocated memory
	deleteMemoryAndCloseFiles(&file, keyArray);

}

void processCommandLine(int argc, char *argv[], CommandLineInfo *cmdLnArgs)
{
	AllowedArgumentsType state = EXPECT_OPTION;
	char ch;
    
    //state machine for command-line arguments
	for(int arg = 1; arg < argc; arg++) {
		switch(state) {
			case EXPECT_OPTION : {
				
				if(argv[arg][0] != '-') { 
					cmdLnArgs->error = BAD_CMD_LINE; 
					return; 
				}
				
				ch = argv[arg][1];
				
				switch (ch) {
					//ENCRYPT MODE --------------------
                    case 'e':case'E':{
						cmdLnArgs->mode = ENCRYPT;
						continue;
					}
					//DECRYPT MODE --------------------
                    case 'd':case 'D': {
						cmdLnArgs->mode = DECRYPT;
						continue;
					}
					//EXPECT_PLAIN_FILE ----------------
                    case 'p': case 'P':{
						state = EXPECT_PLAIN_FILE;
						continue;
					}
					// EXPECT_CIPHER_FILE ---------------
                    case 'c': case 'C': {
						state = EXPECT_CIPHER_FILE;
						continue;
					}
					// EXPECT_KEY_FILE ------------------
                    case 'k': case 'K': {
						state = EXPECT_KEY_FILE;
						continue;
					}
					// BAD_CMD_LINE ----------------------
                    default: {
						cmdLnArgs->error = BAD_CMD_LINE;
						displayProgramUsageAndQuit(argv, arg, cmdLnArgs);
					}
				}/*end nested switch*/
			}/*end expect_option*/
            //EXPECT_PLAIN_FILE ---------------------------
            case EXPECT_PLAIN_FILE : {
				if (strlen(argv[arg]) > 2) 
					cmdLnArgs->plainTextFile = argv[arg];
				else arg--;
				state = EXPECT_OPTION; //expect another option
				continue;
			}
			//EXPECT_CIPHER_FILE ---------------------------
            case EXPECT_CIPHER_FILE : {
				if (strlen(argv[arg]) > 2) 
					cmdLnArgs->cipherTextFile = argv[arg];
				else arg--;
				state = EXPECT_OPTION; //expect another option
				continue;
			}
			//EXPECT_KEY_FILE ---------------------------
            case EXPECT_KEY_FILE : {
				if (strlen(argv[arg]) > 2) 
					cmdLnArgs->keyFile = argv[arg];
				else arg--;
				state = EXPECT_OPTION; //expect another option
				continue;
			}
			default: {
				cmdLnArgs->error = BAD_CMD_LINE;
				displayProgramUsageAndQuit(argv, arg, cmdLnArgs);
			}
		}/*end switch*/
	}/*end for-loop */
	
	//If mode was never changed from initial state, flag an error
    if( cmdLnArgs->mode == 'x') {
		cmdLnArgs->error = BAD_CMD_LINE;
	}
    
    //If any error occurred, display error msg and quit
	if(cmdLnArgs->error != NO_ERROR) 
		displayProgramUsageAndQuit(argv, BAD_CMD_LINE, cmdLnArgs);

}

//Function displays error message when bad cmd-line argument is encountered.
void displayProgramUsageAndQuit(char *argv[], int errorElement, CommandLineInfo *cmdLnArgs)
{
  std::cerr << "\n*******************************************************************" << std::endl;
  std::cerr << "\n\nNOTE: Program must be run from command-line to accept arguments.\nv\n" << std::endl;
  //test for presence of -e or -d first; only required arguments
  std::cerr << "\nCOMMAND-LINE ERROR: [";
	if(cmdLnArgs->mode == 'x') 
	  std::cerr << "Must enter '-e' or '-d']";
	else 
	  std::cerr << argv[errorElement] << "] argument not allowed.\n\n";
  std::cerr << "\nUSAGE:GE4MJ -e/-d -k [file-name] -p [file-name] -c [file-name]\n" << std::endl;
  std::cerr << "\t-e : encrypt from plain-text to cipher-text" << std::endl;
  std::cerr << "\t-d : decrypt from cipher-text to plain-text\n\t\t(either -e or -d required)\n" << std::endl;
  std::cerr << "\t-k : specify name of text-file containing cipher password \n\t\t(optional; default: password.txt)\n" << std::endl;
  std::cerr << "\t-p : specify name of text-file containing plain-text \n\t\t(optional; default: plaintext.txt)\n\n";
  std::cerr << "\t-c : specify name of text-file containting cipher-text \n\t\t(optional; default: ciphertext.txt)\n\n";
  std::cerr << "\t Arguments may be in any order, except filenames, \n\twhich must directly follow the corresponding command.";		
  std::cerr << "\n\n*******************************************************************" << std::endl;
		
  exit(BAD_CMD_LINE);

}/*end displayProgramUsageAndQuit()  */

//Create a 2D array of alphabetic cipher characters (see readme.txt)
void createVigenereSquare(char alphaArr[][MAX_CHARS])
{
	int row, col;
	char rowStartChar = 'A';
	char ch; 		
	
	for (row = 0; row < MAX_CHARS; row++) {
		ch = rowStartChar;
		
		for (col = 0; col < MAX_CHARS; col++){
			if (ch > 'Z') ch = 'A';
			alphaArr[row][col] = ch;
			ch++;
		}
		rowStartChar++;			
	}
}
//Display 2D cipher table for debug purposes
void displayVigenereSquare(char alphaArr[][MAX_CHARS])
{
	cout << endl;
	for (int row = 0; row < MAX_CHARS; row++) {
		for (int col = 0; col < MAX_CHARS; col++) 
			cout << alphaArr[row][col] << " ";
		cout << endl;
	}
}
//Open appropriate files depending on ENCRYPT or DECRYPT MODE
void openFile(CommandLineInfo *cmdLnArgs, OpenFileInfo *file)
{ 
	//Key-file always ifstream
    file->keyFile.open(cmdLnArgs->keyFile.c_str(), ios::in|ios::binary);
		printf("\tOpening key-file: \t\t%s\n", cmdLnArgs->keyFile.c_str());
    
    //If we are encrypting, input file is plaintext file, output file is ciphertextfile
	if (cmdLnArgs->mode == ENCRYPT){
		file->inFile.open(cmdLnArgs->plainTextFile.c_str(), ios::in|ios::binary);
		file->outFile.open(cmdLnArgs->cipherTextFile.c_str(), ios::out|ios::binary);
		printf("\tOpening plain-file for input: \t%s\n", cmdLnArgs->plainTextFile.c_str());
		printf("\tOpening cipher-file for output: %s\n", cmdLnArgs->cipherTextFile.c_str());
	}
    //Otherwise, if we are decrypting, input file is ciphertext file, output file is plaintext
	else if (cmdLnArgs->mode == DECRYPT) {
		file->inFile.open(cmdLnArgs->cipherTextFile.c_str(), ios::in|ios::binary);
		file->outFile.open(cmdLnArgs->plainTextFile.c_str(), ios::out|ios::binary);
		printf("\tOpening cipher-file for input: \t%s\n", cmdLnArgs->cipherTextFile.c_str());
		printf("\tOpening plain-text for output: %s\n", cmdLnArgs->plainTextFile.c_str());
	}
    
    //whichever mode we're in, get the filelength
	if (file->inFile.is_open()) {
		file->inFile.seekg(0L, ios::end);
		file->fileLength = file->inFile.tellg();
		file->inFile.seekg(0L, ios::beg);
	}
}

//Creates a char array to hold the cipher key for translation purposes
char* createKeyArray(OpenFileInfo *file, char* keyArray, int &keyLength, CommandLineInfo* cmdLnArgs)
{
	char tempChar;      //temp read-in  
	int fileLength;     //length of key-file
	char* tempPassword;


	if (file->keyFile.is_open()) {
		
		file->keyFile.seekg(0L, ios::end);      //set file pointer to eof
		fileLength = file->keyFile.tellg();     //return position of pointer as file length
		file->keyFile.seekg(0L, ios::beg);	    //return pointer to beginning of file
		
        
		try{ tempPassword = new char[fileLength](); }   //allocate char array with file-size # elements
		catch (bad_alloc &param) { cout << "\nMEMORY ALLOCATION ERROR!\n"; return NULL; }
			
        //loop through file while i is less than file-lenght and key is less than 1024    
		for (int i = 0; i < fileLength && keyLength < MAX_KEY_LENGTH; i++) {
			
            //get the next char
            tempChar = file->keyFile.get();
            
            //if its an alpha-char, save in array
			if (isalpha(tempChar)) {
				tempPassword[keyLength] = tempChar;
				keyLength++;
			}
		}

		//reallocate to new key size
		try{ keyArray = new char[keyLength+1]; }
		catch (bad_alloc &param){ cout << "\nMEMORY ALLOCATION ERROR!\n"; return NULL; }
		
        //copy key to fitted array
		for (int i = 0; i < keyLength; i++)
			keyArray[i] = tempPassword[i];
		
		keyArray[keyLength] = '\0';	//add null terminator(but not used)

		delete [] tempPassword;
	}
    //if file isn't open
	else {
		file->error = KEY_FILE;
		displayFileErrorAndQuit(file, cmdLnArgs);
	}
	return keyArray;
}
//Get a character from the input file
char getCharacterFromFile(OpenFileInfo* file, CommandLineInfo* cmdLnArgs)
{
	char tempChar;	
	static int count = 0;

	if (file->inFile.is_open())
		tempChar =  file->inFile.get();
	else {
		file->error = IN_FILE;	
		displayFileErrorAndQuit(file, cmdLnArgs);
	}
	return tempChar;

}
//If there is a file-error, display error message and quit
void displayFileErrorAndQuit(OpenFileInfo *file, CommandLineInfo* cmdLnArgs)
{
	std::cerr << "\n*******************************************************************" << std::endl;

	if(file->error == KEY_FILE)
		std::cerr << "\nProblem opening key-file; please ensure that " << cmdLnArgs->keyFile << " is available.\n\n";
	
	if(file->error == IN_FILE) {
		if(cmdLnArgs->mode == ENCRYPT)
		std::cerr << "\nProblem opening input-file; please ensure that " << cmdLnArgs->plainTextFile<< " is available.\n\n";
		if(cmdLnArgs->mode == DECRYPT)
		std::cerr << "\nProblem opening input-file; please ensure that " << cmdLnArgs->cipherTextFile<< " is available.\n\n";
	}
	std::cerr << "\n*******************************************************************" << std::endl;

	exit(0);
}
//translate cipher/plain text character to encoded/decoded char (depends on mode)
char getNextCipherKeyCharacter(char tempRow, char* keyArray, int keyLength, char alphaArr[][MAX_CHARS])
{
	char returnChar;
	
    //if the char is alphabetic, encode it
	if (isalpha(tempRow)) {
		//get corresponding key character 
        char tempCol = getNextKeyCharacter(keyArray, keyLength);
        
        //2D Array translation
        //convert to upper-case, translate, and return lowercase
		if (islower(tempRow)) { 
			tempRow = toupper(tempRow); 
			returnChar = tolower(alphaArr[tempRow-65][tempCol-65]);
		}
		//if already upper-case, translate
        else returnChar = alphaArr[tempRow-65][tempCol-65];
	}
	//otherwise, return it without translating
    else
		returnChar = tempRow;

	return returnChar;
}
//Get the plaintext char's corresponding key-char
char getNextKeyCharacter(char* keyArray, int keyLength)
{
	static int count = -1;
	
	if (count == keyLength-1)
		count = -1;
	count++;
	
	return keyArray[count];
}
//Get the next plaintext character from inputfile
char getNextPlainTextChar(char tempChar, char* keyArray, int keyLength)
{
	char returnChar;
    
    //Algebraic method
    //If its alphabetic, process it
	if (isalpha(tempChar)) {
		char tempCol = getNextKeyCharacter(keyArray, keyLength);
		
        //if its lower-case, change to upper for processing, return to lower
		if (islower(tempChar)) {
			tempChar = toupper(tempChar);
			returnChar = tolower(((((tempChar<tempCol)? tempChar+26 : tempChar)-tempCol) % 26)+65);
		}
		else
			returnChar = ((((tempChar<tempCol)? tempChar+26 : tempChar)-tempCol) % 26)+65;
	
	}
	//otherwise just return it
    else	
		returnChar = tempChar;

	return returnChar;
}
//Delete dynamic memory 
void deleteMemoryAndCloseFiles(OpenFileInfo *file, char* keyArray)
{
	file->keyFile.close();
	file->inFile.close();
	file->outFile.close();

	cout << "\n\tClosing files.\n";

	delete [] keyArray;
}
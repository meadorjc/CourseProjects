/*****************************************************
*  Caleb Meador
*  COSC1437 GE#6 , Fall, 2013
*  Filename:GE6Test.cpp
*  12/05/2013
*
********************************************************/
#define _CRT_SECURE_NO_WARNINGS
      
#include <iostream>
#include <fstream> /*  for file stream objects        */
#include <iomanip> /*  for setw and setfill           */
#include <string>  /*  for anything to do with Strings    */
#include <iostream>/*  for everything else          */
#include <map>   //map string values to enum
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <sys/stat.h>/*file sys info for file checking */
#include "Bitmap.h"
#include "StegoBitmap.h"

using namespace std;

bool DEBUG = 0;


enum ExpectedStates {  
  EXPECT_NEW_DEFAULT = 0,    
  EXPECT_COMMAND,        
  EXPECT_ROW_COL,        
  EXPECT_ROW,          
  EXPECT_COL,          
  EXPECT_COLOR,        
  EXPECT_RED_VAL,        
  EXPECT_GREEN_VAL,      
  EXPECT_BLUE_VAL,      
  EXPECT_ALPHA_VAL,      
  EXPECT_FILE_NAME,    
  EXPECT_QUIT,        
  EXPECT_UNKNOWN,      
  MOD_ROW_COL,         
  EXPECT_EXTENSION,      
  EXPECT_NOTHING  };    

enum StringValues { 
  DEFAULT = 100,        //"default"
  CREATE_BMP_DEFAULT,   // "createDefaultBitmapObject"
  CREATE_BMP_FROM_FILE, // "createBitmapObjectFromBMPFile"
  CREATE_STEGO_DEFAULT, // "hideFileInBMPFile"
  CREATE_STEGO_FROM_FILE,// "createDefaultStegoBitmapObject"
  HIDE_BMP_FILE,     // "createStegoBitmapObjectFromBMPFile"
  GET_HIDDEN_FILE,   // "retrieveFileFromBMPFile"
  DELETE_OBJ,        // "deleteObject"
  INSERT,            // "insert"
  DELETE,            // "delete"
  MODIFY,            // "modify"
  WRITE,             // "write"
  QUIT,              // "quit"
  ROW,               // "row"
  COL,               // "col"
  RED,               // "r"
  GREEN,             // "g"
  BLUE,              // "b"
  ALPHA,             // "a"
  ERROR,             // error flag
  BLANK              // blank flag
  };

  
struct ErrorType 
{ 
  bool errorFlag;
  bool missingDefaultColor;
  bool missingColValue;
  bool missingRowValue;
  bool missingRowOrColType; 
  bool maxRowSize;
  bool maxColSize;
  bool unknownColorType;
  bool unknownCmdOrVal;
  bool unknownCmd;
  bool defaultColorErrorType;
  bool unknownRowOrColType;
  bool rowErrorVal;
  bool colErrorVal;
  bool modifyRowOrColMissing;
  bool emptyString;
  bool negativeNumber;
  bool invalidColorVal;
  bool blankLine; 
  bool missingOutFileName;
  bool missingColorValues;
};

 struct CommandInfo {
  StringValues command;
  int editRow;
  int editCol;
  int writeCount;
  bool editRowTest;
  bool editColTest;
  bool modLoc;    //modify specific row and col
  bool getHiddenFile;
  bool hideBMPFile;
  bool createBMP;
  bool createStego;
  bool createStegoFromFile;
  bool createBMPFromFile;
  bool writeFile;
  bool stegoBMP;

 };
  
 struct FileInfo {
  char readLine[80];        
  ifstream readFile;
  ofstream outFile;
  string fileName;
  string outFileName;
  string inFileName;
  string fileToHideName;
  bool newDefaultOutFileName;
  int fileArgc;
  char** fileArgv;
  int mainLoopIndex;
  bool writtenToFile;

 };

//Map commands from command file to enumerated values and back
static std::map<std::string, StringValues> s_mapStringValues;
static std::map<StringValues, std::string> s_mapEnumValuesToString;
static std::map<ExpectedStates, std::string> s_mapExpectedStatesToString;

/*display prototypes*/
void displayConvertedCommands(FileInfo* file);
void displayErrorStatus(ErrorType* error);
void displayVectorGrid(FileInfo* file);
void displayCommandLineInfo(CommandInfo* cmd);
void displayFatalErrorMessage(Bitmap* bmp, ErrorType* error, FileInfo* file);
void displayFatalErrorMessage(StegoBitmap* stegoBmp, ErrorType* error, FileInfo* file);
void displayFileInfo(FileInfo* file);

void initializeFileValues(FileInfo* file);
void initializeStringMap();
void initializeEnumMap();
void initializeExpectedStatesMap();

/*set defaults*/
void setDefaultErrorStatus(ErrorType* error);
void setDefaultLocationValues(CommandInfo* commandInfo, int mainLoopIndex);

/*process args */  
void processConsoleArgs(int &argc, char* argv[], FileInfo* file);
void processCommandLine(Bitmap* bmp, CommandInfo* commandInfo, FileInfo* file, ErrorType* error);
void processCommandLine(StegoBitmap* stegoBmp, CommandInfo* commandInfo, FileInfo* file, ErrorType* error);
void editBitmap(Bitmap* bmp, FileInfo* file, CommandInfo* cmd, ErrorType* error);
void editBitmap(StegoBitmap* stegoBmp, FileInfo* file, CommandInfo* cmd, ErrorType* error);

/*validation*/
void checkFileExists(FileInfo* file);
void convertCommandToArgv(FileInfo *file, ErrorType* error);
void validateColor(Bitmap* bitmap, ErrorType* error, int* anyDefault, int* anyColor, int* num);
void validateColor(StegoBitmap* stegoBmp, ErrorType* error, int* anyDefault, int* anyColor, int* num);
void validateRowCol(CommandInfo* cmd, ErrorType* error, ExpectedStates* state, int* cmdRowCol, int* numRowCol, bool* genError, int* num, bool* rowColTest);
bool isBlankLine(FileInfo* file);
void validateColorCount(bool* newDefault, ExpectedStates* state, int* colorCount);

/*maintenance*/
void freeDynamicallyAllocatedArgv(FileInfo *file);
void closeFiles(FileInfo* file);
void quitProgram(FileInfo* file );

void main(int argc, char* argv[]) {
  
  FileInfo file;
  ErrorType  error;
  CommandInfo commandInfo;   //user arguments
  Bitmap* bmp = NULL;        //to be dynamically allocated later
  StegoBitmap* stegoBmp = NULL;       //declared as stego to access either class; to be dynamically allocated later

  //Initializations and defaults
  setDefaultLocationValues(&commandInfo, file.mainLoopIndex);
  initializeFileValues(&file);
  initializeStringMap();
  initializeEnumMap();
  initializeExpectedStatesMap();
  setDefaultErrorStatus(&error); 
  
  
  cout << "\nWelcome to the BMP file interpreter:";
  cout << "\nAccepted Console commands: ge5 [user textfile].txt [RET]";
  cout << "\n\nAccepted File commands:";
  cout << setw(15) << right <<"\n\nSet new default color:" 
       << "\n\tdefault r [0-255] g [0-255] b [0-255] a [0-255] (use ALL)";
  cout << setw(15) << right << "\n\nInsert new row or col:" 
       << "\n\tinsert [row]/[col] [#] r [0-255] g [0-255] b [0-255] a [0-255]";
  cout << setw(15) << right << "\n\t\tNOTE: colors optional." 
       << " If omitted, replaced by default values.";
  cout << setw(15) << right << "\n\nDelete a row or col:" 
       << "\n\tdelete [row]/[col] [#] (use all)";
  cout << setw(15) << right << "\n\nModify location:" 
       << "\n\tmod [row] [#] [col] [#] r [0-255] g [0-255] b [0-255] a [0-255]";
  cout << setw(15) << right << "\n\t\tNOTE: colors optional." 
       << " If omitted, replaced by value of 255 (default color)";
  cout << setw(15) << right << "\n\nWrite image to file:" 
       << "\n\twrite [user bmp file-name].bmp";
  cout << setw(15) << right << "\n\nQuit:" << "\n\tquit\n\n";

  processConsoleArgs(argc, argv, &file);
  
  checkFileExists(&file);

  file.readFile.getline(file.readLine, 80);
  
  //track file read progress for error handling
  file.mainLoopIndex = 0;
  
  //main processing loop
  do {
      cout << "\n\t\t[" << file.mainLoopIndex << "]: " << file.readLine; 
      
      //translate commandfile commands to mock argv
      convertCommandToArgv(&file, &error);
  
      //displayConvertedCommands(&file); //for testing
    
    //Process STEGO object commands ONLY
    if (commandInfo.stegoBMP == true) {
      processCommandLine(stegoBmp, &commandInfo, &file, &error);
    
      //WARNING: massive debug output
      if (DEBUG) { 
        displayCommandLineInfo(&commandInfo);
        displayFileInfo(&file);              
        if (commandInfo.createBMP         == true ||
            commandInfo.createBMPFromFile   == true ||
            commandInfo.createStego         == true ||
            commandInfo.createStegoFromFile == true) {
          cout << dec;
          stegoBmp->displayColorInfo();
          stegoBmp->displayVectorGrid();
          cout << hex;
          stegoBmp->displayHeaders();
        }
      }
      //execute commands
      editBitmap(stegoBmp, &file, &commandInfo, &error);
      
      //display any error messages
      displayFatalErrorMessage(stegoBmp, &error, &file);  
  
    }
    //Otherwise, process the standard bitmap object
    else { 
  
      //translate commandfile commands to mock argv
      processCommandLine(bmp, &commandInfo, &file, &error);
      
      //WARNING: massive debug output
      if (DEBUG) {
        cout << dec;
        displayCommandLineInfo(&commandInfo);
        displayFileInfo(&file);
        if (commandInfo.createBMP           == true ||
            commandInfo.createBMPFromFile   == true ||
            commandInfo.createStego         == true ||
            commandInfo.createStegoFromFile == true) {
          cout << dec;
          bmp->displayColorInfo();
          bmp->displayVectorGrid();
          cout << hex;
          bmp->displayHeaders();
        }
      }
      
      //execute commands
      editBitmap(bmp, &file, &commandInfo, &error);
      
      //display any error messages
      displayFatalErrorMessage(bmp, &error, &file);  
    }
  
    //decide object to dynamically create
    try {
      if(commandInfo.createBMP == true)
        bmp = new Bitmap();
      if(commandInfo.createBMPFromFile == true)
        bmp = new Bitmap(file.inFileName);
      if(commandInfo.createStego == true)
        stegoBmp = new StegoBitmap();
      if(commandInfo.createStegoFromFile == true)
        stegoBmp = new StegoBitmap(file.inFileName);
    }
    catch (bad_alloc &param)
    {
      cout << "\n\n\t\tMemory allocation error!\n";
    }
      
    file.mainLoopIndex += 1;
    
    //reset values for next read-line
    setDefaultErrorStatus(&error);
    setDefaultLocationValues(&commandInfo, file.mainLoopIndex);
    
    //get next line from file to process
    file.readFile.getline(file.readLine, 80);
    
  }while(!file.readFile.eof());   /*  end while if the EOF is reached  */
  
  
  freeDynamicallyAllocatedArgv(&file);
  
  closeFiles(&file);
    
  if (!file.writtenToFile) 
    cout << "\n\n\tNote: no write command encountered. Exiting without writing to file."; 
  if (commandInfo.command == QUIT)  
    cout << "\n\n\tQuit option selected.";
  else
    cout << "\n\n\tEnd-of-file reached.";
  
  cout << "\n\tThe program will now end.\n";
  cout << "\tThank you.\n\n";


}//end of main

//display definitions - debug
void displayFileInfo(FileInfo* file)
{
  cout << endl << endl << "FileInfo: \n";
  cout << "fileName: "       << file->fileName << endl;
  cout << "inFileName: "     << file->inFileName << endl;
  cout << "outFileName: "    << file->outFileName << endl;
  cout << "fileToHideName: " << file->fileToHideName << endl;
  cout << "newDefaultOutFileName: " << file->newDefaultOutFileName << endl;
  cout << "fileArgc: "       << file->fileArgc << endl;
  cout << "fileArgv: "       << file->fileArgv << endl;
  cout << "mainLoopIndex: "  << file->mainLoopIndex << endl;
  cout << "writtenToFile: "  << file->writtenToFile << endl;

}

//debug
void displayConvertedCommands(FileInfo* file)
{
  cout << "\n\n\tParsed:\t\t";
    
  for(int i = 0; i < file->fileArgc; i++)
    cout << file->fileArgv[i] << " ";
  cout << endl;
}

//debug
void displayCommandLineInfo(CommandInfo* cmd)
{
  cout << endl;
  cout << setw(10) << "\ncmd->command:"    
       << setw(6)  << s_mapEnumValuesToString[cmd->command] << " address " 
       << setw(6)  << &s_mapEnumValuesToString[cmd->command];
  cout << setw(10) << "\ncmd->editRow:"    
       << setw(4)  << cmd->editRow << " address " 
       << setw(4)  << &cmd->editRow;
  cout << setw(10) << "\ncmd->editCol:"    
       << setw(4)  << cmd->editCol << " address " 
       << setw(4)  << &cmd->editCol;
  cout << setw(10) << "\ncmd->editRowTest:"  
       << setw(4)  << cmd->editRowTest << " address " 
       << setw(4)  << &cmd->editRowTest;
  cout << setw(10) << "\ncmd->editColTest:"  
       << setw(4)  << cmd->editColTest << " address " 
       << setw(4)  << &cmd->editColTest;
  cout << setw(10) << "\ncmd->modLoc:"    
       << setw(4)  << cmd->modLoc << " address " 
       << setw(4)  << &cmd->modLoc;    //modify specific row and col
  cout << setw(10) << "\ngetHiddenFile:" 
       << setw(4)  << cmd->getHiddenFile << " address "
       << setw(4)  << &cmd->getHiddenFile;
  cout << setw(10) << "\nhideBMPFile:" 
       << setw(4)  << cmd->hideBMPFile << " address "
       << setw(4)  << &cmd->hideBMPFile;
  cout << setw(10) << "\ncreateStegoFromFile:" 
       << setw(4)  << cmd->createStegoFromFile << " address "
       << setw(4)  << &cmd->createStegoFromFile;
  cout << setw(10) << "\ncreateBMPFromFile:" 
       << setw(4)  << cmd->createBMPFromFile << " address "
       << setw(4)  << &cmd->createBMPFromFile;
  cout << setw(10) << "\nwriteFile:" 
       << setw(4)  << cmd->writeFile << " address "
       << setw(4)  << &cmd->writeFile;
  cout << setw(10) << "\nstegoBMP:" 
       << setw(4)  << cmd->stegoBMP << " address "
       << setw(4)  << &cmd->stegoBMP;
  cout << setw(10) << "\nwriteCount:" 
       << setw(4)  << cmd->writeCount<< " address "
       << setw(4)  << &cmd->writeCount;
};


//debug
void displayErrorStatus(ErrorType* error)
{
  cout << endl << endl;
  cout << "errorFlag " << boolalpha << error->errorFlag << endl;
  cout << "missingDefaultColor " << boolalpha << error->missingDefaultColor << endl;
  cout << "missingColValue " << boolalpha << error->missingColValue << endl;
  cout << "missingRowValue " << boolalpha << error->missingRowValue << endl;
  cout << "missingRowOrColType " << boolalpha << error->missingRowOrColType << endl; 
  cout << "maxRowSize " << boolalpha << error->maxRowSize << endl;
  cout << "maxColSize " << boolalpha << error->maxColSize << endl;
  cout << "unknownColorType " << boolalpha << error->unknownColorType << endl;
  cout << "unknownCmdOrVal "  << boolalpha << error->unknownCmdOrVal << endl;
  cout << "unknownCmd " << boolalpha << error->unknownCmd << endl;
  cout << "defaultColorErrorType "<< boolalpha << error->defaultColorErrorType << endl;
  cout << "unknownRowOrColType " << boolalpha << error->unknownRowOrColType << endl;
  cout << "rowErrorVal " << boolalpha << error->rowErrorVal << endl;
  cout << "colErrorVal " << boolalpha << error->colErrorVal << endl;
  cout << "modifyRowOrColMissing "<< boolalpha << error->modifyRowOrColMissing << endl;
  cout << "emptyString " << boolalpha << error->emptyString << endl;
  cout << "negativeNumber " << boolalpha << error->negativeNumber << endl;
  cout << "invalidColorVal " << boolalpha << error->invalidColorVal << endl;
  cout << "blankLine  " << boolalpha << error->blankLine << endl; 
  cout << "missingOutFileName " << boolalpha << error->missingOutFileName << endl;
  cout << "missingColorValues " << boolalpha << error->missingColorValues << endl;
  cout << endl << endl;

}

void displayFatalErrorMessage(Bitmap* bmp, ErrorType* error, FileInfo* file)
{ 
    
  if (error->missingColorValues  == true )
    cout << "\n\t\t\t(DEFAULT COLOR applied: missing/invalid type or value)" << endl;
  
  if (error->missingDefaultColor  == true ||
    error->missingColValue        == true ||
    error->missingRowValue        == true ||
    error->missingRowOrColType    == true || 
    error->maxRowSize             == true ||
    error->maxColSize             == true ||
    error->unknownColorType       == true ||
    error->unknownCmdOrVal        == true ||
    error->unknownCmd             == true ||
    error->defaultColorErrorType  == true ||
    error->unknownRowOrColType    == true ||
    error->rowErrorVal            == true ||
    error->colErrorVal            == true ||
    error->modifyRowOrColMissing  == true ||
    error->emptyString            == true ||
    error->negativeNumber         == true ||
    error->invalidColorVal        == true ||
    error->blankLine              == true || 
    error->missingOutFileName     == true )
      error->errorFlag = true;

  
  if (error->errorFlag == true) {

  cout << "\n\n ***********************************************************************************";
  cout << "\n\tAn error has occurred on line " << file->mainLoopIndex << ":\n";
  if (!error->blankLine && !error->emptyString)
    cout << "\n\tCommand: " << *file->fileArgv << endl;
  if (error->missingDefaultColor == true) 
    cout << "\n\tMissing Default Color \n\t\t(Use all: r [0-255] g [0-255] b [0-255] a [0-255])";
  if (error->unknownColorType == true) 
    cout << "\n\tUnknown color type \n\t\t(Use any: r [0-255] g [0-255] b [0-255] a [0-255])";
  if (error->unknownCmdOrVal == true) 
    cout << "\n\tUnknown command or value entered" ;
  if (error->unknownCmd == true) 
    cout << "\n\tUnknown command entered \n\t\t(Use any: default, insert, delete, modify, write, or quit)";
  if (error->defaultColorErrorType == true) 
    cout << "\n\tUnknown color type included in default value \n\t\t(Use all: r [0-255] g [0-255] b [0-255] a [0-255])";
  if (error->unknownRowOrColType == true) 
    cout << "\n\tUnknown row or column type (Use: row or col)" ;
  if (error->rowErrorVal == true) 
    cout << "\n\tUnknown row value \n\t\t(Use: row [0-" << bmp->totalRowCount-1 << "])" ;
  if (error->colErrorVal == true) 
    cout << "\n\tUnknown column value \n\t\t(Use: col [0-" << bmp->totalColCount-1 << "])" ;
  if (error->modifyRowOrColMissing == true) 
    cout << "\n\tBoth the row and column must be specified in any order after modify: " 
       <<"\n\t\t(Use: modify col [0-" << bmp->totalColCount-1 << "] row [0-" << bmp->totalColCount-1 << "])" ;
  if (error->missingColValue == true) 
    cout << "\n\tMissing column value \n\t\t(Use: col [0-" << bmp->totalColCount-1 << "])" ;
  if (error->missingRowValue == true) 
    cout << "\n\tMissing row value \n\t\t(Use: row [0-" << bmp->totalRowCount-1 << "])" ;
  if (error->maxRowSize == true) 
    cout << "\n\tMaximum number of rows added: 20" ;
  if (error->maxColSize == true)
    cout << "\n\tMaximum number of columns added: 20" ;
  if (error->missingRowOrColType == true)
    cout << "\n\tInsert or Delete command must be followed by 'row' or 'col' \n\t(Use: insert [row/col] [0-" << bmp->totalRowCount-1 << "])";
  if(error->negativeNumber == true)
    cout << "\n\tNote: A negative number may not be used";
  if(error->invalidColorVal == true)
    cout << "\n\nInvalid color detected: \n\t\t (Use any: r [0-255] g [0-255] b [0-255] a [0-255])";
  if(error->missingOutFileName == true)
    cout << "\n\t\t*Missing output file name parameter (Use write [out-file-name.bmp]";


  if (DEBUG) displayErrorStatus(error);
  if (DEBUG) system("Pause");

  cout << "\n\n ***********************************************************************************";
  cout << endl << endl;
  }
}

void displayFatalErrorMessage(StegoBitmap* stegoBmp, ErrorType* error, FileInfo* file)
{ 
  if (error->missingColorValues  == true )
    cout << "\n\t\t\t(DEFAULT COLOR applied: missing/invalid type or value)" << endl;
  
  if (error->missingDefaultColor == true ||
    error->missingColValue       == true ||
    error->missingRowValue       == true ||
    error->missingRowOrColType   == true || 
    error->maxRowSize            == true ||
    error->maxColSize            == true ||
    error->unknownColorType      == true ||
    error->unknownCmdOrVal       == true ||
    error->unknownCmd            == true ||
    error->defaultColorErrorType == true ||
    error->unknownRowOrColType   == true ||
    error->rowErrorVal           == true ||
    error->colErrorVal           == true ||
    error->modifyRowOrColMissing == true ||
    error->emptyString           == true ||
    error->negativeNumber        == true ||
    error->invalidColorVal       == true ||
    error->blankLine             == true || 
    error->missingOutFileName    == true )
      error->errorFlag           = true;

  
  if (error->errorFlag == true) {

   cout << "\n\n ***********************************************************************************";
   cout << "\n\tAn error has occurred on line " << file->mainLoopIndex << ":\n";
   if (!error->blankLine && !error->emptyString)
     cout << "\n\tCommand: " << *file->fileArgv << endl;
   if (error->missingDefaultColor == true) 
     cout << "\n\tMissing Default Color \n\t\t(Use all: r [0-255] g [0-255] b [0-255] a [0-255])";
   if (error->unknownColorType == true) 
     cout << "\n\tUnknown color type \n\t\t(Use any: r [0-255] g [0-255] b [0-255] a [0-255])";
   if (error->unknownCmdOrVal == true) 
     cout << "\n\tUnknown command or value entered" ;
   if (error->unknownCmd == true) 
     cout << "\n\tUnknown command entered \n\t\t(Use any: default, insert, delete, modify, write, or quit)";
   if (error->defaultColorErrorType == true) 
     cout << "\n\tUnknown color type included in default value \n\t\t(Use all: r [0-255] g [0-255] b [0-255] a [0-255])";
   if (error->unknownRowOrColType == true) 
     cout << "\n\tUnknown row or column type (Use: row or col)" ;
   if (error->rowErrorVal == true) 
     cout << "\n\tUnknown row value \n\t\t(Use: row [0-" << stegoBmp->totalRowCount-1 << "])" ;
   if (error->colErrorVal == true) 
     cout << "\n\tUnknown column value \n\t\t(Use: col [0-" << stegoBmp->totalColCount-1 << "])" ;
   if (error->modifyRowOrColMissing == true) 
      cout << "\n\tBoth the row and column must be specified in any order after modify: " 
      <<"\n\t\t(Use: modify col [0-" << stegoBmp->totalColCount-1 << "] row [0-" << stegoBmp->totalColCount-1 << "])" ;
   if (error->missingColValue == true) 
     cout << "\n\tMissing column value \n\t\t(Use: col [0-" << stegoBmp->totalColCount-1 << "])" ;
   if (error->missingRowValue == true) 
     cout << "\n\tMissing row value \n\t\t(Use: row [0-" << stegoBmp->totalRowCount-1 << "])" ;
   if (error->maxRowSize == true) 
     cout << "\n\tMaximum number of rows added: 20" ;
   if (error->maxColSize == true)
     cout << "\n\tMaximum number of columns added: 20" ;
   if (error->missingRowOrColType == true)
     cout << "\n\tInsert or Delete command must be followed by 'row' or 'col' \n\t(Use: insert [row/col] [0-" << stegoBmp->totalRowCount-1 << "])";
   if(error->negativeNumber == true)
     cout << "\n\tNote: A negative number may not be used";
   if(error->invalidColorVal == true)
     cout << "\n\nInvalid color detected: \n\t\t (Use any: r [0-255] g [0-255] b [0-255] a [0-255])";
   if(error->missingOutFileName == true)
     cout << "\n\t\t*Missing output file name parameter (Use write [out-file-name.bmp]";
 
 
   if (DEBUG) displayErrorStatus(error);
   if (DEBUG) system("Pause");
 
   cout << "\n\n ***********************************************************************************";
   cout << endl << endl;
  }
}

//validate definitions
void validateColor(Bitmap* bitmap, ErrorType* error, int* anyDefault, int* anyColor, int* num)
{
  //if the color isn't negative...
  if (error->negativeNumber != true) {
    //and the command != DEFAULT...
    if (bitmap->defaultColor.newDefault == true)  //only when command: default
      //And its between 0-255
      if(*num >= 0 && *num <= 255)  
        //then store the number
        *anyDefault = *num;
      else  
      //otherwise, its invalid
      error->invalidColorVal = true;
    else  
      if (*num >= 0 && *num <= 255)  
        //if command != DEFAULT and its from 0-255, store it;
        *anyColor = *num;
      else  
        //otherwise its invalid
        error->invalidColorVal = true;
  }
  else 
    error->invalidColorVal = true;
}/*end validateColor(bmp)*/

void validateColor(StegoBitmap* stegoBmp, ErrorType* error, int* anyDefault, int* anyColor, int* num)
{
  //if the color isn't negative...
  if (error->negativeNumber != true) {
    //and the command != DEFAULT...
    if (stegoBmp->defaultColor.newDefault == true)  //only when command: default
      //And its between 0-255
      if(*num >= 0 && *num <= 255)  
        //then store the number
        *anyDefault = *num;
      else  
      //otherwise, its invalid
      error->invalidColorVal = true;
    else  
      if (*num >= 0 && *num <= 255)  
        //if command != DEFAULT and its from 0-255, store it;
        *anyColor = *num;
      else  
        //otherwise its invalid
        error->invalidColorVal = true;
  }
  else 
    error->invalidColorVal = true;
}/*end validateColor(stegoBmp)*/


//Checksum for default color values
void validateColorCount(bool* newDefault, ExpectedStates* state, int* colorCount)
{
  if (*newDefault)
    *state = EXPECT_NEW_DEFAULT ;
  else if (*colorCount < 5)
    *state = EXPECT_COLOR;
  else 
    *state = EXPECT_UNKNOWN; 
}

//generic row & column validator  : see comment below for passed values
//   validateRowCol(commandInfo,         error,          &state, &cmd->editRow/Col, &file->numRows, &error->col/rowErrorVal, &num, &editRow/ColTest);
void validateRowCol(CommandInfo* cmd, ErrorType* error, ExpectedStates* state, int* cmdRowCol, int* numRowCol, bool* valError, int* num, bool* rowColTest)
{
  if (DEBUG) cout << "\nvalidateRowCol: " << *numRowCol << " " << *num << " " 
          << error->negativeNumber << endl;
  //Can insert up to 20 total rows
  if (*numRowCol < 20 ) {
  //[0 - Current Size] && !(-)
    if ( *num <= *numRowCol && *num >= 0 && error->negativeNumber != true) 
      *cmdRowCol = *num;
    else {  
      cmd->command = ERROR;
      *valError = true;  
  } //generic error; whatever is passed to function
        
    //sentinal, else num copied to col on omission
    *num = -1;            
    *state = EXPECT_COLOR;
  }
  //Can delete even if 20
  else if (*numRowCol == 20 && cmd->command == DELETE) {
    //[0 - Current Size] && !(-)
    if (*num <= *numRowCol && *num >= 0 && error->negativeNumber != true) 
      *cmdRowCol  = *num;
    else {  
      cmd->command = ERROR;
      *valError = true;  
  } //generic error; whatever is passed to function
    //sentinal, else num duplicated to col on omission
    *num = -1;            
    *state = EXPECT_NOTHING;
  }
  //Can modify up to the 20th row
  else if (*numRowCol == 20 && cmd->command == MODIFY ) {
    //[0 - Current Size] && !(-)
    if (*num <= *numRowCol && *num >= 0 && error->negativeNumber != true) 
      *cmdRowCol  = *num;
    else {  
      cmd->command = ERROR;
      *valError = true;  
  } //generic error; whatever is passed to function
        
    //sentinal, else num duplicated to col on omission
    *num = -1;            
    *state = EXPECT_COLOR;
  }  
  else {
    cmd->command = ERROR;
    error->maxRowSize  = (cmd->command == ROW ) ? true : false;
    error->maxColSize  = (cmd->command == ROW ) ? true : false;
  }

  //test modify flag and that row & col haven't been assigned
  if (cmd->modLoc == true &&  (cmd->editCol == -1 || cmd->editRow == -1))
    *state = EXPECT_ROW_COL; 
      
  //flag to mark assignment
  *rowColTest = true;
  
}

//If file doesn't exist, opening will cause fatal error.
void checkFileExists(FileInfo* file)  
{
  struct stat fileInfo;
  
  if (stat(file->fileName.c_str(), &fileInfo) == 0)
    file->readFile.open(file->fileName.c_str(), ios::in);    
  else {
    cout <<"\n\tWARNING: Command-file name parameter from console not found.";
    cout <<"\n\tTerminating program due to fatal error.\n";
    exit(0);
  }

  cout << "\n\tOpening command file: " << file->fileName << "\n\tProcessing command lines->->->" << endl;
}

//Test file to see if blank before reading
bool isBlankLine(FileInfo* file) 
{
  for (unsigned int i = 0; i < strlen(file->readLine); i++)
    if (isalnum(file->readLine[i]))
      return false;

  return true;
}


//reset all errors
void setDefaultErrorStatus(ErrorType* error)
{
  error->errorFlag            = false;
  error->missingDefaultColor  = false;
  error->missingColValue      = false;
  error->missingRowValue      = false;
  error->missingRowOrColType  = false; 
  error->maxRowSize           =false;
  error->maxColSize           =false;
  error->unknownColorType     = false;
  error->unknownCmdOrVal      = false;
  error->unknownCmd           = false;
  error->defaultColorErrorType= false;
  error->unknownRowOrColType  = false;
  error->rowErrorVal          = false;
  error->colErrorVal          = false;
  error->modifyRowOrColMissing= false;
  error->emptyString          = false;
  error->negativeNumber       = false;
  error->invalidColorVal      = false;
  error->blankLine            = false; 
  error->missingOutFileName   = false;
  error->missingColorValues   = false;
}

void setDefaultLocationValues(CommandInfo* commandInfo, int mainLoopIndex)
{  
  commandInfo->editRow     = -1;
  commandInfo->editCol     = -1;
  commandInfo->modLoc      = false;
  commandInfo->editRowTest = false;
  commandInfo->editColTest = false;
  commandInfo->getHiddenFile = false;
  commandInfo->hideBMPFile = false;
  commandInfo->createBMP   = false;
  commandInfo->createStego = false;
  commandInfo->createStegoFromFile = false;
  commandInfo->createBMPFromFile = false;
  commandInfo->writeCount  = 0;
  commandInfo->writeFile   = false;

  if(mainLoopIndex < 1)
    commandInfo->stegoBMP = 0;
  //commandInfo->newBMP = false; special case...cannot be reset once set.
}

//initialize functions
void initializeFileValues(FileInfo* file)
{
  file->fileName     = "";
  file->outFileName  = "";
  file->inFileName   = "";
  file->fileToHideName = "";
  file->newDefaultOutFileName = false;
  file->writtenToFile  = false;
  file->mainLoopIndex  = 0;

}

//Map string arguments from file to enum states
void initializeStringMap() 
{
  s_mapStringValues["default"]                      = DEFAULT;
  s_mapStringValues["createDefaultBitmapObject"]    = CREATE_BMP_DEFAULT;
  s_mapStringValues["createBitmapObjectFromBMPFile"]= CREATE_BMP_FROM_FILE;
  s_mapStringValues["hideFileInBMPFile"]            = HIDE_BMP_FILE; 
  s_mapStringValues["createDefaultStegoBitmapObject"] = CREATE_STEGO_DEFAULT;
  s_mapStringValues["createStegoBitmapObjectFromBMPFile"] = CREATE_STEGO_FROM_FILE;
  s_mapStringValues["retrieveFileFromBMPFile"]            = GET_HIDDEN_FILE;
  s_mapStringValues["deleteObject"] = DELETE_OBJ; 
  s_mapStringValues["insert"]       = INSERT;
  s_mapStringValues["delete"]       = DELETE;
  s_mapStringValues["modify"]       = MODIFY;
  s_mapStringValues["write"]        = WRITE;
  s_mapStringValues["quit"]         = QUIT;
  s_mapStringValues["default"]      = DEFAULT;
  s_mapStringValues["row"]          = ROW;
  s_mapStringValues["col"]          = COL;
  s_mapStringValues["r"]            = RED;
  s_mapStringValues["g"]            = GREEN;
  s_mapStringValues["b"]            = BLUE;
  s_mapStringValues["a"]            = ALPHA;  
  s_mapStringValues["error"]        = ERROR;

}

//Map states to strings for debug purposes.
void initializeEnumMap() 
{
  s_mapEnumValuesToString[DEFAULT]      = "default";
  s_mapEnumValuesToString[CREATE_BMP_DEFAULT] = "createDefaultBitmapObject";
  s_mapEnumValuesToString[CREATE_BMP_FROM_FILE]= "createBitmapObjectFromBMPFile";
  s_mapEnumValuesToString[HIDE_BMP_FILE]    = "hideFileInBMPFile"; 
  s_mapEnumValuesToString[CREATE_STEGO_DEFAULT]= "createDefaultStegoBitmapObject";
  s_mapEnumValuesToString[CREATE_STEGO_FROM_FILE]= "createStegoBitmapObjectFromBMPFile";
  s_mapEnumValuesToString[GET_HIDDEN_FILE]= "retrieveFileFromBMPFile";
  s_mapEnumValuesToString[DELETE_OBJ] = "deleteObject"; 
  s_mapEnumValuesToString[INSERT]   = "insert";
  s_mapEnumValuesToString[DELETE]   = "delete";
  s_mapEnumValuesToString[MODIFY]   = "modify";
  s_mapEnumValuesToString[WRITE]    = "write";
  s_mapEnumValuesToString[QUIT]     = "quit";
  s_mapEnumValuesToString[DEFAULT]  = "default";
  s_mapEnumValuesToString[ROW]      = "row";
  s_mapEnumValuesToString[COL]      = "col";
  s_mapEnumValuesToString[RED]      = "r";
  s_mapEnumValuesToString[GREEN]    = "g";
  s_mapEnumValuesToString[BLUE]     = "b";
  s_mapEnumValuesToString[ALPHA]    = "a";
  s_mapEnumValuesToString[ERROR]    = "error";
}

//Map states to strings for debug purposes.
void initializeExpectedStatesMap()
{
  s_mapExpectedStatesToString[EXPECT_NEW_DEFAULT] = "EXPECT_NEW_DEFAULT";
  s_mapExpectedStatesToString[EXPECT_COMMAND]     = "EXPECT_COMMAND";
  s_mapExpectedStatesToString[EXPECT_ROW_COL]     = "EXPECT_ROW_COL";
  s_mapExpectedStatesToString[EXPECT_ROW]         = "EXPECT_ROW";
  s_mapExpectedStatesToString[EXPECT_COL]         = "EXPECT_COL";
  s_mapExpectedStatesToString[EXPECT_COLOR]       = "EXPECT_COLOR";
  s_mapExpectedStatesToString[EXPECT_RED_VAL]     = "EXPECT_RED_VAL";
  s_mapExpectedStatesToString[EXPECT_GREEN_VAL]   = "EXPECT_GREEN_VAL";
  s_mapExpectedStatesToString[EXPECT_BLUE_VAL]    = "EXPECT_BLUE_VAL";
  s_mapExpectedStatesToString[EXPECT_ALPHA_VAL]   = "EXPECT_ALPHA_VAL";
  s_mapExpectedStatesToString[EXPECT_FILE_NAME]   = "EXPECT_FILE_NAME";
  s_mapExpectedStatesToString[EXPECT_QUIT]        = "EXPECT_QUIT";
  s_mapExpectedStatesToString[EXPECT_UNKNOWN]     = "EXPECT_UNKNOWN";
  s_mapExpectedStatesToString[MOD_ROW_COL]        = "MOD_ROW_COL";
  s_mapExpectedStatesToString[EXPECT_EXTENSION]   = "EXPECT_EXTENSION";
  s_mapExpectedStatesToString[EXPECT_NOTHING]     = "EXPECT_NOTHING";

}

//process and conversion functions
void convertCommandToArgv(FileInfo *file, ErrorType* error)
{
  //If there is no line, return an error   
  if(strlen(file->readLine) == 0) {  
    error->emptyString = true;
    return;
  }

  //If blank line, return an error.
  if(isBlankLine(file)) {
    error->blankLine = true;
    return;
  }
  
  char* tempCopy;               //hold command line          
  unsigned int delimiters = 0;           
  unsigned int i = 0;                

  //if the look hasn't excuted, memory conflict occurs at delete attempt
  if (file->mainLoopIndex > 1) { 
    freeDynamicallyAllocatedArgv(file);
  }
  
  try { tempCopy = new char[strlen(file->readLine) + 1](); }
  catch (bad_alloc &param) { 
    cout << "\nBAD MEMORY ALLOCATION\n";
    return NULL; 
  }
  
  strncpy( tempCopy, file->readLine, strlen(file->readLine)+1);
  
  //test initial character to confirm command
  if (isalpha(file->readLine[0])){  
    delimiters++; 
    i = 1; 
  }
  else i = 0;
  
  //initial pass to look for space+alpha chars; 2 delimiters per word
  for (i = i; i < strlen(file->readLine); i++){  
    if (!isalnum(file->readLine[i]) && isalnum(file->readLine[i+1]))
    delimiters += 2;
  }

  //extra delimiter
  delimiters++;
  
  //array to hold loc of begin and ending spaces of commands
  int* argLocBeginEnd;
  try{ 
    argLocBeginEnd = new int[delimiters](); 
  }
  catch (bad_alloc &param) { 
    cout << "\nBAD MEMORY ALLOCATION\n";
    return; 
  }
  
  int argIndex = 0; 

  //assign first char of delimiter if alpha
  if (strlen(file->readLine) > 0 && isalpha(file->readLine[0])){  
    argLocBeginEnd[0] = 0; 
  i = 1;  
    argIndex++;
  }
  else i = 0;
  

  for (i; i < strlen(file->readLine); i++) {   
    //test if negative
    if (file->readLine[i] == '-') error->negativeNumber = true;

    //if there's a character followed by whitespace, save index
    if (isalnum(file->readLine[i]) && !isalnum(file->readLine[i+1])) {  
      argLocBeginEnd[argIndex] = i; 
      argIndex++;
    }
    
    //if there's whitespace followed by a char, save index
    if (!isalnum(file->readLine[i]) && isalnum(file->readLine[i+1])) {  
      argLocBeginEnd[argIndex] = i+1; 
      argIndex++;
    }
  }   /*  end for  */
  
  //If 2 delimiters per command, then # of commands /= 2
  if (strlen(file->readLine) > 0) 
    file->fileArgc = delimiters/2;
  try {
    file->fileArgv = new char*[delimiters](); 
  }
  catch (bad_alloc &param) { 
    cout << "\nBAD MEMORY ALLOCATION\n";
    return NULL; 
  }
  
  argIndex = 0;
  char* tempArg;
  
  
  for(unsigned int i = 0; i < delimiters/2; i++)
  {
    tempCopy[argLocBeginEnd[argIndex+1]+1] = '\0';
    tempArg = &tempCopy[argLocBeginEnd[argIndex]];
    
    (file->fileArgv)[i] = (char*)malloc(sizeof(char) * (strlen(tempArg) + 1));
    strncpy( (file->fileArgv)[i] , tempArg, strlen(tempArg) + 1);
    
    argIndex += 2;
  }

  delete [] argLocBeginEnd;
  delete [] tempCopy;

}   /*  end function convertCommandToArgv  */

void processCommandLine(Bitmap* bmp, CommandInfo* commandInfo, FileInfo* file, ErrorType* error)
{
  ExpectedStates state = EXPECT_COMMAND; //State machine enum variable       
  int defaultTest = 0;         //checksum for default command
  int colorCount  = 0;         //checksum for regular colors
  int modTest   = 0;         //checksum for mod command
  string word   = "";        //string to test command argument
  int num     = 0;         //integer to test command values
  
  //Don't process if the string is empty
  if (error->emptyString == true || error->blankLine == true ) {
    commandInfo->command = BLANK;
    return;
  }
  
  //File info must be reset after a modify command
  if(commandInfo->modLoc == false)
    setDefaultLocationValues(commandInfo, file->mainLoopIndex);

  //reset error status and default color to avoid false flags
  setDefaultErrorStatus(error);
  
  //Allow an extra iteration for any extra processing
  file->fileArgc++;

  //cycle through all arguments found in readline
  for (int arg = 0; arg < file->fileArgc-1; arg++) {
    
    //null flags to reset at each pass
    num  = -1;
    word = "";

    //validate data and convert to string/int for easy processing
    if (arg < file->fileArgc-1) {
      if (isdigit(*file->fileArgv[arg]))
        num = atoi(file->fileArgv[arg]);
      else if (isalpha(*file->fileArgv[arg]))
        word = file->fileArgv[arg];
    
      if(DEBUG) cout << "\ncount & num & word & argv[i]: "<< arg << num 
               << " " << word << " |" << file->fileArgv[arg] << "| " 
               << file->fileArgc << endl;
    }//end if

    /*state machine to process commands and validate data */
    switch (state) {
      //EXPECT_NEW_DEFAULT -------------------------------------------------
      case EXPECT_NEW_DEFAULT : {
      if(DEBUG) cout << endl << word << " >> " 
        << s_mapExpectedStatesToString[EXPECT_NEW_DEFAULT];
      if(DEBUG) cout << endl << "command: " 
        << s_mapEnumValuesToString[commandInfo->command];

      bmp->defaultColor.newDefault = true;
      
      //iterate through all colors for new default color
      switch (s_mapStringValues[word]) {
        case RED   : {state = EXPECT_RED_VAL;   defaultTest++; continue;}
        case GREEN : {state = EXPECT_GREEN_VAL; defaultTest++; continue;}
        case BLUE  : {state = EXPECT_BLUE_VAL;  defaultTest++; continue;}
        case ALPHA : {state = EXPECT_ALPHA_VAL; defaultTest++; continue;} 
        default  : {state = EXPECT_UNKNOWN;          continue;}
      }
      }    
      //EXPECT_COMMAND -----------------------------------------------------
      case EXPECT_COMMAND : {
      if(DEBUG) cout << endl << word << " >> " 
        << s_mapExpectedStatesToString[EXPECT_COMMAND];
      
      //assign command to enumerated type StringValue
      commandInfo->command = (s_mapStringValues[word]);
      
      //10 command options
      switch(s_mapStringValues[word]) {
        //DEFAULT---------------------------------------------------------
        case DEFAULT: {
        state = EXPECT_NEW_DEFAULT;   
        continue;
        }
        //INSERT ---------------------------------------------------------
        case INSERT : {
        state = EXPECT_ROW_COL;       
        continue;
        }
        //DELETE ---------------------------------------------------------
        case DELETE : {
        state = EXPECT_ROW_COL;       
        continue;
        }
        //MODIFY ---------------------------------------------------------
        case MODIFY : {                             
        state = EXPECT_ROW_COL;                       
        commandInfo->modLoc = true;                     
        continue;                               
        }                                   
        //WRITE   ------------------------------------------------------
        case WRITE   : {                          
        state = EXPECT_FILE_NAME;                       
        commandInfo->writeFile = true;                    
        continue;                               
        }                                   
        //QUIT   -------------------------------------------------------
        case QUIT   : {                           
        state = EXPECT_QUIT;                        
        continue;                               
        }                                   
        //CREATE_BMP_DEFAULT   -------------------------------------------
        case CREATE_BMP_DEFAULT   : {                     
        state = EXPECT_NOTHING;                       
        commandInfo->stegoBMP = false;                    
        continue;                               
        }                                   
        //CREATE_BMP_FROM_FILE -------------------------------------------
        case CREATE_BMP_FROM_FILE : {                     
        commandInfo->stegoBMP = false;                    
        commandInfo->createBMPFromFile = true;                
        state = EXPECT_FILE_NAME;                       
        continue;                               
        }                                   
        //CREATE_STEGO_DEFAULT -------------------------------------------
        case CREATE_STEGO_DEFAULT : {                     
        state = EXPECT_NOTHING;                       
        commandInfo->stegoBMP = true;                     
        continue;                               
        }                                   
        //CREATE_STEGO_FROM_FILE------------------------------------------
        case CREATE_STEGO_FROM_FILE : {                     
        commandInfo->stegoBMP = true;                     
        state = EXPECT_FILE_NAME;                       
        commandInfo->createStegoFromFile = true;              
        continue;                               
        }                                   
        //HIDE_BMP_FILE---------------------------------------------------
        case HIDE_BMP_FILE : {                        
        state = EXPECT_FILE_NAME;                       
        commandInfo->hideBMPFile = true;                  
        continue;                               
        }                                   
        //GET_HIDDEN_FILE-------------------------------------------------
        case GET_HIDDEN_FILE : {                        
        state = EXPECT_FILE_NAME;                       
        commandInfo->getHiddenFile = true;                  
        continue;                               
        }                                   
        //DELETE_OBJ------------------------------------------------------
        case DELETE_OBJ : {                           
        state = EXPECT_NOTHING;                       
        continue;                               
        }                                   
        //default: -------------------------------------------------------
        default : {                               
        state = EXPECT_COMMAND;                       
        commandInfo->command = ERROR;                     
        error->unknownCmd = true;                       
        continue;                               
        }                                   
      }/* end inner switch */
      }//end                                      
      //EXPECT_ROW_COL ---------------------------------------------------
    case EXPECT_ROW_COL : {
        if(DEBUG) cout << endl <<  word << " >> " 
          << s_mapExpectedStatesToString[EXPECT_ROW_COL];
        if(DEBUG) cout << endl << "command: " 
          << s_mapEnumValuesToString[commandInfo->command];

        switch (s_mapStringValues[word]) {
          case ROW   : {
      state = EXPECT_ROW;          
      continue;
      }
          case COL  : {
      state = EXPECT_COL;          
      continue;
      }
          default    : {
      state = EXPECT_UNKNOWN;   
            error->unknownRowOrColType = true;  
      continue;
      } 
        }
      }
      //EXPECT_ROW--------------------------------------------------------
    case EXPECT_ROW   : {
        if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_ROW)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

        //validate row
                
        validateRowCol(commandInfo, error, &state, &commandInfo->editRow, (int*)&(bmp->totalRowCount), &error->rowErrorVal, &num, &commandInfo->editRowTest);
        
        continue;
      }  
      //EXPECT_COL--------------------------------------------------------
    case EXPECT_COL   : {
        if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_COL)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];
        
        //validate column
        validateRowCol(commandInfo, error, &state, &commandInfo->editCol, (int*)&(bmp->totalColCount), &error->colErrorVal, &num, &commandInfo->editColTest);

        continue;
      }
      //EXPECT_COLOR------------------------------------------------------
    case EXPECT_COLOR   : {
        if(DEBUG) cout << endl <<  word << " >> " << s_mapExpectedStatesToString[(EXPECT_COLOR)];
        if(DEBUG) cout << endl << "colorCount = " << colorCount;
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

        if (colorCount == 4) word = "FULL";
        
        switch (s_mapStringValues[word]) {
          case RED     : {state = EXPECT_RED_VAL;     colorCount++;  continue;}
          case GREEN   : {state = EXPECT_GREEN_VAL;  colorCount++;  continue;}
          case BLUE   : {state = EXPECT_BLUE_VAL;    colorCount++;  continue;}
          case ALPHA   : {state = EXPECT_ALPHA_VAL;  colorCount++;  continue;} 
          case 'FULL' : {state = EXPECT_NOTHING;    colorCount++;  continue;}
          default      : {
      state = EXPECT_UNKNOWN;   
            error->unknownColorType = true; 
      continue;
      }        
        }                                    
      }
      //EXPECT_RED_VAL   ---------------------------------------------------------------------------------
    case EXPECT_RED_VAL   : {
        if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_RED_VAL)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];  

        validateColor(bmp, error, &bmp->defaultColor.red, &bmp->color.red, &num);  
        
        validateColorCount(&bmp->defaultColor.newDefault, &state, &colorCount);
        
        continue;
      }  
      //EXPECT_GREEN_VAL   ---------------------------------------------------------------------------------
    case EXPECT_GREEN_VAL   : {
        if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_GREEN_VAL)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

        validateColor(bmp, error,  &bmp->defaultColor.green, &bmp->color.green, &num);    
        
        validateColorCount(&bmp->defaultColor.newDefault, &state, &colorCount);

        continue; 
      }
      //EXPECT_BLUE_VAL   ---------------------------------------------------------------------------------
    case EXPECT_BLUE_VAL   : { 
        if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_BLUE_VAL)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

        validateColor(bmp, error, &bmp->defaultColor.blue, &bmp->color.blue, &num);

        validateColorCount(&bmp->defaultColor.newDefault, &state, &colorCount);

        continue;
      }
      //EXPECT_ALPHA_VAL   ---------------------------------------------------------------------------------
    case EXPECT_ALPHA_VAL   : {
        if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_ALPHA_VAL)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

        validateColor(bmp, error, &bmp->defaultColor.alpha, &bmp->color.alpha, &num);

        validateColorCount(&bmp->defaultColor.newDefault, &state, &colorCount);

        continue;
      }
      //EXPECT_FILE_NAME  ---------------------------------------------------------------------------------
    case EXPECT_FILE_NAME  : {
        if(DEBUG) cout << endl <<  word << " >> " << s_mapExpectedStatesToString[(EXPECT_FILE_NAME)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command]  ;
        
    //HideBMPFile------------------------------------------------------------------------------
    if(commandInfo->hideBMPFile == true && file->fileArgc == 6) {
      if(commandInfo->writeCount < 1) 
      file->inFileName = word;
      else
      file->fileToHideName = word;
      
      state = EXPECT_EXTENSION;
      continue;
    }
        //getHiddenFile------------------------------------------------------------------------------
    if(commandInfo->getHiddenFile == true && file->fileArgc == 6) {
      if(commandInfo->writeCount < 1) 
      file->inFileName= word;
      else
      file->outFileName= word;
      
      state = EXPECT_EXTENSION;
      continue;
    }
    //createBMPFromFile------------------------------------------------------------------------------
    if(commandInfo->createBMPFromFile == true && file->fileArgc == 4){
      file->inFileName = word; 
          state = EXPECT_EXTENSION;
      continue;
    }
    //createStegoFromFile------------------------------------------------------------------------------
    if(commandInfo->createStegoFromFile == true && file->fileArgc == 4) {
      file->inFileName = word; 
          state = EXPECT_EXTENSION;
      continue;
    }
    //writeFile------------------------------------------------------------------------------
    if (commandInfo->writeFile == true && file->fileArgc == 4) {
          file->outFileName = word;
          state = EXPECT_EXTENSION;
      continue;
    }
    //Otherwise------------------------------------------------------------------------------
        else {
          commandInfo->command = ERROR;
          error->missingOutFileName = true;
      state = EXPECT_EXTENSION;
      continue;
    }
    }
      //EXPECT_EXTENSION ---------------------------------------------------------------------------------
    case EXPECT_EXTENSION : {
        if(DEBUG) cout << endl <<  word << " >> " << s_mapExpectedStatesToString[(EXPECT_EXTENSION)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];
        
    if(commandInfo->hideBMPFile == true) {
      if(commandInfo->writeCount < 1) 
      file->inFileName += "." + word;
      else
      file->fileToHideName += "." + word;
      state = EXPECT_FILE_NAME;
    }
    else if(commandInfo->getHiddenFile == true) {
      if(commandInfo->writeCount < 1) 
      file->inFileName += "." + word;
      else
      file->outFileName += "." + word;
      state=EXPECT_FILE_NAME;
    }
    else if (commandInfo->createBMPFromFile == true || commandInfo->createStegoFromFile == true) { 
      file->inFileName += "." + word;
    }
    else       
      file->outFileName += "." + word;

    commandInfo->writeCount++;
    continue;
      }
      //EXPECT_QUIT    ---------------------------------------------------------------------------------
    case EXPECT_QUIT    : {
        if(DEBUG) cout << endl << word << " >> " << s_mapExpectedStatesToString[(EXPECT_QUIT)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command]    ;
        //return to main
        return;
      }
      //EXPECT_UNKNOWN  ---------------------------------------------------------------------------------
    case EXPECT_UNKNOWN  : {
        if(DEBUG) cout << endl << word << " >> " <<s_mapExpectedStatesToString[(EXPECT_UNKNOWN)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];
        error->unknownCmdOrVal = true;                                  
        state = EXPECT_COMMAND;
        continue;
      }
      //EXPECT_NOTHING-----------------------------------------------------------------------------------
    case EXPECT_NOTHING : {
        if(DEBUG) cout << endl << word << " >> " <<s_mapExpectedStatesToString[(EXPECT_UNKNOWN)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];
        state = EXPECT_NOTHING;
        
    continue;
      }
      //default -----------------------------------------------------------------------------------
    default : { 
        if(DEBUG) cout << endl << "DEFAULT :{}";
        continue; 
      }
        
    }//end main switch
  }//end for loop      
  
  //must test to make sure an object has been allocated!!
  if(bmp != NULL) {
  //rgba must be explicitely stated to
    //create a new default color.
    if (bmp->defaultColor.newDefault == true) {
    if(defaultTest != 4)  
        bmp->setDefaultColors(&bmp->color);
    //setDefaultColorValuesToWhite(defaultColor);
    else
    bmp->setDefaultColors();
      
    bmp->defaultColor.newDefault = false;
    }

    if ((commandInfo->command == INSERT || commandInfo->command == MODIFY) && colorCount < 4) {
      bmp->setDefaultColors();
  
    error->missingColorValues = true;
    }
    //modify must have both row and column specified;
    if (commandInfo->modLoc == true) {
    if(commandInfo->editRow  < 0 || commandInfo->editCol < 0 ) {
        commandInfo->command = ERROR;
        error->modifyRowOrColMissing = true;
    }
    }
  
    /*test that commands and values are present*/
    if (commandInfo->command == INSERT && state == EXPECT_ROW && commandInfo->editRow < 0){
        commandInfo->command = ERROR;
        error->missingRowValue = true;
    }
    if (commandInfo->command == INSERT && state == EXPECT_COL && commandInfo->editCol < 0) {
        commandInfo->command = ERROR;
        error->missingColValue = true;
    }

    if (commandInfo->command == DELETE && state == EXPECT_COL && commandInfo->editCol < 0) {
        commandInfo->command = ERROR;
        error->missingColValue = true;
    }
    if (commandInfo->command == DELETE && state == EXPECT_ROW  && commandInfo->editRow < 0){
        commandInfo->command = ERROR;
        error->missingRowValue = true;
    }
  
    if(error->invalidColorVal == true)
      commandInfo->command = ERROR;
  
  /*convert color to byte*/
    bmp->convertColorToPixel();
  }

}//end convert function    


void processCommandLine(StegoBitmap* stegoBmp, CommandInfo* commandInfo, FileInfo* file, ErrorType* error)
{
  ExpectedStates state = EXPECT_COMMAND;   //State machine variable       
  int defaultTest = 0;                //checksum for default command
  int colorCount  = 0;          //checksum for regular colors
  int modTest   = 0;                //checksum for mod command
  string word   = "";                //string to test command argument
  int num     = 0;                  //integer to test command values
  
  //Don't process if the string is empty
  if (error->emptyString == true || error->blankLine == true ) {
    commandInfo->command = BLANK;
    return;
  }
  
  if(commandInfo->modLoc == false)
    setDefaultLocationValues(commandInfo, file->mainLoopIndex);

  //reset error status and default color to avoid false flags
  setDefaultErrorStatus(error);
  //TO DO check to see if these necessary
  /*bmp->setDefaultColors(&bmp->color);
  bmp->setDefaultColors(&bmp->defaultColor);
*/
  file->fileArgc++;

  //cycle through all arguments
  for (int arg = 0; arg < file->fileArgc-1; arg++) {
  num    = -1;              //reset at each pass
    word  = "";

  


  //validate data and convert to string/int for easy processing
    if (arg < file->fileArgc-1) {
      if (isdigit(*file->fileArgv[arg]))
        num = atoi(file->fileArgv[arg]);
      else if (isalpha(*file->fileArgv[arg]))
        word = file->fileArgv[arg];
    
      if(DEBUG) cout << "\nnum & word & argv[i]: " << num << " " << word << " |" << file->fileArgv[arg] << "| " << file->fileArgc << endl;
    }

  /*state machine to process commands and validate data */
    switch (state) {
  
    //EXPECT_NEW_DEFAULT -------------------------------------------------------------------------------      
    case EXPECT_NEW_DEFAULT : {
        if(DEBUG) cout << endl << word << " >> " << s_mapExpectedStatesToString[EXPECT_NEW_DEFAULT];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command]    ;

    stegoBmp->defaultColor.newDefault = true;
        
        switch (s_mapStringValues[word]) {
          case RED  : {state = EXPECT_RED_VAL;   defaultTest++;   continue;}
          case GREEN  : {state = EXPECT_GREEN_VAL; defaultTest++;    continue;}
          case BLUE  : {state = EXPECT_BLUE_VAL;  defaultTest++;   continue;}
          case ALPHA  : {state = EXPECT_ALPHA_VAL; defaultTest++;   continue;} 
          default    : {state = EXPECT_UNKNOWN; 
                  /*error->defaultColorErrorType = true;*/    continue;}
        }
      }    
    //EXPECT_COMMAND -------------------------------------------------------------------------------      
    case EXPECT_COMMAND : {
        if(DEBUG) cout << endl << word << " >> " << s_mapExpectedStatesToString[EXPECT_COMMAND];
        //assign command to enumerated type StringValue
        commandInfo->command = (s_mapStringValues[word]);
        
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command]    ;

        switch(s_mapStringValues[word]) {
      //DEFAULT-------------------------------------------------------------------------------          
      case DEFAULT: {
        state = EXPECT_NEW_DEFAULT;   
        continue;
      }
      //INSERT -------------------------------------------------------------------------------          
      case INSERT : {
        state = EXPECT_ROW_COL;       
        continue;
      }
      //DELETE -------------------------------------------------------------------------------          
      case DELETE : {
        state = EXPECT_ROW_COL;       
        continue;
      }
      //MODIFY -------------------------------------------------------------------------------          
      case MODIFY : {
        state = EXPECT_ROW_COL; 
                commandInfo->modLoc = true;        
        continue;
      }
      //WRITE   -------------------------------------------------------------------------------          
      case WRITE   : {
        state = EXPECT_FILE_NAME;
        commandInfo->writeFile = true;         
        continue;
      }
      //QUIT   -------------------------------------------------------------------------------          
      case QUIT   : {
        state = EXPECT_QUIT;         
        continue;
      }
      //CREATE_BMP_DEFAULT   -------------------------------------------------------------------------------      
      case CREATE_BMP_DEFAULT   : { 
        state = EXPECT_NOTHING;
        commandInfo->stegoBMP = false; 
        continue;
      }
     //CREATE_BMP_FROM_FILE -------------------------------------------------------------------------------      
      case CREATE_BMP_FROM_FILE : {
        commandInfo->stegoBMP = false;
        state = EXPECT_FILE_NAME;
        commandInfo->createBMPFromFile = true;    
        continue;
      }
     //CREATE_STEGO_DEFAULT -------------------------------------------------------------------------------      
      case CREATE_STEGO_DEFAULT : { 
        state = EXPECT_NOTHING;
        commandInfo->stegoBMP = true; 
        continue;
      }
      //CREATE_STEGO_FROM_FILE -------------------------------------------------------------------------------      
      case CREATE_STEGO_FROM_FILE : { 
        commandInfo->stegoBMP = true; 
        commandInfo->createStegoFromFile = true; 
        state = EXPECT_FILE_NAME;
        continue;
      }
      //HIDE_BMP_FILE      -------------------------------------------------------------------------------      
      case HIDE_BMP_FILE      : {
        state = EXPECT_FILE_NAME;
        commandInfo->hideBMPFile = true;        
        continue;
      }
      //GET_HIDDEN_FILE    -------------------------------------------------------------------------------      
      case GET_HIDDEN_FILE    : {
        state = EXPECT_FILE_NAME;
        commandInfo->getHiddenFile = true;      
        continue;
      }
      //DELETE_OBJ       -------------------------------------------------------------------------------      
      case DELETE_OBJ       : { 
        state = EXPECT_NOTHING;  
        continue;
      }
      //: -------------------------------------------------------------------------------      
      default    : { 
      state = EXPECT_COMMAND;  
            commandInfo->command = ERROR;
            error->unknownCmd = true;    
      continue;
      }
        }
      }
    //EXPECT_ROW_COL -------------------------------------------------------------------------------      
    case EXPECT_ROW_COL : {
        if(DEBUG) cout << endl <<  word << " >> " << s_mapExpectedStatesToString[EXPECT_ROW_COL];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

        switch (s_mapStringValues[word]) {
          case ROW   : {
      state = EXPECT_ROW;          
      continue;
      }
          case COL  : {
      state = EXPECT_COL;          
      continue;
      }
          default    : {
      state = EXPECT_UNKNOWN;   
            error->unknownRowOrColType = true;  
      continue;
      } 
        }
      }
    //EXPECT_ROW   -------------------------------------------------------------------------------      
    case EXPECT_ROW   : {
        if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_ROW)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

        //validate row
                
        validateRowCol(commandInfo, error, &state, &commandInfo->editRow, (int*)&(stegoBmp->totalRowCount), &error->rowErrorVal, &num, &commandInfo->editRowTest);
        
        continue;
      }  
    //EXPECT_COL   -------------------------------------------------------------------------------      
    case EXPECT_COL   : {
        if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_COL)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];
        
        //validate column
        validateRowCol(commandInfo, error, &state, &commandInfo->editCol, (int*)&(stegoBmp->totalColCount), &error->colErrorVal, &num, &commandInfo->editColTest);

        continue;
      }
    //EXPECT_COLOR   -------------------------------------------------------------------------------      
    case EXPECT_COLOR   : {
        if(DEBUG) cout << endl <<  word << " >> " << s_mapExpectedStatesToString[(EXPECT_COLOR)];
        if(DEBUG) cout << endl << "colorCount = " << colorCount;
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

        if (colorCount == 4) word = "FULL";
        
        switch (s_mapStringValues[word]) {
          case RED     : {state = EXPECT_RED_VAL;     colorCount++;  continue;}
          case GREEN   : {state = EXPECT_GREEN_VAL;  colorCount++;  continue;}
          case BLUE   : {state = EXPECT_BLUE_VAL;    colorCount++;  continue;}
          case ALPHA   : {state = EXPECT_ALPHA_VAL;  colorCount++;  continue;} 
          case 'FULL' : {state = EXPECT_NOTHING;    colorCount++;  continue;}
          default      : {
      state = EXPECT_UNKNOWN;   
            error->unknownColorType = true; 
      continue;
      }        
        }                                    
      }
    //EXPECT_RED_VAL   -------------------------------------------------------------------------------      
    case EXPECT_RED_VAL   : {
        if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_RED_VAL)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];  

        validateColor(stegoBmp, error, &stegoBmp->defaultColor.red, &stegoBmp->color.red, &num);  
        
        validateColorCount(&stegoBmp->defaultColor.newDefault, &state, &colorCount);
        
        continue;
      }  
    //EXPECT_GREEN_VAL   -------------------------------------------------------------------------------      
    case EXPECT_GREEN_VAL   : {
        if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_GREEN_VAL)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

        validateColor(stegoBmp, error,  &stegoBmp->defaultColor.green, &stegoBmp->color.green, &num);    
        
        validateColorCount(&stegoBmp->defaultColor.newDefault, &state, &colorCount);

        continue; 
      }
      //EXPECT_BLUE_VAL   -------------------------------------------------------------------------------      
    case EXPECT_BLUE_VAL   : { 
        if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_BLUE_VAL)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

        validateColor(stegoBmp, error, &stegoBmp->defaultColor.blue, &stegoBmp->color.blue, &num);

        validateColorCount(&stegoBmp->defaultColor.newDefault, &state, &colorCount);

        continue;
      }
    //EXPECT_ALPHA_VAL   -------------------------------------------------------------------------------      
    case EXPECT_ALPHA_VAL   : {
        if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_ALPHA_VAL)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

        validateColor(stegoBmp, error, &stegoBmp->defaultColor.alpha, &stegoBmp->color.alpha, &num);

        validateColorCount(&stegoBmp->defaultColor.newDefault, &state, &colorCount);

        continue;
      }
    //EXPECT_FILE_NAME  -------------------------------------------------------------------------------      
    case EXPECT_FILE_NAME  : {
        if(DEBUG) cout << endl <<  word << " >> " << s_mapExpectedStatesToString[(EXPECT_FILE_NAME)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command]  ;
        
    //HideBMPFile------------------------------------------------------------------------------
    if(commandInfo->hideBMPFile == true && file->fileArgc == 6) {
      if(commandInfo->writeCount < 1) 
      file->inFileName = word;
      else
      file->fileToHideName = word;
      
      state = EXPECT_EXTENSION;
      continue;
    }
        //getHiddenFile------------------------------------------------------------------------------
    if(commandInfo->getHiddenFile == true && file->fileArgc == 6) {
      if(commandInfo->writeCount < 1) 
      file->inFileName= word;
      else
      file->outFileName= word;
      
      state = EXPECT_EXTENSION;
      continue;
    }
    //createBMPFromFile------------------------------------------------------------------------------
    if(commandInfo->createBMPFromFile == true && file->fileArgc == 4){
      file->inFileName = word; 
          state = EXPECT_EXTENSION;
      continue;
    }
    //createStegoFromFile------------------------------------------------------------------------------
    if(commandInfo->createStegoFromFile == true && file->fileArgc == 4) {
      file->inFileName = word; 
          state = EXPECT_EXTENSION;
      continue;
    }
    //writeFile------------------------------------------------------------------------------
    if (commandInfo->writeFile == true && file->fileArgc == 4) {
          file->outFileName = word;
          state = EXPECT_EXTENSION;
      continue;
    }
    //Otherwise------------------------------------------------------------------------------
        else {
          commandInfo->command = ERROR;
          error->missingOutFileName = true;
      state = EXPECT_EXTENSION;
      continue;
    }
    }
    //EXPECT_EXTENSION------------------------------------------------------------------------------
    case EXPECT_EXTENSION : {
        if(DEBUG) cout << endl <<  word << " >> " << s_mapExpectedStatesToString[(EXPECT_EXTENSION)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];
        
    if(commandInfo->hideBMPFile == true) {
      if(commandInfo->writeCount < 1) 
      file->inFileName += "." + word;
      else
      file->fileToHideName += "." + word;
      state = EXPECT_FILE_NAME;
    }
    else if(commandInfo->getHiddenFile == true) {
      if(commandInfo->writeCount < 1) 
      file->inFileName += "." + word;
      else
      file->outFileName += "." + word;
      state=EXPECT_FILE_NAME;
    }
    else if (commandInfo->createBMPFromFile == true || commandInfo->createStegoFromFile == true) { 
      file->inFileName += "." + word;
    }
    else       
      file->outFileName += "." + word;

    commandInfo->writeCount++;
    continue;
      }
    //EXPECT_QUIT------------------------------------------------------------------------------
    case EXPECT_QUIT    : {
        if(DEBUG) cout << endl << word << " >> " << s_mapExpectedStatesToString[(EXPECT_QUIT)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command]    ;
        //return to main
        return;
      }
    //EXPECT_UNKNOWN  ------------------------------------------------------------------------------
    case EXPECT_UNKNOWN  : {
        if(DEBUG) cout << endl << word << " >> " <<s_mapExpectedStatesToString[(EXPECT_UNKNOWN)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];
        error->unknownCmdOrVal = true;                                  
        state = EXPECT_COMMAND;
        continue;
      }
    //EXPECT_NOTHING -------------------------------------------------------------------------------      
    case EXPECT_NOTHING : {
        if(DEBUG) cout << endl << word << " >> " <<s_mapExpectedStatesToString[(EXPECT_UNKNOWN)];
        if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];
        state = EXPECT_NOTHING;
        continue;
      }
    //default: -------------------------------------------------------------------------------      
    default : { 
        if(DEBUG) cout << endl << "DEFAULT :{}";
        continue; 
      }
        
    }//end main switch
  }//end for loop      
  
  //must test to make sure an object has been allocated!!
  if(stegoBmp != NULL) {
  
  //rgba must be explicitely stated to
    //create a new default color.
    if (stegoBmp->defaultColor.newDefault == true) {
    if(defaultTest != 4)  
        stegoBmp->setDefaultColors(&stegoBmp->color);
    //setDefaultColorValuesToWhite(defaultColor);
    else
    stegoBmp->setDefaultColors();
      
    stegoBmp->defaultColor.newDefault = false;
    }

    if ((commandInfo->command == INSERT || commandInfo->command == MODIFY) && colorCount < 4) {
      stegoBmp->setDefaultColors();
  
    error->missingColorValues = true;
    }
    //modify must have both row and column specified;
    if (commandInfo->modLoc == true) {
    if(commandInfo->editRow  < 0 || commandInfo->editCol < 0 ) {
        commandInfo->command = ERROR;
        error->modifyRowOrColMissing = true;
    }
    }
  
    /*test that commands and values are present*/
    if (commandInfo->command == INSERT && state == EXPECT_ROW && commandInfo->editRow < 0){
        commandInfo->command = ERROR;
        error->missingRowValue = true;
    }
    if (commandInfo->command == INSERT && state == EXPECT_COL && commandInfo->editCol < 0) {
        commandInfo->command = ERROR;
        error->missingColValue = true;
    }

    if (commandInfo->command == DELETE && state == EXPECT_COL && commandInfo->editCol < 0) {
        commandInfo->command = ERROR;
        error->missingColValue = true;
    }
    if (commandInfo->command == DELETE && state == EXPECT_ROW  && commandInfo->editRow < 0){
        commandInfo->command = ERROR;
        error->missingRowValue = true;
    }
  
    if(error->invalidColorVal == true)
      commandInfo->command = ERROR;
  
  /*convert color to byte*/
    stegoBmp->convertColorToPixel();
  }
}//end convert function    

void processConsoleArgs(int &argc, char* argv[], FileInfo* file)
{
  if(argc != 2) { 
  
    std::cerr << "\n*******************************************************************" << std::endl;
    std::cerr << "\nCOMMAND-LINE ERROR:";
    std::cerr << "\nUSAGE:GE5 [command-file name.txt] " << std::endl;
    std::cerr << "\n\tUser must specify a command-file name." << std::endl;
    std::cerr << "\tPlease ensure file exists and is in the same folder as the executable." << std::endl;
    std::cerr << "\n\tProgram terminated." << std::endl;
    std::cerr << "\n\n*******************************************************************" << std::endl;
    
    exit(0);
  }
  else file->fileName = argv[1]; 
}


void quitProgram(FileInfo* file ) 
{
  file->readFile.seekg(0L, ios::end);

}

void editBitmap(Bitmap* bmp, FileInfo* file, CommandInfo* cmd, ErrorType* error)
{ 
  switch(cmd->command){
    case DEFAULT  : { break; }  
  case CREATE_BMP_DEFAULT: { 
    cmd->createBMP = true;   //no arg
    break; 
  }
  case CREATE_BMP_FROM_FILE: { 
    cmd->createBMPFromFile = true;
    break; 
  }
  case CREATE_STEGO_DEFAULT: { 
    cmd->createStego = true;   //no arg
    break; 
  }
  case CREATE_STEGO_FROM_FILE: { 
    cmd->createStegoFromFile = true;
    break; 
  }
  case HIDE_BMP_FILE:  {
    break;
  }
  case GET_HIDDEN_FILE: {
    break;
  }
  
  case DELETE_OBJ: { 
    delete bmp;  
    break; 
  }
  case INSERT    : {  
    if(cmd->editRowTest) { 
    bmp->insertRow(cmd->editRow); 
    cmd->editRowTest = false; 
    break; 
    }
      if(cmd->editColTest) { 
    bmp->insertCol(cmd->editCol); 
    cmd->editColTest = false; 
    break; 
    }
      cmd->command = ERROR;
      error->missingRowOrColType = true;
      editBitmap(bmp, file, cmd, error);
      break;
    }
    case DELETE    : {
      if(cmd->editRowTest) { 
    bmp->deleteRow(cmd->editRow); 
    cmd->editRowTest = false; 
    break; 
    }
      if(cmd->editColTest) { 
    bmp->deleteCol(cmd->editCol); 
    cmd->editColTest = false; 
    break; 
    }
      cmd->command = ERROR;
      error->missingRowOrColType = true;
      editBitmap(bmp, file, cmd, error);
      break;
    }
    case MODIFY    : { 
    bmp->modRowCol(cmd->editRow, cmd->editCol); 
    cmd->modLoc = false; 
    break; 
  }
    case WRITE    : { 
    bmp->writeToFile(file->outFileName, bmp->grid); 
    file->writtenToFile = true; 
    break; 
  } 
    case QUIT      : { 
    quitProgram(file); 
    break; 
  }
    case ERROR    : { break; }
    case BLANK    : { break; }
    default        : { break; }
  
  }



}


void editBitmap(StegoBitmap* stegoBmp, FileInfo* file, CommandInfo* cmd, ErrorType* error)
{ 
  switch(cmd->command){
    case DEFAULT  : { break; }  
  case CREATE_BMP_DEFAULT: { 
    cmd->createBMP = true;   //no arg
    break; 
  }
  case CREATE_BMP_FROM_FILE: { 
    cmd->createBMPFromFile = true;
    break; 
  }
  case CREATE_STEGO_DEFAULT: { 
    cmd->createStego = true;   //no arg
    break; 
  }
  case CREATE_STEGO_FROM_FILE: { 
    cmd->createStegoFromFile = true;
    break; 
  }
  case HIDE_BMP_FILE:  {
    try {

    stegoBmp->hideFileInBMPFile(file->inFileName, file->fileToHideName);
    }
    catch(StegoBitmap::hideFileTooBig){

    cout << "\n\n\t\tERROR: Size of file to hide too large for carrier file.\n\n";
    }
    break;
  }
  case GET_HIDDEN_FILE: {
    try {
    stegoBmp->retrieveFileFromBMPFile(file->inFileName, file->outFileName);
    }
    catch(StegoBitmap::hiddenFileSizeInconsistancy){
    cout << "\n\n\t\tERROR: Size indicated by data hidden in file inconsistent with carrier file.\n\n";
    }
    catch(StegoBitmap::negativeHiddenFileSize) {
    cout << "\n\n\t\tERROR: Size indicated by data hidden in file is negative: read failure.\n\n";
    }
    break;
  }
  case DELETE_OBJ: { 
    cmd->stegoBMP = false;
    delete stegoBmp;  
    break; 
  }
  case INSERT    : {  
    if(cmd->editRowTest) { 
    stegoBmp->insertRow(cmd->editRow); 
    cmd->editRowTest = false; 
    break; 
    }
      if(cmd->editColTest) { 
    stegoBmp->insertCol(cmd->editCol); 
    cmd->editColTest = false; 
    break; 
    }
      cmd->command = ERROR;
      error->missingRowOrColType = true;
      editBitmap(stegoBmp, file, cmd, error);
      break;
    }
    case DELETE    : {
      if(cmd->editRowTest) { 
    stegoBmp->deleteRow(cmd->editRow); 
    cmd->editRowTest = false; 
    break; 
    }
      if(cmd->editColTest) { 
    stegoBmp->deleteCol(cmd->editCol); 
    cmd->editColTest = false; 
    break; 
    }
      cmd->command = ERROR;
      error->missingRowOrColType = true;
      editBitmap(stegoBmp, file, cmd, error);
      break;
    }
    case MODIFY    : { 
    stegoBmp->modRowCol(cmd->editRow, cmd->editCol); 
    cmd->modLoc = false; 
    break; 
  }
    case WRITE    : { 
    stegoBmp->writeToFile(file->outFileName, stegoBmp->grid); 
    file->writtenToFile = true; 
    break; 
  } 
    case QUIT      : { 
    quitProgram(file); 
    break; 
  }
    case ERROR    : { break; }
    case BLANK    : { break; }
    default        : { break; }
  
  }



}

//closing functions
void closeFiles(FileInfo* file)
{
  if(file->readFile)
    file->readFile.close();
  if(file->outFile)
    file->outFile.close();
}


/*-----------------------------------------------------------------------------*\
|  Primary Function : Free Dynamically Allocated Memory for Argv pointer array  |
\*-----------------------------------------------------------------------------*/
void freeDynamicallyAllocatedArgv(FileInfo *file)
{
  /*  This function frees all the dynamically allocated memory used by the fileArgv variable  */
  
  /*  Declare and Initialize Variables  */
  int i = 0;                /*  Standard Iteration Variable      */

  /*  Begin a loop through the pointers in fileArgv as limited by the int in fileArgc  */
  for ( i = 0 ; i < file->fileArgc ; i++ )
  {
    /*  Free the memory for the char array pointed to by element i of fileArgv  */
    free(file->fileArgv[i]);

  }   /*  end for  */
  
  /*  Free (Delete) the dynamically allocated memory for the char pointer array fileArgv  */
  delete [] file->fileArgv;

}   /*  end function freeDynamicallyAllocatedArgv  */
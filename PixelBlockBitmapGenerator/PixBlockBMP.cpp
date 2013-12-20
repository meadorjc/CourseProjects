/*****************************************************
*  Caleb Meador
*  COSC1437 GE#5 , Fall, 2013
*  Filename: PixBlockBMP.cpp
*  11/18/2013
*   updated 12/18/2013
*
*   NOTE: To compile and write to file correctly, 
*          must use cl.exe's /Zp2 to pad bytes 
********************************************************/

#include <iostream>
#include <fstream>   /*  for file stream objects  */
#include <iomanip>   /*  for setw and setfill        */
#include <string>    /*  for anything to do with String*/
#include <iostream>  /*  for everything else         */
#include <map>       //map string values to enum
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <sys/stat.h>  /*file sys info for checking if file exists*/

using namespace std;

bool DEBUG = 0;

//Enumerated type for state machine decision process
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
  EXPECT_NOTHING
};

//enumerates user-input options, matches to string value
enum StringValues {
  DEFAULT = 100,
  INSERT,
  DELETE,
  MODIFY,
  WRITE,
  QUIT,
  ROW,
  COL,
  RED,
  GREEN,
  BLUE,
  ALPHA,
  ERROR,
  BLANK
};
//error flags
struct ErrorType {
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

//bmp file header
struct BMPHeader {
  char fileSignature[2];        // = BM
  unsigned int bmpFileSize;     // 10x10 grid = 1,000,122
  unsigned short int unused_1;
  unsigned short int unused_2;
  unsigned int pixelOffset;     //122 after both headers
};

//2nd header for bmp files
struct DIBHeader {
  unsigned int numBytesDIBHeader;
  unsigned int widthBitmapInPixels;
  unsigned int heightBitmapInPixels;
  unsigned short numColorPlanes;
  unsigned short numBitsPerPixel;
  unsigned int typeCompression;
  unsigned int sizeRawDataInPixelArray;
  unsigned int horizPhysicalResolution;
  unsigned int vertPhysicalResolution;
  unsigned int numColorsInPalette;
  unsigned int importantColors;
  unsigned int redChannelBitMask;
  unsigned int greenChannelBitMask;
  unsigned int blueChannelBitMask;
  unsigned int alphaChannelBitMask;
  unsigned int typeOfColorSpace;
  unsigned int colorSpaceEndPoints[9];
  unsigned int redGamma;
  unsigned int greenGamma;
  unsigned int blueGamma;
};

struct Color {
  int red;
  int green;
  int blue;
  int alpha;
  unsigned int pixelColor;  //value to store in vector<uint> grid
  bool newDefault;          //user specified new default color

  void convertColorToPixel(); //byte shifts RGBA colors into uint (ABRG mode)

};

//Holds command-file info
struct CommandInfo {
  StringValues command;
  int editRow;
  int editCol;
  bool editRowTest; //flag for edit row
  bool editColTest; //flag for edit col
  bool modLoc;      //flag for modify
};

//Holds details about file operations
struct FileInfo {
  char readLine[80];
  ifstream readFile;
  ofstream outFile;
  string fileName;
  string outFileName;
  bool newDefaultOutFileName;
  int fileArgc;     //create virtual command-line from infile
  char** fileArgv;  //create virtual command-line from infile
  int mainLoopIndex;//track iterations of main for-loop
  bool writtenToFile; //deprecate

  vector <unsigned int> grid;   //holds bmp raw color data
  int numRows;
  int numCols;
  int row;
  int col;
  int rowDupCount;
  int colDupCount;
  int gridIndex;


};

//Map commands from command file to enumerated values and back
static std::map<std::string, StringValues> s_mapStringValues;
static std::map<StringValues, std::string> s_mapEnumValuesToString;
static std::map<ExpectedStates, std::string> s_mapExpectedStatesToString;

/*display prototypes*/
void displayConvertedCommands(FileInfo* file);
void displayErrorStatus(ErrorType* error);
void displayColorInfo (Color* color);
void displayDibHeader(DIBHeader* dibHeader);
void displayBmpHeader(BMPHeader* bmpHeader);
void displayVectorGrid(FileInfo* file);
void displayCommandLineInfo(CommandInfo* cmd);
void displayErrorMessage(ErrorType* error, FileInfo* file);
void displayFileInfo(FileInfo* file);

/*initialization*/
void createDefaultBmpFile(FileInfo* file, Color* color);
void initializeDibHeader(DIBHeader* dibheader);
void initializeBmpHeader(BMPHeader* bmpHeader);
void initializeFileValues(FileInfo* file);
void initializeStringMap();
void initializeEnumMap();
void initializeExpectedStatesMap();

/*set defaults*/
void setDefaultErrorStatus(ErrorType* error);
void setDefaultColorValues(Color* color, Color* defaultColor);
void setDefaultColorValuesToWhite(Color* defaultColor);
void setDefaultLocationValues(CommandInfo* commandInfo);

/*process args */
void processConsoleArgs(int &argc, char* argv[], FileInfo* file);
void processCommandLine(Color* color, Color* newDefaultColor, 
                        CommandInfo* commandInfo, FileInfo* file, ErrorType* error);
void editBitmap(FileInfo* file, CommandInfo* cmd, BMPHeader* bmp, DIBHeader* dib, 
                Color* color, Color* newDefault, ErrorType* error);

/*validation*/
void checkFileExists(FileInfo* file);
void convertCommandToArgv(FileInfo *file, ErrorType* error);
void validateColor(Color* color, Color* defaultColor, ErrorType* error, 
                   int* anyDefault, int* anyColor, int* num);
void validateRowCol(CommandInfo* cmd, ErrorType* error, ExpectedStates* state, 
                    int* cmdRowCol, int* numRowCol, bool* genError, int* num, 
                    bool* rowColTest);
bool isBlankLine(FileInfo* file);
void validateColorCount(bool* newDefault, ExpectedStates* state, int* colorCount);

/*grid processing and writing*/
void insertRow(FileInfo* file, CommandInfo* cmd, BMPHeader* bmp, DIBHeader* dib, 
               Color* color);
void deleteRow(FileInfo* file, CommandInfo* cmd, BMPHeader* bmp, DIBHeader* dib);
void insertCol(FileInfo* file, CommandInfo* cmd, BMPHeader* bmp, DIBHeader* dib, 
               Color* color);
void deleteCol(FileInfo* file, CommandInfo* cmd, BMPHeader* bmp, DIBHeader* dib);
void modRowCol(FileInfo* file, CommandInfo* cmd, Color* color);
void writeBmpFile(FileInfo* file, CommandInfo* cmd, BMPHeader* bmp, DIBHeader* dib);

/*maintenance*/
void freeDynamicallyAllocatedArgv(FileInfo *file);
void closeFiles(FileInfo* file);
void quitProgram(FileInfo* file );

void main(int argc, char* argv[]) {

  Color     color,           //user-specified
            defaultColor;    //default color
  ErrorType error;
  CommandInfo commandInfo;   //user arguments
  FileInfo  file;            //info from file
  BMPHeader bmpHeader;       //required for BMP
  DIBHeader dibHeader;       //required for BMP

  //Initializations and defaults
  setDefaultColorValuesToWhite(&defaultColor);
  setDefaultLocationValues(&commandInfo);
  initializeFileValues(&file);
  initializeStringMap();
  initializeEnumMap();
  initializeExpectedStatesMap();
  initializeBmpHeader(&bmpHeader);
  initializeDibHeader(&dibHeader);
  setDefaultErrorStatus(&error);

  printf("\n\n***********************************************************************************");
  printf("\nWelcome to the PIXBLOCKBMP interpreter:");
  printf("\n\nAccepted Console commands: PixBlockBMP [user textfile].txt [RET]");
  printf("\n\nAccepted File commands:");
  // printf("\n\nNEW DEFAULT COLOR:----------------------------------------------");
  printf("\n\n default r [0-255] g [0-255] b [0-255] a [0-255] (use ALL)");
  // printf("\n\nINSERT ROW or COL:----------------------------------------------");
  printf("\n\n insert {row | col} [#] r [0-255] g [0-255] b [0-255] a [0-255]");
  printf("\n\n\t\tNOTE: colors optional. \n\t\tIf omitted, replaced by default values.");
  // printf("\n\nDELETE ROW or COL:----------------------------------------------");
  printf("\n\n delete {row | col} [#] (use all)");
  // printf("\n\nMODIFY BLOCK:---------------------------------------------------");
  printf("\n\n mod [row] [#] [col] [#] r [0-255] g [0-255] b [0-255] a [0-255]");
  printf("\n\n\t\tNOTE: colors optional. \n\t\tIf omitted, replaced by value of 255 (default color)");
  // printf("\n\nWRITE TO FILE:--------------------------------------------------");
  printf("\n\n write [user bmp file-name].bmp");
  // printf("\n\nQUIT PROGRAM:---------------------------------------------------");
  printf("\n\n quit\n\n");
  printf("\n\n***********************************************************************************");
  
  //process true console arguments
  processConsoleArgs(argc, argv, &file);
  
  //check if file exists before opening/reading
  checkFileExists(&file);
  
  //create default BMP model structure and colors in vector grid
  createDefaultBmpFile(&file, &color);
  
  //get initial command-file line to parse
  file.readFile.getline(file.readLine, 80);

  //track file read progress for error handling
  file.mainLoopIndex = 0;      

  do {  //until file ends
    
    cout << "\n\t\t[" << file.mainLoopIndex << "]: " << file.readLine;
    
    //convert command-file arguments into usable commands for editing bitmaps
    convertCommandToArgv(&file, &error);

    //displayConvertedCommands(&file); //for testing
    
    //after parsing execute commands
    processCommandLine(&color, &defaultColor, &commandInfo, &file, &error);
    
    //for debug purposes only
    if (DEBUG) { //massive output
      displayCommandLineInfo(&commandInfo);
      displayFileInfo(&file);
      displayColorInfo(&color);
      displayColorInfo(&defaultColor);
      displayBmpHeader(&bmpHeader);
      displayDibHeader(&dibHeader);
      cout << dec;
      displayVectorGrid(&file);
    }

    //direct command to edit functions
    editBitmap(&file, &commandInfo, &bmpHeader, &dibHeader, &color, &defaultColor, &error);
    
    //If any error occurs, display a message and continue program
    displayErrorMessage(&error, &file);

    //reset values for next read-line
    setDefaultErrorStatus(&error);
    setDefaultColorValues(&color, &defaultColor);
    setDefaultLocationValues(&commandInfo);

    file.readFile.getline(file.readLine, 80);

    file.mainLoopIndex += 1;

  } while(!file.readFile.eof());   /*  end while if the EOF is reached  */


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
void displayFileInfo(FileInfo* file) {
  cout << "fileName: "              << file->fileName << endl;
  cout << "outFileName: "           << file->outFileName << endl;
  cout << "newDefaultOutFileName: " << file->newDefaultOutFileName << endl;
  cout << "fileArgc: "              << file->fileArgc << endl;
  cout << "fileArgv: "              << file->fileArgv << endl;
  cout << "mainLoopIndex: "         << file->mainLoopIndex << endl;
  cout << "writtenToFile: "         << file->writtenToFile << endl;
  cout << "grid.size(): "           << file->grid.size() << endl;
  cout << "numRows: "               << file->numRows << endl;
  cout << "numCols: "               << file->numCols << endl;
}

//debug
void displayConvertedCommands(FileInfo* file) {
  cout << "\n\n\tParsed:\t\t";

  for(int i = 0; i < file->fileArgc; i++)
    cout << file->fileArgv[i] << " ";
  cout << endl;
}

//debug
void displayColorInfo (Color* color) {
  cout << endl;
  cout << endl << boolalpha<< "newDefault: \t" << color->newDefault;
  cout << endl << setw(6)  << "red  \t" << setw(4) << color->red  << " address: " << setw(6) << &color->red;
  cout << endl << setw(6)  << "green\t" << setw(4) << color->green << " address: " << setw(6) << &color->green;
  cout << endl << setw(6)  << "blue \t" << setw(4) << color->blue  << " address: " << setw(6) << &color->blue;
  cout << endl << setw(6)  << "alpha\t" << setw(4) << color->alpha << " address: " << setw(6) << &color->alpha;
}

//debug
void displayCommandLineInfo(CommandInfo* cmd) {
  cout  << endl;
  cout  << setw(10) << "\ncmd->command:"
        << setw(6)  << s_mapEnumValuesToString[cmd->command] << " address "
        << setw(6)   << &s_mapEnumValuesToString[cmd->command];
  cout  << setw(10) << "\ncmd->editRow:"
        << setw(4)  << cmd->editRow    << " address "
        << setw(4)  << &cmd->editRow;
  cout  << setw(10) << "\ncmd->editCol:"
        << setw(4)  << cmd->editCol    << " address "
        << setw(4)  << &cmd->editCol;
  cout  << setw(10) << "\ncmd->editRowTest:"
        << setw(4)  << cmd->editRowTest  << " address "
        << setw(4)  << &cmd->editRowTest;
  cout  << setw(10) << "\ncmd->editColTest:"
        << setw(4)  << cmd->editColTest  << " address "
        << setw(4)  << &cmd->editColTest;
  cout  << setw(10) << "\ncmd->modLoc:"
        << setw(4)  << cmd->modLoc    << " address "
        << setw(4)  << &cmd->modLoc;    //modify specific row and col


};

//debug
void displayBmpHeader(BMPHeader* bmpHeader) {
  cout << endl << "BmpHeader settings" << endl;
  cout << endl << "bmpHeader->fileSignature[0] "  << bmpHeader->fileSignature[0];
  cout << endl << "bmpHeader->fileSignature[1] "  << bmpHeader->fileSignature[1];
  cout << endl << "bmpHeader->bmpFileSize "   << bmpHeader->bmpFileSize;
  cout << endl << "bmpHeader->unused_1 "      << bmpHeader->unused_1;
  cout << endl << "bmpHeader->unused_2 "      << bmpHeader->unused_2;
  cout << endl << "bmpHeader->pixelOffset "   << bmpHeader->pixelOffset;
  cout << endl;
}
//for debug
void displayVectorGrid(FileInfo* file) {
  int vectorCount = file->numRows*file->numCols;

  cout << endl << endl;
  for(int i = 0; i < file->numRows; i++) {
    cout << endl;
    vectorCount -= file->numCols;
    for (int j = 0; j < file->numCols; j++) {
      cout << vectorCount++ << "\t";

    }
    vectorCount -= file->numCols;
  }
}

//debug
void displayErrorStatus(ErrorType* error) {
  cout << endl << endl;
  cout << "errorFlag "            << boolalpha << error->errorFlag << endl;
  cout << "missingDefaultColor "  << boolalpha << error->missingDefaultColor << endl;
  cout << "missingColValue "      << boolalpha << error->missingColValue << endl;
  cout << "missingRowValue "      << boolalpha << error->missingRowValue << endl;
  cout << "missingRowOrColType "  << boolalpha << error->missingRowOrColType << endl;
  cout << "maxRowSize "           << boolalpha << error->maxRowSize << endl;
  cout << "maxColSize "           << boolalpha << error->maxColSize << endl;
  cout << "unknownColorType "     << boolalpha << error->unknownColorType << endl;
  cout << "unknownCmdOrVal "      << boolalpha << error->unknownCmdOrVal << endl;
  cout << "unknownCmd "           << boolalpha << error->unknownCmd << endl;
  cout << "defaultColorErrorType "<< boolalpha << error->defaultColorErrorType << endl;
  cout << "unknownRowOrColType "  << boolalpha << error->unknownRowOrColType << endl;
  cout << "rowErrorVal "          << boolalpha << error->rowErrorVal << endl;
  cout << "colErrorVal "          << boolalpha << error->colErrorVal << endl;
  cout << "modifyRowOrColMissing "<< boolalpha << error->modifyRowOrColMissing << endl;
  cout << "emptyString "          << boolalpha << error->emptyString << endl;
  cout << "negativeNumber "       << boolalpha << error->negativeNumber << endl;
  cout << "invalidColorVal "      << boolalpha << error->invalidColorVal << endl;
  cout << "blankLine  "           << boolalpha << error->blankLine << endl;
  cout << "missingOutFileName "   << boolalpha << error->missingOutFileName << endl;
  cout << "missingColorValues "   << boolalpha << error->missingColorValues << endl;
  cout << endl << endl;

}

void displayDibHeader(DIBHeader* dibHeader) {
  cout << endl << "dibHeader->numBytesDIBHeader: "    << dibHeader->numBytesDIBHeader;
  cout << endl << "dibHeader->widthBitmapInPixels: "  << dibHeader->widthBitmapInPixels ;
  cout << endl << "dibHeader->heightBitmapInPixels: " << dibHeader->heightBitmapInPixels;
  cout << endl << "dibHeader->numColorPlanes: "     << dibHeader->numColorPlanes;
  cout << endl << "dibHeader->numBitsPerPixel: "    << dibHeader->numBitsPerPixel;
  cout << endl << "dibHeader->typeCompression: "    << dibHeader->typeCompression;
  cout << endl << "dibHeader->sizeRawDataInPixelArray: "  << dibHeader->sizeRawDataInPixelArray;
  cout << endl << "dibHeader->horizPhysicalResolution: "  << dibHeader->horizPhysicalResolution;
  cout << endl << "dibHeader->vertPhysicalResolution: "   << dibHeader->vertPhysicalResolution;
  cout << endl << "dibHeader->numColorsInPalette: " << dibHeader->numColorsInPalette;
  cout << endl << "dibHeader->importantColors: "    << dibHeader->importantColors;
  cout << endl << "dibHeader->redChannelBitMask: "  << dibHeader->redChannelBitMask;
  cout << endl << "dibHeader->greenChannelBitMask: " << dibHeader->greenChannelBitMask;
  cout << endl << "dibHeader->blueChannelBitMask: "  << dibHeader->blueChannelBitMask;
  cout << endl << "dibHeader->alphaChannelBitMask: " << dibHeader->alphaChannelBitMask;
  cout << endl << "dibHeader->typeOfColorSpace: "    << dibHeader->typeOfColorSpace;
  cout << endl << "dibHeader->colorSpaceEndPoints: " << dibHeader->colorSpaceEndPoints;
  cout << endl << "dibHeader->redGamma: "    << dibHeader->redGamma;
  cout << endl << "dibHeader->greenGamma: "  << dibHeader->greenGamma;
  cout << endl << "dibHeader->blueGamma: "   << dibHeader->blueGamma;
}

void displayErrorMessage(ErrorType* error, FileInfo* file) {

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
      cout << "\n\tUnknown row value \n\t\t(Use: row [0-" << file->numRows-1 << "])" ;
    if (error->colErrorVal == true)
      cout << "\n\tUnknown column value \n\t\t(Use: col [0-" << file->numCols-1 << "])" ;
    if (error->modifyRowOrColMissing == true)
      cout << "\n\tBoth the row and column must be specified in any order after modify: "
           <<"\n\t\t(Use: modify col [0-" << file->numCols-1 << "] row [0-" << file->numCols-1 << "])" ;
    if (error->missingColValue == true)
      cout << "\n\tMissing column value \n\t\t(Use: col [0-" << file->numCols-1 << "])" ;
    if (error->missingRowValue == true)
      cout << "\n\tMissing row value \n\t\t(Use: row [0-" << file->numRows-1 << "])" ;
    if (error->maxRowSize == true)
      cout << "\n\tMaximum number of rows added: 20" ;
    if (error->maxColSize == true)
      cout << "\n\tMaximum number of columns added: 20" ;
    if (error->missingRowOrColType == true)
      cout << "\n\tInsert or Delete command must be followed by 'row' or 'col' \n\t(Use: insert [row/col] [0-" << file->numRows-1 << "])";
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
void validateColor(Color* color, Color* defaultColor, ErrorType* error, int* anyDefault, int* anyColor, int* num) {

  if (error->negativeNumber != true) {
    if (defaultColor->newDefault == true)  //only when command: default
      if(*num >= 0 && *num <= 255)
        *anyDefault = *num;
      else
        error->invalidColorVal = true;
    else if (*num >= 0 && *num <= 255)
      *anyColor = *num;
    else
      error->invalidColorVal = true;
  } else
    error->invalidColorVal = true;
}

//Checksum for default color values
void validateColorCount(bool* newDefault, ExpectedStates* state, int* colorCount) {
  if (*newDefault)
    *state = EXPECT_NEW_DEFAULT ;
  else if (*colorCount < 5)
    *state = EXPECT_COLOR;
  else
    *state = EXPECT_UNKNOWN;
}

//generic row & column validator
void validateRowCol(CommandInfo* cmd, ErrorType* error, ExpectedStates* state, int* cmdRowCol, int* numRowCol, bool* valError, int* num, bool* rowColTest) {
  if (DEBUG) cout << "\nvalidateRowCol: " << *numRowCol << " " << *num << " " << error->negativeNumber << endl;

  //Can insert up to 20 total rows
  if (*numRowCol < 20 ) {
    if (*num <= *numRowCol && *num >= 0 && error->negativeNumber != true) //[0 - Current Size] && !(-)
      *cmdRowCol = *num;
    else {
      cmd->command = ERROR;
      *valError = true;
    } //generic error; whatever is passed to function

    //sentinal, else num duplicated to col on omission
    *num = -1;
    *state = EXPECT_COLOR;
  }
  //Can delete even if 20
  else if (*numRowCol == 20 && cmd->command == DELETE) {
    if (*num <= *numRowCol && *num >= 0 && error->negativeNumber != true) //[0 - Current Size] && !(-)
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
    if (*num <= *numRowCol && *num >= 0 && error->negativeNumber != true) //[0 - Current Size] && !(-)
      *cmdRowCol  = *num;
    else {
      cmd->command = ERROR;
      *valError = true;
    } //generic error; whatever is passed to function

    //sentinal, else num duplicated to col on omission
    *num = -1;
    *state = EXPECT_COLOR;
  } else {
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
void checkFileExists(FileInfo* file) {
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
bool isBlankLine(FileInfo* file) {
  for (int i = 0; i < strlen(file->readLine); i++)
    if (isalnum(file->readLine[i]))
      return false;

  return true;
}

//set functions
void setDefaultColorValues(Color* color, Color* defaultColor) {
  color->red  = defaultColor->red;
  color->green  = defaultColor->green;
  color->blue  = defaultColor->blue;
  color->alpha  = defaultColor->alpha;
  defaultColor->newDefault  = false;
}

//In case user omits new default data
void setDefaultColorValuesToWhite(Color* defaultColor) {
  defaultColor->red  = 255;
  defaultColor->green  = 255;
  defaultColor->blue  = 255;
  defaultColor->alpha  = 255;
  defaultColor->newDefault= false;
}

//reset all errors
void setDefaultErrorStatus(ErrorType* error) {
  error->errorFlag    	      = false;
  error->missingDefaultColor  = false;
  error->missingColValue      = false;
  error->missingRowValue      = false;
  error->missingRowOrColType  = false;
  error->maxRowSize    	      = false;
  error->maxColSize           = false;
  error->unknownColorType     = false;
  error->unknownCmdOrVal      = false;
  error->unknownCmd           = false;
  error->defaultColorErrorType= false;
  error->unknownRowOrColType  = false;
  error->rowErrorVal    = false;
  error->colErrorVal    = false;
  error->modifyRowOrColMissing   = false;
  error->emptyString    = false;
  error->negativeNumber = false;
  error->invalidColorVal= false;
  error->blankLine      = false;
  error->missingOutFileName  = false;
  error->missingColorValues  = false;
}

void setDefaultLocationValues(CommandInfo* commandInfo) {
  commandInfo->editRow    = -1;
  commandInfo->editCol    = -1;
  commandInfo->modLoc     = false;
  commandInfo->editRowTest  = false;
  commandInfo->editColTest  = false;

}

//initialize functions
void initializeFileValues(FileInfo* file) {
  file->fileName      = "command.txt";
  file->outFileName   = "default.bmp";
  file->numRows       = 10;
  file->numCols       = 10;
  file->newDefaultOutFileName   = false;
  file->writtenToFile           = false;
}

//Map string arguments from file to enum states
void initializeStringMap() {
  s_mapStringValues["default"]  = DEFAULT;
  s_mapStringValues["insert"]   = INSERT;
  s_mapStringValues["delete"]   = DELETE;
  s_mapStringValues["modify"]   = MODIFY;
  s_mapStringValues["write"]    = WRITE;
  s_mapStringValues["quit"]     = QUIT;
  s_mapStringValues["default"]  = DEFAULT;
  s_mapStringValues["row"]  = ROW;
  s_mapStringValues["col"]  = COL;
  s_mapStringValues["r"]    = RED;
  s_mapStringValues["g"]    = GREEN;
  s_mapStringValues["b"]    = BLUE;
  s_mapStringValues["a"]    = ALPHA;
  s_mapStringValues["error"]  = ERROR;

}

//Map states to strings for debug purposes.
void initializeEnumMap() {
  s_mapEnumValuesToString[DEFAULT]  = "default";
  s_mapEnumValuesToString[INSERT]   = "insert";
  s_mapEnumValuesToString[DELETE]   = "delete";
  s_mapEnumValuesToString[MODIFY]   = "modify";
  s_mapEnumValuesToString[WRITE]    = "write";
  s_mapEnumValuesToString[QUIT]     = "quit";
  s_mapEnumValuesToString[DEFAULT]  = "default";
  s_mapEnumValuesToString[ROW]    = "row";
  s_mapEnumValuesToString[COL]    = "col";
  s_mapEnumValuesToString[RED]    = "r";
  s_mapEnumValuesToString[GREEN]  = "g";
  s_mapEnumValuesToString[BLUE]   = "b";
  s_mapEnumValuesToString[ALPHA]  = "a";
  s_mapEnumValuesToString[ERROR]  = "error";
}

//Map states to strings for debug purposes.
void initializeExpectedStatesMap() {
  s_mapExpectedStatesToString[EXPECT_NEW_DEFAULT]  = "EXPECT_NEW_DEFAULT";
  s_mapExpectedStatesToString[EXPECT_COMMAND]  = "EXPECT_COMMAND";
  s_mapExpectedStatesToString[EXPECT_ROW_COL]  = "EXPECT_ROW_COL";
  s_mapExpectedStatesToString[EXPECT_ROW]    = "EXPECT_ROW";
  s_mapExpectedStatesToString[EXPECT_COL]    = "EXPECT_COL";
  s_mapExpectedStatesToString[EXPECT_COLOR]  = "EXPECT_COLOR";
  s_mapExpectedStatesToString[EXPECT_RED_VAL]  = "EXPECT_RED_VAL";
  s_mapExpectedStatesToString[EXPECT_GREEN_VAL]  = "EXPECT_GREEN_VAL";
  s_mapExpectedStatesToString[EXPECT_BLUE_VAL]  = "EXPECT_BLUE_VAL";
  s_mapExpectedStatesToString[EXPECT_ALPHA_VAL]  = "EXPECT_ALPHA_VAL";
  s_mapExpectedStatesToString[EXPECT_FILE_NAME]  = "EXPECT_FILE_NAME";
  s_mapExpectedStatesToString[EXPECT_QUIT]  = "EXPECT_QUIT";
  s_mapExpectedStatesToString[EXPECT_UNKNOWN]  = "EXPECT_UNKNOWN";
  s_mapExpectedStatesToString[MOD_ROW_COL]  = "MOD_ROW_COL";
  s_mapExpectedStatesToString[EXPECT_EXTENSION]  = "EXPECT_EXTENSION";
  s_mapExpectedStatesToString[EXPECT_NOTHING]  = "EXPECT_NOTHING";

}

void initializeBmpHeader(BMPHeader* bmpHeader) {
  bmpHeader->fileSignature[0] = 'B';
  bmpHeader->fileSignature[1] = 'M';
  bmpHeader->bmpFileSize = 1000122;
  bmpHeader->unused_1 = 0;
  bmpHeader->unused_2 = 0;
  bmpHeader->pixelOffset = 122;

}

void initializeDibHeader(DIBHeader* dibHeader) {
  dibHeader->numBytesDIBHeader  = 108;
  dibHeader->widthBitmapInPixels  = 500;
  dibHeader->heightBitmapInPixels  = 500;
  dibHeader->numColorPlanes  = 1;
  dibHeader->numBitsPerPixel  = 32;
  dibHeader->typeCompression  = 3;
  dibHeader->sizeRawDataInPixelArray  = 1000000;
  dibHeader->horizPhysicalResolution  = 2835;
  dibHeader->vertPhysicalResolution   = 2835;
  dibHeader->numColorsInPalette  = 0;
  dibHeader->importantColors  = 0;
  dibHeader->redChannelBitMask  = 0x00FF0000;
  dibHeader->greenChannelBitMask  = 0x0000FF00;
  dibHeader->blueChannelBitMask  = 0x000000FF;
  dibHeader->alphaChannelBitMask  = 0xFF000000;
  dibHeader->typeOfColorSpace  = 0x57696E20;
  dibHeader->colorSpaceEndPoints[9]  = 0;
  dibHeader->redGamma      = 0;
  dibHeader->greenGamma      = 0;
  dibHeader->blueGamma      = 0;

}

//process and conversion functions
void convertCommandToArgv(FileInfo *file, ErrorType* error) {
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

  char* tempCopy;                //hold command line
  unsigned int delimiters = 0;
  int i = 0;


  //if the look hasn't excuted, memory conflict occurs at delete attempt
  if (file->mainLoopIndex > 1) {
    freeDynamicallyAllocatedArgv(file);
  }

  try {
    tempCopy = new char[strlen(file->readLine) + 1]();
  } catch (bad_alloc &param) {
    return;
  }

  strncpy( tempCopy, file->readLine, strlen(file->readLine)+1);

  //test initial character to confirm command
  if (isalpha(file->readLine[0])) {
    delimiters++;
    i = 1;
  } else i = 0;

  //initial pass to look for space+alpha chars; 2 delimiters per word
  for (i = i; i < strlen(file->readLine); i++) {
    if (!isalnum(file->readLine[i]) && isalnum(file->readLine[i+1]))
      delimiters += 2;
  }

  //extra delimiter
  delimiters++;

  //array to hold loc of begin and ending spaces of commands
  int* argLocBeginEnd;

  try {
    argLocBeginEnd = new int[delimiters]();
  } catch (bad_alloc &param) {
    return;
  }

  int argIndex = 0;

  //assign first char of delimiter if alpha
  if (strlen(file->readLine) > 0 && isalpha(file->readLine[0])) {
    argLocBeginEnd[0] = 0;
    i = 1;
    argIndex++;
  } else i = 0;


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
  if (strlen(file->readLine) > 0) file->fileArgc = delimiters/2;

  try {
    file->fileArgv = new char*[delimiters]();
  } catch (bad_alloc &param) {
    return;
  }

  argIndex = 0;
  char* tempArg;

  for(int i = 0; i < delimiters/2; i++) {
    tempCopy[argLocBeginEnd[argIndex+1]+1] = '\0';
    tempArg = &tempCopy[argLocBeginEnd[argIndex]];

    (file->fileArgv)[i] = (char*)malloc(sizeof(char) * (strlen(tempArg) + 1));
    strncpy( (file->fileArgv)[i] , tempArg, strlen(tempArg) + 1);

    argIndex += 2;
  }

  delete [] argLocBeginEnd;
  delete [] tempCopy;

}   /*  end function convertCommandToArgv  */

void processCommandLine(Color* color, Color* defaultColor, CommandInfo* commandInfo, FileInfo* file, ErrorType* error) {
  ExpectedStates state = EXPECT_COMMAND;   //State machine variable
  int defaultTest = 0;      //checksum for default command
  int colorCount  = 0;                    //checksum for regular colors
  int modTest     = 0;      //checksum for mod command
  string word     = "";      //string to test command argument
  int num         = 0;      //integer to test command values

  //Don't process if the string is empty
  if (error->emptyString == true || error->blankLine == true ) {
    commandInfo->command = BLANK;
    return;
  }

  if(commandInfo->modLoc == false)
    setDefaultLocationValues(commandInfo);

  //reset error status and default color to avoid false flags
  setDefaultErrorStatus(error);
  setDefaultColorValues(color, defaultColor);

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
    case EXPECT_NEW_DEFAULT : {
      if(DEBUG) cout << endl << word << " >> " << s_mapExpectedStatesToString[EXPECT_NEW_DEFAULT];
      if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command]    ;

      defaultColor->newDefault = true;

      switch (s_mapStringValues[word]) {
      case RED  : {
        state = EXPECT_RED_VAL;
        defaultTest++;
        continue;
      }
      case GREEN  : {
        state = EXPECT_GREEN_VAL;
        defaultTest++;
        continue;
      }
      case BLUE  : {
        state = EXPECT_BLUE_VAL;
        defaultTest++;
        continue;
      }
      case ALPHA  : {
        state = EXPECT_ALPHA_VAL;
        defaultTest++;
        continue;
      }
      default    : {
        state = EXPECT_UNKNOWN;
        /*error->defaultColorErrorType = true;*/    continue;
      }
      }
    }
    case EXPECT_COMMAND : {
      if(DEBUG) cout << endl << word << " >> " << s_mapExpectedStatesToString[EXPECT_COMMAND];
      //assign command to enumerated type StringValue
      commandInfo->command = (s_mapStringValues[word]);

      if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command]    ;

      switch(s_mapStringValues[word]) {
      case DEFAULT: {
        state = EXPECT_NEW_DEFAULT;
        continue;
      }
      case INSERT : {
        state = EXPECT_ROW_COL;
        continue;
      }
      case DELETE : {
        state = EXPECT_ROW_COL;
        continue;
      }
      case MODIFY : {
        state = EXPECT_ROW_COL;
        commandInfo->modLoc = true;
        continue;
      }
      case WRITE   : {
        state = EXPECT_FILE_NAME;
        continue;
      }
      case QUIT   : {
        state = EXPECT_QUIT;
        continue;
      }
      default    : {
        state = EXPECT_COMMAND;
        commandInfo->command = ERROR;
        error->unknownCmd = true;
        continue;
      }
      }
    }
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
    case EXPECT_ROW   : {
      if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_ROW)];
      if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

      //validate row

      validateRowCol(commandInfo, error, &state, &commandInfo->editRow, &file->numRows, &error->rowErrorVal, &num, &commandInfo->editRowTest);

      continue;
    }
    case EXPECT_COL   : {
      if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_COL)];
      if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

      //validate column
      validateRowCol(commandInfo, error, &state, &commandInfo->editCol, &file->numCols, &error->colErrorVal, &num, &commandInfo->editColTest);

      continue;
    }
    case EXPECT_COLOR   : {
      if(DEBUG) cout << endl <<  word << " >> " << s_mapExpectedStatesToString[(EXPECT_COLOR)];
      if(DEBUG) cout << endl << "colorCount = " << colorCount;
      if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

      if (colorCount == 4) word = "FULL";

      switch (s_mapStringValues[word]) {
      case RED   : {
        state = EXPECT_RED_VAL;
        colorCount++;
        continue;
      }
      case GREEN   : {
        state = EXPECT_GREEN_VAL;
        colorCount++;
        continue;
      }
      case BLUE   : {
        state = EXPECT_BLUE_VAL;
        colorCount++;
        continue;
      }
      case ALPHA   : {
        state = EXPECT_ALPHA_VAL;
        colorCount++;
        continue;
      }
      case 'FULL' : {
        state = EXPECT_NOTHING;
        colorCount++;
        continue;
      }
      default    : {
        state = EXPECT_UNKNOWN;
        error->unknownColorType = true;
        continue;
      }
      }
    }
    case EXPECT_RED_VAL   : {
      if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_RED_VAL)];
      if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

      validateColor(color, defaultColor, error, &defaultColor->red, &color->red, &num);

      validateColorCount(&defaultColor->newDefault, &state, &colorCount);

      continue;
    }
    case EXPECT_GREEN_VAL   : {
      if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_GREEN_VAL)];
      if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

      validateColor(color, defaultColor, error, &defaultColor->green, &color->green, &num);

      validateColorCount(&defaultColor->newDefault, &state, &colorCount);

      continue;
    }

    case EXPECT_BLUE_VAL   : {
      if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_BLUE_VAL)];
      if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

      validateColor(color, defaultColor, error, &defaultColor->blue, &color->blue, &num);

      validateColorCount(&defaultColor->newDefault, &state, &colorCount);

      continue;
    }
    case EXPECT_ALPHA_VAL   : {
      if(DEBUG) cout << endl << num << " >> " << s_mapExpectedStatesToString[(EXPECT_ALPHA_VAL)];
      if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];

      validateColor(color, defaultColor, error, &defaultColor->alpha, &color->alpha, &num);

      validateColorCount(&defaultColor->newDefault, &state, &colorCount);

      continue;
    }
    case EXPECT_FILE_NAME  : {
      if(DEBUG) cout << endl <<  word << " >> " << s_mapExpectedStatesToString[(EXPECT_FILE_NAME)];
      if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command]  ;
      if (file->fileArgc != 4) {
        commandInfo->command = ERROR;
        error->missingOutFileName = true;
        continue;
      } else
        file->outFileName = word;

      state = EXPECT_EXTENSION;
      continue;
    }
    case EXPECT_EXTENSION : {
      if(DEBUG) cout << endl <<  word << " >> " << s_mapExpectedStatesToString[(EXPECT_EXTENSION)];
      if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];
      file->outFileName += "." + word;
      continue;
    }
    case EXPECT_QUIT    : {
      if(DEBUG) cout << endl << word << " >> " << s_mapExpectedStatesToString[(EXPECT_QUIT)];
      if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command]    ;
      //return to main
      return;
    }
    case EXPECT_UNKNOWN  : {
      if(DEBUG) cout << endl << word << " >> " <<s_mapExpectedStatesToString[(EXPECT_UNKNOWN)];
      if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];
      error->unknownCmdOrVal = true;
      state = EXPECT_COMMAND;
      continue;
    }
    case EXPECT_NOTHING : {
      if(DEBUG) cout << endl << word << " >> " <<s_mapExpectedStatesToString[(EXPECT_UNKNOWN)];
      if(DEBUG) cout << endl << "command: " << s_mapEnumValuesToString[commandInfo->command];
      state = EXPECT_NOTHING;
      continue;
    }
    default : {
      if(DEBUG) cout << endl << "DEFAULT :{}";
      continue;
    }

    }
  }//end for loop

  //rgba must be explicitely stated to
  //create a new default color.
  if (defaultColor->newDefault == true) {
    if(defaultTest != 4)
      setDefaultColorValuesToWhite(defaultColor);

    defaultColor->newDefault = false;
  }

  if ((commandInfo->command == INSERT || commandInfo->command == MODIFY) && colorCount < 4) {
    setDefaultColorValues(color, defaultColor);
    error->missingColorValues = true;
  }
  //modify must have both row and column specified;
  if (commandInfo->modLoc == true)
    if(commandInfo->editRow  < 0 || commandInfo->editCol < 0 ) {
      commandInfo->command = ERROR;
      error->modifyRowOrColMissing = true;
    }

  /*test that commands and values are present*/
  if (commandInfo->command == INSERT && state == EXPECT_ROW && commandInfo->editRow < 0) {
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
  if (commandInfo->command == DELETE && state == EXPECT_ROW  && commandInfo->editRow < 0) {
    commandInfo->command = ERROR;
    error->missingRowValue = true;
  }

  if(error->invalidColorVal == true)
    commandInfo->command = ERROR;

  /*convert color to byte*/
  color->convertColorToPixel();

}

void  processConsoleArgs(int &argc, char* argv[], FileInfo* file) {
  if(argc != 2) {

    std::cerr << "\n*******************************************************************" << std::endl;
    std::cerr << "\nCOMMAND-LINE ERROR:";
    std::cerr << "\nUSAGE:GE5 [command-file name.txt] " << std::endl;
    std::cerr << "\n\tUser must specify a command-file name." << std::endl;
    std::cerr << "\tPlease ensure file exists and is in the same folder as the executable." << std::endl;
    std::cerr << "\n\tProgram terminated." << std::endl;
    std::cerr << "\n\n*******************************************************************" << std::endl;

    exit(0);
  } else file->fileName = argv[1];
}

void Color::convertColorToPixel() {
  // data for bitmap - in Big Endian, the order of 4 bytes for the pixel is Alpha, Red, Green, Blue from left to right
  // These bytes will be stored in Little Endian in memory and in the BMP file
  pixelColor = (alpha << 24) + (red << 16) + (green << 8) + blue;
}

//execution processes
void createDefaultBmpFile(FileInfo* file, Color* color) {
  // add values to grid vector starting with bottom row, then next to bottom row, and ending with top row
  for (file->gridIndex = 0; file->gridIndex < 100; file->gridIndex++) {
    // write out block letter C in blue on white background
    // logic for black c cells
    if (    file->gridIndex >= 80 && file->gridIndex <= 99
            ||  file->gridIndex >= 0  && file->gridIndex <= 20
            || (file->gridIndex+10)  % 10 == 0
            || (file->gridIndex+9 )  % 10 == 0
       )
      file->grid.push_back (0xFF000000); // black letter cells
    else
      file->grid.push_back (0xFFFFFFFF);  // background cell is white

    file->numCols = file->grid.size()/10;
    file->numRows = file->grid.size()/10;

  }
}

void writeBmpFile(FileInfo* file, CommandInfo* cmd, BMPHeader* bmp, DIBHeader* dib) {

  cout << "\n\n\tOutput file name: " << file->outFileName;

  cout << "\n\tWriting BMP file to disk..\n";
  // Now write the vector to disk
  file->outFile.open (file->outFileName, ios::binary);
  file->outFile.write (reinterpret_cast<char *> (bmp), sizeof (*bmp));
  file->outFile.write (reinterpret_cast<char *> (dib), sizeof (*dib));

  for (file->row = 0; file->row < file->numRows; file->row++)
    for (file->rowDupCount = 1; file->rowDupCount <= 50; file->rowDupCount++)
      for (file->col = 0; file->col< file->numCols; file->col++)
        for (file->colDupCount = 1; file->colDupCount <= 50; file->colDupCount++)
          // Note the file->col + file->row * numCols calculation maps the two-dimensional coordinate to a one-dimensional array (vector)
          file->outFile.write (reinterpret_cast<char *> (&(file->grid[file->col + file->row * file->numCols])), sizeof (unsigned int));

  cout << "\tFile write complete. \n\tPlease check " << file->outFileName << "\n";

  file->outFile.close();

  file->writtenToFile = true;

}

void quitProgram(FileInfo* file ) {
  file->readFile.seekg(0L, ios::end);

}

void editBitmap(FileInfo* file, CommandInfo* cmd, BMPHeader* bmp, DIBHeader* dib, Color* color, Color* newDefault, ErrorType* error) {
  switch(cmd->command) {
  case DEFAULT  : {
    break;
  }
  case INSERT    : {
    if(cmd->editRowTest) {
      insertRow(file, cmd, bmp, dib, color);
      break;
    }
    if(cmd->editColTest) {
      insertCol(file, cmd, bmp, dib, color);
      break;
    }
    cmd->command = ERROR;
    error->missingRowOrColType = true;
    editBitmap(file, cmd, bmp, dib, color, newDefault, error);
    break;
  }
  case DELETE    : {
    if(cmd->editRowTest) {
      deleteRow(file, cmd, bmp, dib);
      break;
    }
    if(cmd->editColTest) {
      deleteCol(file, cmd, bmp, dib);
      break;
    }
    cmd->command = ERROR;
    error->missingRowOrColType = true;
    editBitmap(file, cmd, bmp, dib, color, newDefault, error);
    break;
  }
  case MODIFY    : {
    modRowCol(file, cmd, color);
    break;
  }
  case WRITE    : {
    writeBmpFile(file, cmd, bmp, dib);
    break;
  }
  case QUIT    : {
    quitProgram(file);
    break;
  }
  case ERROR    : {
    break;
  }
  case BLANK    : {
    break;
  }
  default      : {
    break;
  }

  }



}

void insertRow(FileInfo* file, CommandInfo* cmd, BMPHeader* bmp, DIBHeader* dib, Color* color) {

  // Now lets insert row in the vector; convert to file output numbering
  int rowToInsert = file->numRows - cmd->editRow;

  cout << dec;
  if (DEBUG) {
    cout << "The current size of the vector grid is " << file->grid.size() << endl;
  }

  file->grid.insert(file->grid.begin() + (rowToInsert * file->numCols), file->numCols, color->pixelColor);
  file->numRows++;

  if (DEBUG) {
    cout << "After insertion, the new size of the vector is " << file->grid.size() << endl;
  }

  // First adjust values in bitmap header
  if (DEBUG) {
    cout << "The current bmp file size is " << bmp->bmpFileSize << endl;
  }
  bmp->bmpFileSize += 50 * 50 * 4 * file->numCols; // increase of 100,000 bytes
  if (DEBUG) {
    cout << "The new bmp file size is " << bmp->bmpFileSize << endl;
  }

  dib->heightBitmapInPixels += 50; // one row added increases height by 50 pixels
  if (DEBUG) {
    cout << "The new pixel height of bitmap is " << dib->heightBitmapInPixels << endl;
  }

  if (DEBUG) {
    cout << "The current size of the raw pixel data is " << dib->sizeRawDataInPixelArray << endl;
  }
  dib->sizeRawDataInPixelArray += 50 * 50 * 4 * file->numCols; // increase of 100,000 bytes
  if (DEBUG) {
    cout << "The new size of the raw pixel data is " << dib->sizeRawDataInPixelArray << endl;
  }

  cmd->editRowTest = false;
}

void deleteRow(FileInfo* file, CommandInfo* cmd, BMPHeader* bmp, DIBHeader* dib) {
  // Now how about deleting or erasing a row
  int rowToDelete = file->numRows - cmd->editRow - 1 ;

  cout << dec;
  if (DEBUG) {
    cout << "\nThe current size of the vector grid is " << file->grid.size() << endl;
  }

  file->grid.erase(file->grid.begin() + rowToDelete * file->numCols, file->grid.begin() + rowToDelete * file->numCols + file->numCols);
  file->numRows--;

  if (DEBUG) {
    cout << "After deletion, the new size of the vector is " << file->grid.size() << endl;
  }

  // First adjust values in bitmap header
  bmp->bmpFileSize -= 50 * 50 * 4 * file->numCols; // increase of 100,000 bytes
  if (DEBUG) {
    cout << "The new bmp file size is " << bmp->bmpFileSize << endl;
  }

  dib->heightBitmapInPixels -= 50; // one row added increases height by 50 pixels
  if (DEBUG) {
    cout << "The new pixel height of bitmap is " << dib->heightBitmapInPixels << endl;
  }

  dib->sizeRawDataInPixelArray -= 50 * 50 * 4 * file->numCols; // increase of 100,000 bytes
  if (DEBUG) {
    cout << "The new size of the raw pixel data is " << dib->sizeRawDataInPixelArray << endl;
  }

  cmd->editRowTest = false;

}

void insertCol(FileInfo* file, CommandInfo* cmd, BMPHeader* bmp, DIBHeader* dib, Color* color) {
  int colToInsert = cmd->editCol;
  int offset;

  cout << dec; // set display to decimal
  if (DEBUG) cout << "\nThe current size of the vector is " << file->grid.size() << endl;

  for(int row = 0; row < file->numRows; row++) {
    offset = row * file->numCols + colToInsert + row;
    file->grid.insert(file->grid.begin()+offset, color->pixelColor);
  }
  file->numCols++;

  if (DEBUG) cout << "\nThe new size of the vector is " << file->grid.size() << endl;

  // First adjust values in bitmap header
  if (DEBUG) cout << "The current bmp file size is " << bmp->bmpFileSize << endl;
  if (DEBUG) cout << "The current size of the raw pixel data is " << dib->sizeRawDataInPixelArray << endl;
  if (DEBUG) cout << "The current size of numCols is " << file->numCols << endl;

  bmp->bmpFileSize += 50 * 50 * 4 * file->numRows; // increase of 100,000 bytes
  if (DEBUG) cout << "The new bmp file size is " << bmp->bmpFileSize << endl;

  dib->widthBitmapInPixels += 50; // one row added increases height by 50 pixels
  if (DEBUG) cout << "The new pixel width of bitmap is " << dib->widthBitmapInPixels << endl;

  dib->sizeRawDataInPixelArray += 50 * 50 * 4 * file->numRows; // increase of 100,000 bytes
  if (DEBUG) cout << "The new size of the raw pixel data is " << dib->sizeRawDataInPixelArray << endl;

  cmd->editColTest = false;

} // end insertColumn

void deleteCol(FileInfo* file, CommandInfo* cmd, BMPHeader* bmp, DIBHeader* dib) {
  int colToErase;
  int offset;

  cout << dec; // set display to decimal
  if (DEBUG) cout << "\nThe current size of the vector is " << file->grid.size() << endl;

  for(int row = 0; row < file->numRows; row++) {
    offset = (row * file->numCols + cmd->editCol - row);
    if(DEBUG) cout << endl << "offset: " << offset;
    file->grid.erase(file->grid.begin()+offset, file->grid.begin()+offset+1);
  }
  file->numCols--;


  if (DEBUG) cout << "\nThe new size of the vector is " << file->grid.size() << endl;

  // First adjust values in bitmap header
  if (DEBUG) cout << "The current bmp file size is " << bmp->bmpFileSize << endl;
  if (DEBUG) cout << "The current size of the raw pixel data is " << dib->sizeRawDataInPixelArray << endl;

  bmp->bmpFileSize -= 50 * 50 * 4 * file->numRows; // increase of 100,000 bytes
  if (DEBUG) cout << "The new bmp file size is " << bmp->bmpFileSize << endl;

  dib->widthBitmapInPixels -= 50; // one row added increases height by 50 pixels
  if (DEBUG) cout << "The new pixel height of bitmap is " << dib->heightBitmapInPixels << endl;

  dib->sizeRawDataInPixelArray -= 50 * 50 * 4 * file->numRows; // increase of 100,000 bytes
  if (DEBUG) cout << "The new size of the raw pixel data is " << dib->sizeRawDataInPixelArray << endl;

  cmd->editColTest = false;


} // end insertColumn

void modRowCol(FileInfo* file, CommandInfo* cmd, Color* color) {
  int row = file->numRows - cmd->editRow - 1;
  int col = cmd->editCol;
  int modLocation = (row*(file->numRows))+col;

  file->grid[modLocation] = color->pixelColor;

  cmd->modLoc = false;
}

//closing functions
void closeFiles(FileInfo* file) {
  if(file->readFile)
    file->readFile.close();
  if(file->outFile)
    file->outFile.close();
}

/*-----------------------------------------------------------------------------*\
|  Primary Function : Free Dynamically Allocated Memory for Argv pointer array  |
\*-----------------------------------------------------------------------------*/
void freeDynamicallyAllocatedArgv(FileInfo *file) {
  /*  This function frees all the dynamically allocated memory used by the fileArgv variable  */

  /*  Declare and Initialize Variables  */
  int i = 0;                              /*  Standard Iteration Variable            */

  /*  Begin a loop through the pointers in fileArgv as limited by the int in fileArgc  */
  for ( i = 0 ; i < file->fileArgc ; i++ ) {
    /*  Free the memory for the char array pointed to by element i of fileArgv  */
    free(file->fileArgv[i]);

  }   /*  end for  */

  /*  Free (Delete) the dynamically allocated memory for the char pointer array fileArgv  */
  delete [] file->fileArgv;

}   /*  end function freeDynamicallyAllocatedArgv  */
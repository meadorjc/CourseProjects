/*****************************************************
*	Caleb Meador
*	COSC1437 GE#6 , Fall, 2013
*	Filename:Bitmap.cpp
*	12/05/2013
*
********************************************************/
#include "Bitmap.h"
#include <iostream>
#include <fstream>
using namespace std;



Bitmap::Bitmap()
{
    DEBUG_BMP = 0;

    if (DEBUG_BMP) cout << "Executing Bitmap no-arg constructor" << endl;

    setDefaultColors(&color);         //colors to white
    setDefaultColors(&defaultColor); //colors to white
    setBmpDefault();
    setDibDefault();

    calcTotalRowCount();
    calcTotalColCount();

    unsigned int count = 1;            //for DEBUG_BMP only

    unsigned int bytesInFirstRow = dibHeader.widthBitmapInPixels * INT_SIZE;       // width * 4;  #chars in first row; get color data from here
    unsigned int bytesInFullRow = dibHeader.widthBitmapInPixels * REPS * INT_SIZE; // width*50*4; #chars duplicated; skip all of this
    unsigned int bytesInCol = REPS*INT_SIZE;

    if(DEBUG_BMP)
    {
        cout << "The size of the bmp header structure is " << sizeof (bmpHeader) << endl;
        cout << "The size of the dib header structure is " << sizeof (dibHeader) << endl;
    }
    // add values to grid vector starting with bottom row,
    //then next to bottom row, and ending with top row
    for (int gridIndex = 0; gridIndex < 100; gridIndex++)
    {
        // write out block letter C in blue on white background
        // logic for black c cells
        if (    gridIndex >= 80 && gridIndex <= 99
                ||  gridIndex >= 0  && gridIndex <= 20
                || (gridIndex+10)  % 10 == 0
                || (gridIndex+9 )  % 10 == 0
           )
            grid.push_back (0xFFFF0000); // red letter cells
        else
            grid.push_back (0xFFFFFFFF);  // background cell is white

        dibHeader.setHeightBitmapInPixels(grid.size()*5);
        dibHeader.setWidthBitmapInPixels( grid.size()*5);
    }
}

Bitmap::Bitmap(string name)
{
    DEBUG_BMP = 0;
    setDefaultColors(&color); //colors to white
    setDefaultColors(&defaultColor); //colors to white

    ifstream inFile;
    inFile.open(name, ios::in|ios::binary|ios::ate);

    printf("\n\t\tReading %s.\n", name.c_str());

    if (inFile)
    {

        int fileSize;

        //set file size
        fileSize = inFile.tellg();

        if(DEBUG_BMP) cout << endl << endl << "fileSize: " << fileSize << endl;

        //set pointer to beginning of file
        inFile.seekg(0L, ios::beg);

        printf("\n\t\tReading and storing header data.\n");

        //read char, bitshift, and assign. Unless noted, all variables are unsigned ints
        //bmp ---------------------------------------------------------------------------------------------------------------------------------
        getByteAndShift(&bmpHeader.fileSignature[0], NULL, NULL, sizeof(bmpHeader.fileSignature[0]), inFile); //char
        getByteAndShift(&bmpHeader.fileSignature[1], NULL, NULL, sizeof(bmpHeader.fileSignature[0]), inFile); //char
        getByteAndShift(NULL, NULL, &bmpHeader.bmpFileSize, sizeof(bmpHeader.bmpFileSize), inFile);
        getByteAndShift(NULL, &bmpHeader.unused_1, NULL, sizeof(bmpHeader.unused_1 ), inFile);//unsigned short
        getByteAndShift(NULL, &bmpHeader.unused_2, NULL, sizeof(bmpHeader.unused_2 ), inFile);//unsigned short
        getByteAndShift(NULL, NULL, &bmpHeader.pixelOffset , sizeof(bmpHeader.pixelOffset), inFile);

        //dibHeader --------------------------------------------------------------------------------------------------------------------------------
        getByteAndShift(NULL, NULL, &dibHeader.numBytesDIBHeader    , sizeof(dibHeader.numBytesDIBHeader    ), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.widthBitmapInPixels  , sizeof(dibHeader.widthBitmapInPixels  ), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.heightBitmapInPixels , sizeof(dibHeader.heightBitmapInPixels ), inFile);
        getByteAndShift(NULL, &dibHeader.numColorPlanes       , NULL, sizeof(dibHeader.numColorPlanes       ), inFile);//unsigned short
        getByteAndShift(NULL, &dibHeader.numBitsPerPixel      , NULL, sizeof(dibHeader.numBitsPerPixel      ), inFile);//unsigned short
        getByteAndShift(NULL, NULL, &dibHeader.typeCompression      , sizeof(dibHeader.typeCompression      ), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.sizeRawDataInPixelArray , sizeof(dibHeader.sizeRawDataInPixelArray ), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.horizPhysicalResolution , sizeof(dibHeader.horizPhysicalResolution ), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.vertPhysicalResolution  , sizeof(dibHeader.vertPhysicalResolution  ), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.numColorsInPalette  , sizeof(dibHeader.numColorsInPalette  ), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.importantColors     , sizeof(dibHeader.importantColors     ), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.redChannelBitMask   , sizeof(dibHeader.redChannelBitMask   ), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.greenChannelBitMask , sizeof(dibHeader.greenChannelBitMask ), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.blueChannelBitMask  , sizeof(dibHeader.blueChannelBitMask  ), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.alphaChannelBitMask , sizeof(dibHeader.alphaChannelBitMask ), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.typeOfColorSpace    , sizeof(dibHeader.typeOfColorSpace    ), inFile);
        for(int i = 0; i < 9; i++)
            getByteAndShift(NULL, NULL, &dibHeader.colorSpaceEndPoints[i], sizeof(dibHeader.colorSpaceEndPoints[i]), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.redGamma   , sizeof(dibHeader.redGamma   ), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.greenGamma , sizeof(dibHeader.greenGamma ), inFile);
        getByteAndShift(NULL, NULL, &dibHeader.blueGamma  , sizeof(dibHeader.blueGamma  ), inFile);

        calcTotalRowCount();
        calcTotalColCount();

        if (DEBUG_BMP) cout << endl << endl << inFile.tellg() << endl << endl;
        if (DEBUG_BMP) displayHeaders();

        printf("\n\t\tReading and storing color in vector.\n");
        /**************************************************************************************************************************************
          To reproduce the original multidimensional array, iterate through rows and cols skipping duplicated data.
          Set the inFile pointer to the current loc.
          Use vector.push_back() to automatically reverse the order.
          Get 4 consecutive bytes and bitshift into big endian order.

        ***************************************************************************************************************************************/
        unsigned int count = 1;

        unsigned int bytesInFirstRow = dibHeader.widthBitmapInPixels * INT_SIZE;       // width * 4;  #chars in first row; get color data from here
        unsigned int bytesInFullRow = dibHeader.widthBitmapInPixels * REPS * INT_SIZE; // width*50*4; #chars duplicated; skip all of this
        unsigned int bytesInCol = REPS*INT_SIZE;                                 // 50*4;       #chars duplicated in col; skip it.

        if (DEBUG_BMP) printf("BIT_SHIFT_8 %d BIT_SHIFT_16 %d BIT_SHIFT_24: %d\n\n", BIT_SHIFT_8, BIT_SHIFT_16, BIT_SHIFT_24);
        if (DEBUG_BMP) printf("firstrow: %u fullrow: %u  bytesinCol: %u\n\n", bytesInFirstRow, bytesInFullRow, bytesInCol);

        for (unsigned int row = bmpHeader.pixelOffset; row < fileSize; row += bytesInFullRow)
        {
            for(unsigned int col = row; col < (row + bytesInFirstRow); col += bytesInCol)
            {
                inFile.seekg( col );                                                  //set inFile pointer
                grid.push_back( inFile.get() + (inFile.get() << BIT_SHIFT_8) + (inFile.get() << BIT_SHIFT_16) + (inFile.get()<< BIT_SHIFT_24));

                if (DEBUG_BMP) printf("%u %u %u %x %u\n", row, col, count++, grid[count], (unsigned int)(inFile.tellg()));
            } //inner-for
        }   //outer-for


        inFile.close();

    }//end of if-statement
}//end of no-arg Bitmap


void Bitmap::writeToFile(string outFileName, vector<unsigned int> grid)
{
    ofstream outFile;

    cout << "\n\n\tOutput file name: " << outFileName;

    cout << "\n\tWriting BMP file to disk..\n";
    // Now write the vector to disk
    outFile.open (outFileName, ios::binary);
    outFile.write (reinterpret_cast<char *> (&bmpHeader), sizeof (bmpHeader));
    outFile.write (reinterpret_cast<char *> (&dibHeader), sizeof (dibHeader));

    unsigned int totalRowCount = dibHeader.heightBitmapInPixels/REPS;
    unsigned int totalColCount = dibHeader.widthBitmapInPixels/REPS;

    for (unsigned int row = 0; row < totalRowCount; row++)
        for (unsigned int rowDupCount = 1; rowDupCount <= REPS; rowDupCount++)
            for (unsigned int col = 0; col < totalColCount; col++)
                for (unsigned int colDupCount = 1; colDupCount <= REPS; colDupCount++)
                    // Note the file->col + file->row * numCols calculation maps the two-dimensional coordinate to a one-dimensional array (vector)
                    outFile.write (reinterpret_cast<char *> (&(grid[col + row * totalColCount])), sizeof (unsigned int));

    cout << "\tFile write complete. \n\tPlease check " << outFileName << "\n";

    outFile.close();

    //writtenToFile = true; //implement at writeToFile call!!

}


void Bitmap::convertColorToPixel()
// data for bitmap - in Big Endian, the order of 4 bytes for the pixel is Alpha, Red, Green, Blue from left to right
// These bytes will be stored in Little Endian in memory and in the BMP file

{
    color.pixelColor = (color.alpha << 24) + (color.red << 16) + (color.green << 8) + color.blue;
}



void Bitmap::insertCol (int colToInsert)
{
    int offset;

    cout << dec; // set display to decimal
    if (DEBUG_BMP) cout << "\nThe current size of the vector is " << grid.size() << endl;

    for(unsigned int row = 0; row < totalRowCount; row++)
    {
        offset = row * totalColCount + colToInsert + row;
        grid.insert(grid.begin()+offset, color.pixelColor);
    }
    totalColCount++;

    if (DEBUG_BMP) cout << "\nThe new size of the vector is " << grid.size() << endl;

    // First adjust values in bitmap header
    if (DEBUG_BMP) cout << "The current bmp file size is " << bmpHeader.bmpFileSize << endl;
    if (DEBUG_BMP) cout << "The current size of the raw pixel data is " << dibHeader.sizeRawDataInPixelArray << endl;
    if (DEBUG_BMP) cout << "The current size of totalColCount is " << totalColCount << endl;

    bmpHeader.bmpFileSize += 50 * 50 * 4 * totalColCount; // increase of 100,000 bytes
    if (DEBUG_BMP) cout << "The new bmp file size is " << bmpHeader.bmpFileSize << endl;

    dibHeader.widthBitmapInPixels += 50; // one row added increases height by 50 pixels
    if (DEBUG_BMP) cout << "The new pixel width of bitmap is " << dibHeader.widthBitmapInPixels << endl;

    dibHeader.sizeRawDataInPixelArray += 50 * 50 * 4 * totalRowCount; // increase of 100,000 bytes
    if (DEBUG_BMP) cout << "The new size of the raw pixel data is " << dibHeader.sizeRawDataInPixelArray << endl;

    calcTotalColCount(); //TO DO is this necessary??
    //cmd->editColTest = false; TO DO make sure this is reset after!

} // end insertColumn

void Bitmap::deleteCol(int colToDelete)
{
    int offset;

    cout << dec; // set display to decimal
    if (DEBUG_BMP) cout << "\nThe current size of the vector is " << grid.size() << endl;

    for(unsigned int row = 0; row < totalRowCount; row++)
    {
        offset = (row * totalColCount + colToDelete - row);
        if(DEBUG_BMP) cout << endl << "offset: " << offset;
        grid.erase(grid.begin()+offset, grid.begin()+offset+1);
    }
    totalColCount--;


    if (DEBUG_BMP) cout << "\nThe new size of the vector is " << grid.size() << endl;

    // First adjust values in bitmap header
    if (DEBUG_BMP) cout << "The current bmp file size is " << bmpHeader.bmpFileSize << endl;
    if (DEBUG_BMP) cout << "The current size of the raw pixel data is " << dibHeader.sizeRawDataInPixelArray << endl;

    bmpHeader.bmpFileSize -= 50 * 50 * 4 * totalRowCount; // increase of 100,000 bytes
    if (DEBUG_BMP) cout << "The new bmp file size is " << bmpHeader.bmpFileSize << endl;

    dibHeader.widthBitmapInPixels -= 50; // one row added increases height by 50 pixels
    if (DEBUG_BMP) cout << "The new pixel height of bitmap is " << dibHeader.heightBitmapInPixels << endl;

    dibHeader.sizeRawDataInPixelArray -= 50 * 50 * 4 * totalRowCount; // increase of 100,000 bytes
    if (DEBUG_BMP) cout << "The new size of the raw pixel data is " << dibHeader.sizeRawDataInPixelArray << endl;

    //cmd->editColTest = false; //to do: set this in main

    calcTotalColCount(); //to do check to see if necessary.


} // end deleteCol

void Bitmap::modRowCol(int rowToEdit, int colToEdit)
{
    int row = totalRowCount - rowToEdit - 1;
    int modLocation = (row*(totalRowCount))+colToEdit;

    grid[modLocation] = color.pixelColor;

    //cmd->modLoc = false; TO DO flag in main()
}




void Bitmap::insertRow (int rowToInsert)
{

    // Now lets insert row in the vector; convert to file output numbering
    rowToInsert = totalRowCount - rowToInsert;

    cout << dec;
    if (DEBUG_BMP)
    {
        cout << "The current size of the vector grid is " << grid.size() << endl;
    }

    grid.insert(grid.begin() + (rowToInsert * totalColCount), totalColCount, color.pixelColor);
    totalRowCount++;

    if (DEBUG_BMP)
    {
        cout << "After insertion, the new size of the vector is " << grid.size() << endl;
    }

    // First adjust values in bitmap header
    if (DEBUG_BMP)
    {
        cout << "The current bmp file size is " << bmpHeader.bmpFileSize << endl;
    }
    bmpHeader.bmpFileSize += 50 * 50 * 4 * totalColCount; // increase of 100,000 bytes
    if (DEBUG_BMP)
    {
        cout << "The new bmp file size is " << bmpHeader.bmpFileSize << endl;
    }

    dibHeader.heightBitmapInPixels += 50; // one row added increases height by 50 pixels
    if (DEBUG_BMP)
    {
        cout << "The new pixel height of bitmap is " << dibHeader.heightBitmapInPixels << endl;
    }

    if (DEBUG_BMP)
    {
        cout << "The current size of the raw pixel data is " << dibHeader.sizeRawDataInPixelArray << endl;
    }
    dibHeader.sizeRawDataInPixelArray += 50 * 50 * 4 * totalColCount; // increase of 100,000 bytes
    if (DEBUG_BMP)
    {
        cout << "The new size of the raw pixel data is " << dibHeader.sizeRawDataInPixelArray << endl;
    }

    calcTotalRowCount(); //TO DO // see if this is necessary?
    //cmd->editRowTest = false; //TO DO implement in main() if necessary

} // end insertRow


void Bitmap::deleteRow(int rowToDelete)
{

    // Now how about deleting or erasing a row
    rowToDelete = totalRowCount - rowToDelete - 1 ;

    cout << dec;
    if (DEBUG_BMP)
    {
        cout << "\nThe current size of the vector grid is " << grid.size() << endl;
    }

    grid.erase(grid.begin() + rowToDelete * totalColCount, grid.begin() + rowToDelete * totalColCount + totalColCount);
    totalRowCount--;

    if (DEBUG_BMP)
    {
        cout << "After deletion, the new size of the vector is " << grid.size() << endl;
    }

    // First adjust values in bitmap header
    bmpHeader.bmpFileSize -= 50 * 50 * 4 * totalColCount; // increase of 100,000 bytes
    if (DEBUG_BMP)
    {
        cout << "The new bmp file size is " << bmpHeader.bmpFileSize << endl;
    }

    dibHeader.heightBitmapInPixels -= 50; // one row added increases height by 50 pixels
    if (DEBUG_BMP)
    {
        cout << "The new pixel height of bitmap is " << dibHeader.heightBitmapInPixels << endl;
    }

    dibHeader.sizeRawDataInPixelArray -= 50 * 50 * 4 * totalColCount; // increase of 100,000 bytes
    if (DEBUG_BMP)
    {
        cout << "The new size of the raw pixel data is " << dibHeader.sizeRawDataInPixelArray << endl;
    }

    //cmd->editRowTest = false; TO DO turn off in main();

    //calcTotalRowCount(); //To DO: necessary?

}


void Bitmap::setBmpDefault()
{
    bmpHeader.fileSignature[0] = 'B';
    bmpHeader.fileSignature[1] = 'M';
    bmpHeader.bmpFileSize = 1000122;
    bmpHeader.unused_1 = 0;
    bmpHeader.unused_2 = 0;
    bmpHeader.pixelOffset = 122;
}

void Bitmap::setDibDefault()
{
    dibHeader.numBytesDIBHeader		  = 108;
    dibHeader.widthBitmapInPixels		= 500;
    dibHeader.heightBitmapInPixels		= 500;
    dibHeader.numColorPlanes			    = 1;
    dibHeader.numBitsPerPixel			  = 32;
    dibHeader.typeCompression			  = 3;
    dibHeader.sizeRawDataInPixelArray  = 1000000;
    dibHeader.horizPhysicalResolution	= 2835;
    dibHeader.vertPhysicalResolution	  = 2835;
    dibHeader.numColorsInPalette		  = 0;
    dibHeader.importantColors			  = 0;
    dibHeader.redChannelBitMask		  = 0x00FF0000;
    dibHeader.greenChannelBitMask		= 0x0000FF00;
    dibHeader.blueChannelBitMask		  = 0x000000FF;
    dibHeader.alphaChannelBitMask		= 0xFF000000;
    dibHeader.typeOfColorSpace			  = 0x57696E20;
    dibHeader.colorSpaceEndPoints[9]	= 0;
    dibHeader.redGamma					= 0;
    dibHeader.greenGamma				= 0;
    dibHeader.blueGamma				= 0;
}

//Display header info for DEBUG_BMP purposes
void Bitmap::displayHeaders()
{
    cout << endl << endl;
    cout << endl << "BMP Header " << dec;
    cout << endl << "bmpHeader.fileSignature[0] " << bmpHeader.fileSignature[0];
    cout << endl << "bmpHeader.fileSignature[1] " << bmpHeader.fileSignature[1];
    cout << endl << "bmpHeader.bmpFileSize " << bmpHeader.bmpFileSize ;
    cout << endl << "bmpHeader.unused_1 " << bmpHeader.unused_1 ;
    cout << endl << "bmpHeader.unused_2 " << bmpHeader.unused_2 ;
    cout << endl << "bmpHeader.pixelOffset " << bmpHeader.pixelOffset ;

    cout << endl << "DIB Header";
    cout << endl << "dibHeader.numBytesdib " <<   dibHeader.numBytesDIBHeader;
    cout << endl << "dibHeader.widthBitmapInPixels " << dibHeader.widthBitmapInPixels;
    cout << endl << "dibHeader.heightBitmapInPixels " << dibHeader.heightBitmapInPixels;
    cout << endl << "dibHeader.numColorPlanes " << dibHeader.numColorPlanes;
    cout << endl << "dibHeader.numBitsPerPixel " << dibHeader.numBitsPerPixel;
    cout << endl << "dibHeader.typeCompression " << dibHeader.typeCompression;
    cout << endl << "dibHeader.sizeRawDataInPixelArray " << dibHeader.sizeRawDataInPixelArray;
    cout << endl << "dibHeader.horizPhysicalResolution " << dibHeader.horizPhysicalResolution;
    cout << endl << "dibHeader.vertPhysicalResolution " << dibHeader.vertPhysicalResolution;
    cout << endl << "dibHeader.numColorsInPalette " << dibHeader.numColorsInPalette;
    cout << endl << "dibHeader.importantColors " << dibHeader.importantColors;
    cout << endl << "dibHeader.redChannelBitMask " << dibHeader.redChannelBitMask;
    cout << endl << "dibHeader.greenChannelBitMask " << dibHeader.greenChannelBitMask;
    cout << endl << "dibHeader.blueChannelBitMask " << dibHeader.blueChannelBitMask;
    cout << endl << "dibHeader.alphaChannelBitMask " << dibHeader.alphaChannelBitMask;
    cout << endl << "dibHeader.typeOfColorSpace " << dibHeader.typeOfColorSpace;
    cout << endl << "dibHeader.colorSpaceEndPoints[9] " << dibHeader.colorSpaceEndPoints[9];
    cout << endl << "dibHeader.redGamma " << dibHeader.redGamma;
    cout << endl << "dibHeader.greenGamma " << dibHeader.greenGamma;
    cout << endl << "dibHeader.blueGamma " << dibHeader.blueGamma;


}

//standard can accept color or newDefaultColor
void Bitmap::setDefaultColors(Color* c)
{
    c->red = 255;
    c->green = 255;
    c->blue = 255;
    c->alpha = 255;
    c->newDefault = false;
}
//overloaded
void Bitmap::setDefaultColors()
{
    color.red  = defaultColor.red;
    color.green  = defaultColor.green;
    color.blue  = defaultColor.blue;
    color.alpha  = defaultColor.alpha;
    defaultColor.newDefault  = false;
}

void Bitmap::displayVectorGrid()
{
    int vectorCount = totalRowCount*totalColCount;

    cout << endl << endl;
    for(unsigned int i = 0; i < totalRowCount; i++)
    {
        cout << endl;
        vectorCount -= totalColCount;
        for (unsigned int j = 0; j < totalColCount; j++)
        {
            cout << vectorCount++ << "\t";

        }
        vectorCount -= totalColCount;
    }

    for (int i = 0; i < grid.size(); i++)
        cout << endl << i << " " << hex << grid[i];




}

//DEBUG_BMP: will take color or newDefault
void Bitmap::displayColorInfo ()
{
    cout << endl;
    cout << endl << boolalpha	<< "newDefault: \t" << color.newDefault;
    cout << endl << setw(6)		<< "red  \t"	 << setw(4) << color.red	<< " address: " << setw(6) << &color.red;
    cout << endl << setw(6)		<< "green\t"	 << setw(4) << color.green << " address: " << setw(6) << &color.green;
    cout << endl << setw(6)		<< "blue \t"	 << setw(4) << color.blue	<< " address: " << setw(6) << &color.blue;
    cout << endl << setw(6)		<< "alpha\t"	 << setw(4) << color.alpha << " address: " << setw(6) << &color.alpha;

    cout << endl;
    cout << endl << boolalpha	<< "defaultColor: \t" << defaultColor.newDefault;
    cout << endl << setw(6)		<< "red  \t"	 << setw(4) << defaultColor.red	<< " address: " << setw(6) << &defaultColor.red;
    cout << endl << setw(6)		<< "green\t"	 << setw(4) << defaultColor.green << " address: " << setw(6) << &defaultColor.green;
    cout << endl << setw(6)		<< "blue \t"	 << setw(4) << defaultColor.blue	<< " address: " << setw(6) << &defaultColor.blue;
    cout << endl << setw(6)		<< "alpha\t"	 << setw(4) << defaultColor.alpha << " address: " << setw(6) << &defaultColor.alpha;


}

//read char, bitshift, and assign. Unless noted, all variables are unsigned ints
/**************************************************************************************************************************************
  Because data is stored in little-endian format (the smallest numeral is on the left), bytes within data-types must be reversed to
 big-endian (the biggest numeral is on the left) by shifting them by 0 and 8 bytes, and 0, 8, 16, and 24 bytes for shorts and ints,
 respectively.

***************************************************************************************************************************************/

void Bitmap::getByteAndShift(char* tempChar, unsigned short* tempShort, unsigned int* tempInt, int size, ifstream &inFile)
{
    switch(size)
    {
    case 1:
    {
        *tempChar = inFile.get();
        break;

    }
    case 2:
    {
        *tempShort = (inFile.get()) + (inFile.get() << BIT_SHIFT_8);
        break;
    }
    case 4:
    {
        *tempInt = (inFile.get()) + (inFile.get() << BIT_SHIFT_8) + (inFile.get() << BIT_SHIFT_16) + (inFile.get()<< BIT_SHIFT_24);
        break;
    }

    }
}

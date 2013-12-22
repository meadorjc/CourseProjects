/*****************************************************
*	Caleb Meador
*	COSC1437 GE#6 , Fall, 2013
*	Filename:StegoBitmap.h
*	12/05/2013
*
********************************************************/
#include "StegoBitmap.h"

  //Following code provided in class
  void StegoBitmap::hideFileInBMPFile(string fileToHideInName, string fileToHideName) 
  {
    
    string fileWithHiddenDataName = fileToHideInName;
    fileWithHiddenDataName.replace(fileToHideInName.length()-4, 4, "withHiddenFile.bmp");

    // Read from original BMP file and creates and write to new BMP file with hidden data 
    ifstream fileToHide(fileToHideName, ios::in | ios::binary | ios::ate);           // read only ; set to end
    ifstream originalBMPFile (fileToHideInName, ios::in | ios::binary | ios::ate);	          // read-only 
    ofstream carrierFile (fileWithHiddenDataName, ios::out | ios::binary);                 // create-write

    if (fileToHide.fail()) { cout << "\n\tError opening file to hide" << endl; return;}
    if (originalBMPFile.fail()) { cout << "\n\tError opening original BMP file" << endl; return;}
    if (carrierFile.fail()) { cout << "\n\tError creating/opening carrier file" << endl; return;}

    int fileToHideSize = fileToHide.tellg();      //preset to eof; tellg() to get filesize 
    int fileToHideInSize = originalBMPFile.tellg(); //preset to eof; tellg() to get filesize
    
    //throw exception if (filesize * bits) is too big to hide in original file.
    if ((fileToHideSize*8)+32+64 > fileToHideInSize) throw hideFileTooBig();

    if (DEBUG_STEGO) cout << "File Size data " <<  fileToHideSize << " " << fileToHideInSize <<  endl;


    fileToHide.seekg (0L, ios::beg);        // position read pointer to start of fileToHide
    originalBMPFile.seekg(0L, ios::beg);  // position read pointer to start of fileToHide

    // copy headers from original BMP file to carrier file
    char temp[HEADER_OFFSET];
    originalBMPFile.read (temp, HEADER_OFFSET);
    carrierFile.write (temp, HEADER_OFFSET);

    // position read and write pointers to start of pixel data
    originalBMPFile.seekg ((long)HEADER_OFFSET, ios::beg); // should already be positioned here
    carrierFile.seekp ((long)HEADER_OFFSET, ios::beg);

    if (DEBUG_STEGO)
    {
       cout << "Ready to begin writing file size data" << endl;
       cout << "File write pointer at: " << carrierFile.tellp() << endl;
       cout << "File read pointer at: " << originalBMPFile.tellg() << endl;
    }

    // Hide file size of hidden file in first 32 bytes of carrierFile
    // I.E. In big endian 61163 is hex: 00 00 EE EB and binary: 0000 0000 0000 0000 1110 1110 1110 1011
    // We will hide the bits in the file in big endian order or MSB first

    char byteToModify;
    int tempFileSize = fileToHideSize;

    if (DEBUG_STEGO) cout << "Writing file size data" << endl;
    for (int bitCount = 1; bitCount <= 32; bitCount++)
    {
      originalBMPFile.get(byteToModify);
      ((tempFileSize & INT_TEST_MASK) == INT_TEST_MASK) ? byteToModify |= SET_MASK : byteToModify &= CLEAR_MASK;
      tempFileSize = tempFileSize << 1;        // shift bits left so we can examine the next bit on next iteration
      carrierFile.put(byteToModify);            
    }  

    if (DEBUG_STEGO)
    {
       cout << "Done writing file size data" << endl;
       cout << "File read pointer at: " << originalBMPFile.tellg() << endl;
       cout << "File write pointer at: " << carrierFile.tellp() << endl;
    }

  
    // The next 64 bytes of the carrier file will be reserved for future use to store the ASCII characters of the extension of the hidden file.
    // 64 bytes allows an 8 character extension to be hidden. Most extensions just use 3 characters. The unused bits of the extension should be set
    // to 0 bits.

    // FUTURE VERSION TO DO: add the file extension code code here - for now just copy data from original
    char temp64[64];
    originalBMPFile.read (temp64, 64);
    carrierFile.write (temp64, 64);

    if (DEBUG_STEGO)
    {
       cout << "Finished reserving space for file name extension" << endl;
       cout << "File read pointer at: " << originalBMPFile.tellg() << endl;
       cout << "File write pointer at: " << carrierFile.tellp() << endl;
    }     

    char hiddenFileByte;

    // process each byte in the file to hide
    for (int numBytesToProcess = 1; numBytesToProcess <= fileToHideSize; numBytesToProcess++)  
    {
      fileToHide.get(hiddenFileByte);                 
      // Now loop through the 8 bits of this hidden file byte, using each bit to modify one byte of carrier file
      // Process the MSB (left bit) first and work from left to right
      for (int bitCount = 1; bitCount <= 8; bitCount++)
      {
        originalBMPFile.get(byteToModify);
        ((hiddenFileByte & BYTE_TEST_MASK) == BYTE_TEST_MASK) ? (byteToModify |= SET_MASK) : (byteToModify &= CLEAR_MASK);
        hiddenFileByte = hiddenFileByte << 1; // shift bits left so we can examine the next bit on next iteration
        carrierFile.put(byteToModify);    
      }
    }

    int bmpPixelBytesToModify = fileToHideSize * 8; //calc for later
    int bmpPixelBytes = fileToHideInSize;
    // Now finish by copying remaining bytes from originalBMPFile to carrierFile
    int numBytesToCopy = bmpPixelBytes - bmpPixelBytesToModify- BYTES_TO_STORE_FILE_SIZE - BYTES_TO_STORE_FILE_EXTENSION;
    char * ptrBytesToCopy = new char [numBytesToCopy];
    originalBMPFile.read (ptrBytesToCopy, numBytesToCopy);
    carrierFile.write (ptrBytesToCopy, numBytesToCopy);
    delete [] ptrBytesToCopy;

    if (DEBUG_STEGO)
    {
       cout << "Finished creating carrier file" << endl;
       cout << "Original BMP file read pointer at: " << originalBMPFile.tellg() << endl;
       cout << "Carrier file write pointer at: " << carrierFile.tellp() << endl;
       cout << "Hidden file pointer at: " << fileToHide.tellg() << endl;
    }


    fileToHide.close();
    carrierFile.close();   
    originalBMPFile.close();
  
}

  //retrieveFileFromBMPFile fileWithHiddenData.BMP fileToReveal.xyz
  //TO DO exception handling
  void StegoBitmap::retrieveFileFromBMPFile(string fileWithHiddenData, string fileToFind)
  {
   // Read from original BMP file and creates and write to new BMP file with hidden data 
    ifstream carrierFile(fileWithHiddenData, ios::in | ios::binary | ios::ate);               // read only
    ofstream fileToWrite (fileToFind, ios::out | ios::binary);	                        // create-write

    if (carrierFile.fail()) { cout << "\n\n\t\tError opening file to hide" << endl; return;}
    if (fileToWrite.fail()) { cout << "\n\n\t\tError creating/opening carrier file" << endl; return;}

    //get carrierFile size
    int carrierFileSize = carrierFile.tellg();

    // position read and write pointers to start of pixel data
    carrierFile.seekg (122L, ios::beg); //start writing after header
    fileToWrite.seekp (0L, ios::beg);


    // Hide file size of hidden file in first 32 bytes of carrierFile
    // Hidden bits are in the file in big endian order or MSB first
    unsigned int fileSize = 0;
		unsigned char quarterInt[4] = {0};
        
		for(int byte = 0; byte < 4; byte++)       //loop through (4*8) bytes to create 4 bytes
			for(int bit = 7; bit >= 0; bit--)        // loop through 8 bytes to create 1 bit
				//if least sig.fig is 1, shift 1, else 0 into quarterInt by bit# positions 
		    quarterInt[byte] |= ((carrierFile.get() & SET_MASK) == SET_MASK ? 1 : 0) << bit;  
		
    //shift 4 quarterInts into a single unsigned int
    fileSize = (quarterInt[0] << 24) + (quarterInt[1] << 16) + (quarterInt[2] << 8) + quarterInt[3];
    
    //throw exception at negative/inconsistent file size
    if(fileSize < 0)                 throw negativeHiddenFileSize();
    if((fileSize*8)+32+64 > carrierFileSize) throw hiddenFileSizeInconsistancy();
      

    char hiddenFileByte; //byte with code
    char byteToWrite;    //decoded byte

    //set coded file to start after header+fileSize+extension
	  carrierFile.seekg(122+BYTES_TO_STORE_FILE_SIZE+BYTES_TO_STORE_FILE_EXTENSION);

    if(DEBUG_STEGO)  cout << "Writing file size data " << fileSize << endl;

    // process fileSize # of bytes in the stegonographed file
    for (int numBytesToProcess = 1; numBytesToProcess <= fileSize; numBytesToProcess++)  
    {
      byteToWrite = 0; //reset to 0 to clear previous data

      // Loop through the 8 bytes and shift least sig.fig into byteToWrite
	    for (int bitCount = 7; bitCount >= 0; bitCount--)
      {
          //if least sig.fig is 1, shift 1, else 0 into quarterInt by bit# positions 
          byteToWrite |= ((carrierFile.get() & SET_MASK) == SET_MASK ? 1 : 0) << bitCount;
	    }
      //write decoded byte to out-file
      fileToWrite.put(byteToWrite);
    }
	
    //close files
    carrierFile.close();   
    fileToWrite.close();
	
  }




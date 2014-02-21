/*****************************************************
*	Caleb Meador
*	COSC1437 GE#6 , Fall, 2013
*	Filename:StegoBitmap.h
*	12/05/2013
*
********************************************************/
#ifndef STEGO_BITMAP_H
#define STEGO_BITMAP__H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <string>
#include "Bitmap.h"



class StegoBitmap : public Bitmap
{
protected:
    static const bool DEBUG_STEGO = 0;

    //static const int BMP_PIXEL_BYTES = 1000000; // standard 10 by 10 cell BMP
    //static const int HIDDEN_FILE_SIZE = 61163;  // actual size of a test file to hide
    //static const int BMP_PIXEL_BYTES_TO_MODIFY = HIDDEN_FILE_SIZE * 8;
    static const int HEADER_OFFSET = 122;
    static const int BYTES_TO_STORE_FILE_SIZE = 32;
    static const int BYTES_TO_STORE_FILE_EXTENSION = 64;

    static const unsigned int INT_TEST_MASK = 0x80000000; // test most significant bit of int
    static const char BYTE_TEST_MASK = 0x80;              // test left-most bit of char
    static const char CLEAR_MASK = 0xFE;
    static const char SET_MASK = 0x01;


public:

    class hideFileTooBig              {};
    class hiddenFileSizeInconsistancy {};
    class negativeHiddenFileSize      {};

    //createDefaultStegoBitmapObject
    StegoBitmap() : Bitmap()
    {
        printf("\n\n\t\tCreating StegoBitmap: \n\n");
    }

    //createStegoBitmapObjectFromBMPFile
    //TO DO pass parameter to the base class constructor.
    StegoBitmap(string name) : Bitmap(name)
    {
        printf("\n\n\t\tCreating StegoBitmap from %s: \n\n", name.c_str());
    }

    void hideFileInBMPFile(string fileWithHiddenData, string fileToHide);

    //retrieveFileFromBMPFile fileWithHiddenData.BMP fileToReveal.xyz
    //TO DO exception handling
    void retrieveFileFromBMPFile(string fileWithHiddenData, string fileToFind);

};

#endif
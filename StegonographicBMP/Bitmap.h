/*****************************************************
*	Caleb Meador
*	COSC1437 GE#6 , Fall, 2013
*	Filename:Bitmap.h
*	12/05/2013
*
********************************************************/
#ifndef BITMAP_H
#define BITMAP_H

#include "BitmapHeader.h"
#include "DIBHeader.h"
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Bitmap
{

  

protected:

  
  
  // embedded objects
	BitmapHeader bmpHeader;	//required for BMP
	DIBHeader dibHeader; 	//required for BMP

  

 
  public:
   //constants
  static const unsigned int BIT_SHIFT_8  = 8;
  static const unsigned int BIT_SHIFT_16 = 16;
  static const unsigned int BIT_SHIFT_24 = 24;
  static const unsigned int REPS         = 50; //repetitions in duplicate count.
  static const unsigned int INT_SIZE     = 4;
    
  struct Color {
	int red;
	int green; 
	int blue;
	int alpha;
	unsigned int pixelColor;
	bool newDefault;	//user specified new default color

  };	



    
    //debug
  bool DEBUG_BMP;
  Color	  color, 		//user-specified
			    defaultColor; //default color
	unsigned int totalRowCount; 
  unsigned int totalColCount;

  vector <unsigned int> grid;
  
  //constructors
	Bitmap ();   //no arg constructor
  Bitmap(string name); //1 arg constructor to read from existing BMP
  
  //inline functions
  
  //setters
  void calcTotalRowCount() 
  { totalRowCount = dibHeader.heightBitmapInPixels/REPS; }
  
  void calcTotalColCount()
  { totalColCount = dibHeader.widthBitmapInPixels/REPS;  }

  
  
  //getters
  unsigned int getTotalRowCount()
  { return totalRowCount;  }
  
  unsigned int getTotalColCount()
  { return totalColCount; }
	
  
  // Instance member functions - definted in Bitmap.cpp
	void setBmpDefault();
  void setDibDefault();
  void setDefaultColors(Color* c);
  void setDefaultColors();
  void convertColorToPixel();
  void displayHeaders();
  void displayVectorGrid();
  void displayColorInfo(); 
  void insertRow(int rowToInsert);
	void deleteRow(int rowToDelete);
	void insertCol(int colToInsert);
	void deleteCol(int colToDelete);
	void modRowCol(int rowToEdit, int colToEdit);
	void writeToFile(string outFileName, vector<unsigned int> grid);



};

#endif
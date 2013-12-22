/*****************************************************
*	Caleb Meador
*	COSC1437 GE#6 , Fall, 2013
*	Filename:BitmapHeader.h
*	12/05/2013
*
********************************************************/
#ifndef BMPHEADER_H
#define BMPHEADER_H

class BitmapHeader
{

  public:
  
  char fileSignature[2];
  unsigned int bmpFileSize;	  // change to 1,000,122
  unsigned short int unused_1;
  unsigned short int unused_2;
  unsigned int pixelOffset;
  
  //no arg constructor
  //BitmapHeader();
  
  
	//setters
	void setfileSignature_0(char s)
	{ fileSignature[0] = s; }
	
	void setfileSignature_1(char s)
	{ fileSignature[1] = s; }
	
	void setbmpFileSize(int s)
	{ bmpFileSize = s; }
	
	void setunused_1(int s)
	{ unused_1 = s; }
	
	void setunused_2(int s)
	{ unused_2 = s; }
	
	void setpixelOffset(int s)
	{ pixelOffset = s;  }

	//resetters
	void resetFileSig_0() 
	{ fileSignature[0] = 'B'; }
	
	void resetFileSig_1() 
	{ fileSignature[1] = 'M'; }
	
	void resetFileSize() 
	{ bmpFileSize = 1000122; }
	
	void resetUnused_1() 
	{ unused_1 = 0; }
	
	void resetUnused_2() 
	{ unused_2 = 0; }
	
	void resetpixelOffset() 
	{ pixelOffset = 122; }
	
	
	
	
	 
	
	//getters 
	char getFileSig_0()
	{ return fileSignature[0];	}

	char getFileSig_1()
	{ return fileSignature[1];	}

	unsigned int getFileSize()
	{	return bmpFileSize;	  }

	unsigned short int getUnused_1()
	{ return unused_1;		}

	unsigned short int getUnused_2()
	{	return unused_2;		}

	unsigned int getPixelOffset()
	{	return pixelOffset;}

};



#endif
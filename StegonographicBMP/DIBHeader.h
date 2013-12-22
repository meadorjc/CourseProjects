/*****************************************************
*	Caleb Meador
*	COSC1437 GE#6 , Fall, 2013
*	Filename:DIBHeader.h
*	12/05/2013
*
********************************************************/
#ifndef DIBHEADER_H
#define DIBHEADER_H

class DIBHeader
{
  public:
  
  unsigned int numBytesDIBHeader;
  unsigned int widthBitmapInPixels;      // change to 500
  unsigned int heightBitmapInPixels;     // change to 500
  unsigned short numColorPlanes;
  unsigned short numBitsPerPixel;
  unsigned int typeCompression;
  unsigned int sizeRawDataInPixelArray;  // change to 1,000,000
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
	
	//No arg constructor
	//DIBHeader::DIBHeader();
  
	void setNumBytesDIBHeader(unsigned int s)
	{ numBytesDIBHeader		  = s; }
	
	void setWidthBitmapInPixels(unsigned int s)
	{ widthBitmapInPixels		= s;       }
	
	void setHeightBitmapInPixels(unsigned int s)
	{ heightBitmapInPixels		= s;      }
	
	void setNumColorPlanes(unsigned short s)
	{ numColorPlanes			    =s; }
	
	void setNumBitsPerPixel(unsigned short s)
	{ numBitsPerPixel			  =s; }
	
	void setTypeCompression(unsigned int s)
	{ typeCompression			  =s; }
	
	void setSizeRawDataInPixelArray(unsigned int s)
	{ sizeRawDataInPixelArray  = s;   }
	
	void setHorizPhysicalResolution(unsigned int s)
	{ horizPhysicalResolution	= s; }
	
	void setVertPhysicalResolution(unsigned int s)
	{ vertPhysicalResolution	  = s; }
	
	void setNumColorsInPalette(unsigned int s)
	{ numColorsInPalette		 = s; }
	
	void setImportantColors(unsigned int s)
	{ importantColors			=  s; }
	
	void setRedChannelBitMask(unsigned int s)
	{ redChannelBitMask		  = s; }
	
	void setGreenChannelBitMask(unsigned int s)
	{ greenChannelBitMask		= s; }
	
	void setBlueChannelBitMask(unsigned int s)
	{ blueChannelBitMask		  = s; }
	
	void setAlphaChannelBitMask(unsigned int s)
	{ alphaChannelBitMask		= s; }
	
	void setTypeOfColorSpace(unsigned int s)
	{ typeOfColorSpace			  = s; }
	
	//pass a pointer set array
	/*void setColorSpaceEndPoints(unsigned int s[])
	{   colorSpaceEndPoints	= s; }
	*/
	void setRedGamma(unsigned int s)
	{ redGamma					=s; }
	
	void setGreenGamma(unsigned int s)
	{ greenGamma				=s; }
	
	void setBlueGamma(unsigned int s)
	{ blueGamma				=s; }

  
  
  //getters
	
	
	
  	unsigned int getNumBytesDIBHeader()
	{ return numBytesDIBHeader		  ; }
	
	unsigned int getWidthBitmapInPixels()
	{ return widthBitmapInPixels		;       }
	
	unsigned int getHeightBitmapInPixels()
	{ return heightBitmapInPixels		;      }
	
	unsigned short getNumColorPlanes()
	{ return numColorPlanes			    ; }
	
	unsigned short getNumBitsPerPixel()
	{ return numBitsPerPixel			  ; }
	
	unsigned int getTypeCompression()
	{ return typeCompression			  ; }
	
	unsigned int getSizeRawDataInPixelArray()
	{ return sizeRawDataInPixelArray  ;   }
	
	unsigned int getHorizPhysicalResolution()
	{ return horizPhysicalResolution	; }
	
	unsigned int getVertPhysicalResolution()
	{ return vertPhysicalResolution	  ; }
	
	unsigned int getNumColorsInPalette()
	{ return numColorsInPalette		 ; }
	
	unsigned int getImportantColors()
	{ return importantColors			 ; }
	
	unsigned int getRedChannelBitMask()
	{ return redChannelBitMask		  ; }
	
	unsigned int getGreenChannelBitMask()
	{ return greenChannelBitMask		; }
	
	unsigned int getBlueChannelBitMask()
	{ return blueChannelBitMask		  ; }
	
	unsigned int getAlphaChannelBitMask()
	{ return alphaChannelBitMask		; }
	
	unsigned int getTypeOfColorSpace()
	{ return typeOfColorSpace			  ; }
	
	//return a pointer to array
	unsigned int* getColorSpaceEndPoints()
	{ return colorSpaceEndPoints	; }
		
	unsigned int getRedGamma()
	{ return redGamma					; }
	
	unsigned int getGreenGamma()
	{ return greenGamma				; }
	
	unsigned int getBlueGamma()
	{ return blueGamma				; }
  
  
  
  
  
  };





#endif
@ECHO OFF
REM NOTE: Must run from within VisualStudio's command-line
cl /Zp2 StegoBMP.cpp StegoBitmap.cpp Bitmap.cpp BitmapHeader.cpp DIBHeader.cpp
PAUSE

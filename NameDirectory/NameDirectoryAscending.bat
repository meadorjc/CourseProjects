@ECHO OFF
ECHO Unsorted Data:
ECHO.
type InputExample.txt
ECHO.
ECHO Now running command-line arguments:
ECHO "NameDirectory asc < InputExample.txt"
ECHO.
NameDirectory asc < InputExample.txt 
ECHO.
ECHO.
ECHO Creating new file OutputExample.txt
NameDirectory asc < InputExample.txt > OutputExample.txt
ECHO.
PAUSE
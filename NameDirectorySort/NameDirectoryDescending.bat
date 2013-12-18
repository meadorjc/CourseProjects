@ECHO OFF
ECHO Unsorted Data:
ECHO.
type InputExample.txt
ECHO.
ECHO Now running command-line arguments:
ECHO "NameDirectory des < InputExample.txt"
ECHO.
NameDirectory des < InputExample.txt 
ECHO.
ECHO.
ECHO Creating new file OutputExample.txt
NameDirectory des < InputExample.txt > OutputExample.txt
ECHO.
PAUSE
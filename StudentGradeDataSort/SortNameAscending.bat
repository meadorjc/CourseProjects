@ECHO OFF
ECHO Unsorted Data:
ECHO.
type InputExample.txt
ECHO.
ECHO.
ECHO Now running command-line arguments:
ECHO.
ECHO.
ECHO "StudentGradeDataSort name asc < InputExample.txt"
ECHO.
StudentGradeDataSort name asc < InputExample.txt 
ECHO.
ECHO.
ECHO Creating new file OutputExample.txt
StudentGradeDataSort name asc < InputExample.txt > SortNameAscendingOutput.txt
ECHO.
PAUSE
@ECHO OFF
ECHO Unsorted Data:
ECHO.
type InputExample.txt
ECHO.
ECHO.
ECHO Now running command-line arguments:
ECHO.
ECHO.
ECHO "StudentGradeDataSort score asc < InputExample.txt"
ECHO.
StudentGradeDataSort score asc < InputExample.txt 
ECHO.
ECHO.
ECHO Creating new file SortNameDescendingOutput.txt
StudentGradeDataSort score asc < InputExample.txt > SortScoreAscendingOutput.txt
ECHO.
PAUSE
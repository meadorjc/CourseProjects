@ECHO OFF
ECHO Unsorted Data:
ECHO.
type InputExample.txt
ECHO.
ECHO.
ECHO Now running command-line arguments:
ECHO.
ECHO.
ECHO "StudentGradeDataSort score des < InputExample.txt"
ECHO.
StudentGradeDataSort score des < InputExample.txt 
ECHO.
ECHO.
ECHO Creating new file SortNameDescendingOutput.txt
StudentGradeDataSort score des < InputExample.txt > SortScoreDescendingOutput.txt
ECHO.
PAUSE
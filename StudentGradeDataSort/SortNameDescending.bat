@ECHO OFF
ECHO Unsorted Data:
ECHO.
type InputExample.txt
ECHO.
ECHO.
ECHO Now running command-line arguments:
ECHO.
ECHO.
ECHO "StudentGradeDataSort name des < InputExample.txt"
ECHO.
StudentGradeDataSort name des < InputExample.txt 
ECHO.
ECHO.
ECHO Creating new file SortNameDescendingOutput.txt
StudentGradeDataSort name des < InputExample.txt > SortNameDescendingOutput.txt
ECHO.
PAUSE
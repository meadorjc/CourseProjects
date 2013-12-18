::Caleb Meador 12/17/2013 meadorjc at gmail dot com
::Hexcode modified from http://www.dostips.com/forum/viewtopic.php?f=3&t=3857
@echo off
setlocal EnableDelayedExpansion
::Define a Linefeed variable
set LF=^


::above 2 blank lines are critical - do not remove.
ECHO Encrypted File:
ECHO ******************************************************
type EncryptedFile.txt
ECHO.
ECHO ******************************************************
ECHO.
ECHO Cipher key:
type password.txt
ECHO.
ECHO.
ECHO Now running command-line arguments:
ECHO VigenereEncryption -d -c EncryptedFile.txt -p DecryptedFile.txt -k password.txt
ECHO. 
ECHO.
::Create a dash variable to avoid problems printing 0x96 char
call :hexprint "0x2D" TAB
VigenereEncryption %TAB%d %TAB%c EncryptedFile.txt %TAB%p DecryptedFile.txt %TAB%k password.txt
ECHO.
ECHO.
ECHO Creating new file DecryptedFile.txt
ECHO.
ECHO.
ECHO Decrypted file
ECHO ******************************************************
type DecryptedFile.txt
ECHO.
ECHO ******************************************************
ECHO.
ECHO End of program.
ECHO.
PAUSE
exit /b

:hexPrint  string  [rtnVar]
  for /f eol^=^%LF%%LF%^ delims^= %%A in (
    'forfiles /p "%~dp0." /m "%~nx0" /c "cmd /c echo(%~1"'
  ) do if "%~2" neq "" (set %~2=%%A) else echo(%%A
exit /b
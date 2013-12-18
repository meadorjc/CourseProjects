::Caleb Meador 12/17/2013 meadorjc at gmail dot com
::Hexcode modified from http://www.dostips.com/forum/viewtopic.php?f=3&t=3857
@echo off
setlocal EnableDelayedExpansion
::chcp 1252
::Define a Linefeed variable
set LF=^


::above 2 blank lines are critical - do not remove.
ECHO Unencrypted File:
ECHO ******************************************************
type plaintext.txt
ECHO.
ECHO ******************************************************
ECHO.
ECHO Cipher key:
type password.txt
ECHO.
ECHO.
call :hexprint "0x2D" TAB

ECHO Now running command-line arguments:
::Create a DASH variable that points to function
REM ECHO VigenereEncryption %DASH%e %DASH%p  PlainText.txt %DASH%c EncryptedFile.txt %DASH%k password.txt
ECHO VigenereEncryption -e -p  PlainText.txt -c EncryptedFile.txt -k password.txt
ECHO. 
ECHO.
VigenereEncryption  %TAB%e  %TAB%p PlainText.txt %TAB%c EncryptedFile.txt %TAB%k password.txt
ECHO.
ECHO.
ECHO Creating new file EncryptedFile.txt
ECHO.
ECHO.
ECHO Encrypted file
ECHO ******************************************************
type EncryptedFile.txt
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
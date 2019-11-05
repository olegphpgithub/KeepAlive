@echo off

DEL "%~dp0..\res\bigmodule.wav" /Q /F
"c:\Program Files (x86)\NSIS246\makensis.exe" "%~dp0..\..\Release\Inetc.nsi"
IF NOT '%ERRORLEVEL%'=='0' GOTO failure

EXIT /B 0

:failure
EXIT /B 1
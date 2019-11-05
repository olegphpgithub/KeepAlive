@echo off

DEL "%~dp0..\..\Release\debug.txt" /Q /F

EXIT /B 0

:failure
EXIT /B 1
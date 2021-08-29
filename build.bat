@echo off
goto main
:buildmsvc
echo Please edit line 8 and line 9.
notepad cfdesk.cpp
cl /EHsc /std:c++17 /O2 /F268435456 predictor.cpp
cl /EHsc /std:c++17 /O2 /F268435456 cfdesk.cpp
del predictor.obj
del cfdesk.obj
goto exit
:buildgcc
echo Please edit line 8 and line 9.
notepad cfdesk.cpp
g++ -std=c++14 predictor.cpp -o predictor
g++ -std=c++14 cfdesk.cpp -o cfdesk
goto exit
:main
goto buildmsvc
::goto buildgcc if you use G++ compiler
:exit
pause
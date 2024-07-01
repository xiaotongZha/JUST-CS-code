@echo off
setlocal

:loop

echo Please choice lab range 1-8 or 'q' to quit:
set /p num=

if "%num%"=="1" goto l1
if "%num%"=="2" goto l2
if "%num%"=="3" goto l3
if "%num%"=="4" goto l4
if "%num%"=="5" goto l5
if "%num%"=="6" goto l6
if "%num%"=="7" goto l7
if "%num%"=="8" goto l8
if /i "%num%"=="q" goto end

echo Invalid input.
goto loop

:l1
cd ./l1
run main.cc
cd ../
goto loop

:l2
cd ./l2
run main.cc
cd ../
goto loop

:l3
cd ./l3
run main.cc
cd ../
goto loop

:l4
cd ./l4
run main.cc
cd ../
goto loop

:l5
cd ./l5
python main.py
cd ../
goto loop

:l6
cd ./l6
run main.cc
cd ../
goto loop

:l7
cd ./l7
run main.cc
cd ../
goto loop

:l8
cd ./l8
python main.py
cd ../
goto loop

:end
echo Exiting...
pause
endlocal


@echo off
cd ..\Processor
call build

cd ..\Emulator
python bintoc.py
mingw32-make

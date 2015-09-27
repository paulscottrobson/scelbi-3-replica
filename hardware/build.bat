@echo off

cd ..\emulator
call build.bat
cd ..\hardware
copy /Y ..\emulator\drivers.* src
copy /Y ..\emulator\sys_processor*.* src
copy /Y ..\emulator\sys_debug_system.h src
copy /Y ..\emulator\__*.* src

platformio run
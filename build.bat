qmake gSimModel.pro 
mingw32-make.exe

copy ".\release\gSimModel.dll" "..\gSimExe"
del ".\release\gSimModel.dll"

remove_unused.bat
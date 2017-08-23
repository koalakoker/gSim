qmake gSimModel.pro 
mingw32-make.exe

copy ".\release\gSimModel.dll" "..\gSimExe"
del ".\release\gSimModel.dll"

del /Q "debug"
rmdir "debug"
del /Q "release"
rmdir "release"
del ".qmake.stash"
del "Makefile"
del "Makefile.Debug"
del "Makefile.Release"
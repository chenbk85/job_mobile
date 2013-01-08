mc -U sample.mc 
pause
rc -r sample.rc 
pause
link -dll -noentry -out:sample.dll sample.res 
pause

Build Svc.exe Svc.cpp
Build 

SvcConfig.cpp, and SvcControl.cpp
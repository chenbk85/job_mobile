mc -U %1.mc
rc -r %1.rc
echo %1
link -dll -noentry -out:%2\%1.dll %1.res
rem copy %1.dll %2
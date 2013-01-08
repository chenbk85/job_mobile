mc -U jServerTestEvent.mc
rc -r jServerTestEvent.rc
echo %1
link -dll -noentry -out:jServerTestEvent.dll jServerTestEvent.res
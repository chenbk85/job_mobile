cd ..\bin


set DEST=..\..\..\..\..\lib\lib_mech\bin\client\URelease_Win32
copy %DEST%\Com_Util.dll				.\URelease
copy %DEST%\PacketGenerator.exe				.\URelease
copy %DEST%\jBase.dll					.\URelease
copy %DEST%\jCommon.dll					.\URelease
copy %DEST%\jGlobal.ini					.\URelease
copy %DEST%\jLog.dll					.\URelease
copy %DEST%\jUtil.dll					.\URelease
copy %DEST%\jXml.dll					.\URelease


set DEST=..\..\..\..\..\lib\lib_mech\bin\client\UDebug_Win32
copy %DEST%\Com_Util.dll				.\UDebug
copy %DEST%\PacketGenerator.exe				.\UDebug
copy %DEST%\jBase.dll 					.\UDebug
copy %DEST%\jCommon.dll					.\UDebug
copy %DEST%\jGlobal.ini					.\UDebug
copy %DEST%\jLog.dll					.\UDebug
copy %DEST%\jUtil.dll					.\UDebug
copy %DEST%\jXml.dll					.\UDebug

pause
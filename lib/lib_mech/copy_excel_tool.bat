set target_bin=%cd%\..\..\..\..\dualgo\Tool\excel\bin\UDebug
set src_bin=%cd%\bin\client\UDebug_Win32
copy /y %src_bin%\Com_Util.dll %target_bin%
copy /y %src_bin%\Excel_Converter.exe %target_bin%
copy /y %src_bin%\jBase.dll %target_bin%
copy /y %src_bin%\jCommon.dll %target_bin%
copy /y %src_bin%\jLog.dll %target_bin%
copy /y %src_bin%\jSquirrel.dll %target_bin%
copy /y %src_bin%\jUtil.dll %target_bin%
copy /y %src_bin%\jXml.dll %target_bin%


set target_bin=%cd%\..\..\..\..\dualgo\Tool\excel\bin\URelease
set src_bin=%cd%\bin\client\URelease_Win32

copy /y %src_bin%\Com_Util.dll %target_bin%
copy /y %src_bin%\Excel_Converter.exe %target_bin%
copy /y %src_bin%\jBase.dll %target_bin%
copy /y %src_bin%\jCommon.dll %target_bin%
copy /y %src_bin%\jLog.dll %target_bin%
copy /y %src_bin%\jSquirrel.dll %target_bin%
copy /y %src_bin%\jUtil.dll %target_bin%
copy /y %src_bin%\jXml.dll %target_bin%

pause
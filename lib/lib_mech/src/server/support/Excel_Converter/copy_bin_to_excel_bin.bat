cd Z:\job_sam\bin\client\urelease_vc80

copy /y Excel_Converter.exe Z:\job_sam\bin\server\xls\bin\URelease
copy /y jBase.dll Z:\job_sam\bin\server\xls\bin\URelease
copy /y jUtil.dll Z:\job_sam\bin\server\xls\bin\URelease
copy /y jCommon.dll Z:\job_sam\bin\server\xls\bin\URelease
copy /y com_util.dll Z:\job_sam\bin\server\xls\bin\URelease
copy /y jXml.dll Z:\job_sam\bin\server\xls\bin\URelease

mkdir udebug
CD Z:\job_sam\bin\client\udebug_vc80
copy /y Excel_Converter.exe Z:\job_sam\bin\server\xls\bin\Udebug
copy /y jBase.dll Z:\job_sam\bin\server\xls\bin\Udebug
copy /y jUtil.dll Z:\job_sam\bin\server\xls\bin\Udebug
copy /y jCommon.dll Z:\job_sam\bin\server\xls\bin\Udebug
copy /y com_util.dll Z:\job_sam\bin\server\xls\bin\Udebug
copy /y jXml.dll Z:\job_sam\bin\server\xls\bin\Udebug

pause
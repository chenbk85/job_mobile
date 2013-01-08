# Microsoft Developer Studio Generated NMAKE File


ALL : \
	"..\..\bin\Translations\ToolkitPro.ResourceArSa.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceBg.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceCs.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceDa.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceDe.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceEl.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceEn.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceEs.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceEt.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceFi.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceFr.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceHe.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceHr.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceHu.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceIt.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceJa.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceKo.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceLt.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceLv.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceNl.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceNo.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourcePl.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourcePt.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourcePtBr.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceRo.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceRu.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceSk.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceSl.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceSv.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceTh.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceTr.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceUk.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceZhCn.dll" \
	"..\..\bin\Translations\ToolkitPro.ResourceZhTw.dll"           




RSC=rc.exe
RSC_PROJ=/l 0x409 /i "../../Source" /i "../../Source/Common" /d "NDEBUG" 
LINK32=link.exe
LINK32_FLAGS=/nologo /dll /incremental:no /machine:I386 /nodefaultlib /opt:nowin98 /noentry 

"..\..\bin\Translations" :
    if not exist "	..\..\bin\Translations/$(NULL)" mkdir "..\..\bin\Translations"


# ResourceArSa

"ResourceArSa\Release" :
    if not exist "ResourceArSa/Release/$(NULL)" mkdir "ResourceArSa/Release"

"..\..\bin\Translations\ToolkitPro.ResourceArSa.dll" : "ResourceArSa\Release" "ResourceArSa\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceArSa.dll" "ResourceArSa\Release\Resource.res"

"ResourceArSa\Release\Resource.res" : ".\ResourceArSa\Resource.rc" "ResourceArSa\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceArSa\Release\Resource.res" .\ResourceArSa\Resource.rc


# ResourceBg

"ResourceBg\Release" :
    if not exist "ResourceBg/Release/$(NULL)" mkdir "ResourceBg/Release"

"..\..\bin\Translations\ToolkitPro.ResourceBg.dll" : "ResourceBg\Release" "ResourceBg\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceBg.dll" "ResourceBg\Release\Resource.res"

"ResourceBg\Release\Resource.res" : ".\ResourceBg\Resource.rc" "ResourceBg\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceBg\Release\Resource.res" .\ResourceBg\Resource.rc


# ResourceCs

"ResourceCs\Release" :
    if not exist "ResourceCs/Release/$(NULL)" mkdir "ResourceCs/Release"

"..\..\bin\Translations\ToolkitPro.ResourceCs.dll" : "ResourceCs\Release" "ResourceCs\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceCs.dll" "ResourceCs\Release\Resource.res"

"ResourceCs\Release\Resource.res" : ".\ResourceCs\Resource.rc" "ResourceCs\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceCs\Release\Resource.res" .\ResourceCs\Resource.rc


# ResourceDa

"ResourceDa\Release" :
    if not exist "ResourceDa/Release/$(NULL)" mkdir "ResourceDa/Release"

"..\..\bin\Translations\ToolkitPro.ResourceDa.dll" : "ResourceDa\Release" "ResourceDa\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceDa.dll" "ResourceDa\Release\Resource.res"

"ResourceDa\Release\Resource.res" : ".\ResourceDa\Resource.rc" "ResourceDa\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceDa\Release\Resource.res" .\ResourceDa\Resource.rc


# ResourceDe

"ResourceDe\Release" :
    if not exist "ResourceDe/Release/$(NULL)" mkdir "ResourceDe/Release"

"..\..\bin\Translations\ToolkitPro.ResourceDe.dll" : "ResourceDe\Release" "ResourceDe\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceDe.dll" "ResourceDe\Release\Resource.res"

"ResourceDe\Release\Resource.res" : ".\ResourceDe\Resource.rc" "ResourceDe\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceDe\Release\Resource.res" .\ResourceDe\Resource.rc


# ResourceEl

"ResourceEl\Release" :
    if not exist "ResourceEl/Release/$(NULL)" mkdir "ResourceEl/Release"

"..\..\bin\Translations\ToolkitPro.ResourceEl.dll" : "ResourceEl\Release" "ResourceEl\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceEl.dll" "ResourceEl\Release\Resource.res"

"ResourceEl\Release\Resource.res" : ".\ResourceEl\Resource.rc" "ResourceEl\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceEl\Release\Resource.res" .\ResourceEl\Resource.rc


# ResourceEn

"ResourceEn\Release" :
    if not exist "ResourceEn/Release/$(NULL)" mkdir "ResourceEn/Release"

"..\..\bin\Translations\ToolkitPro.ResourceEn.dll" : "ResourceEn\Release" "ResourceEn\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceEn.dll" "ResourceEn\Release\Resource.res"

"ResourceEn\Release\Resource.res" : ".\ResourceEn\Resource.rc" "ResourceEn\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceEn\Release\Resource.res" .\ResourceEn\Resource.rc


# ResourceEs

"ResourceEs\Release" :
    if not exist "ResourceEs/Release/$(NULL)" mkdir "ResourceEs/Release"

"..\..\bin\Translations\ToolkitPro.ResourceEs.dll" : "ResourceEs\Release" "ResourceEs\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceEs.dll" "ResourceEs\Release\Resource.res"

"ResourceEs\Release\Resource.res" : ".\ResourceEs\Resource.rc" "ResourceEs\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceEs\Release\Resource.res" .\ResourceEs\Resource.rc


# ResourceEt

"ResourceEt\Release" :
    if not exist "ResourceEt/Release/$(NULL)" mkdir "ResourceEt/Release"

"..\..\bin\Translations\ToolkitPro.ResourceEt.dll" : "ResourceEt\Release" "ResourceEt\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceEt.dll" "ResourceEt\Release\Resource.res"

"ResourceEt\Release\Resource.res" : ".\ResourceEt\Resource.rc" "ResourceEt\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceEt\Release\Resource.res" .\ResourceEt\Resource.rc


# ResourceFi

"ResourceFi\Release" :
    if not exist "ResourceFi/Release/$(NULL)" mkdir "ResourceFi/Release"

"..\..\bin\Translations\ToolkitPro.ResourceFi.dll" : "ResourceFi\Release" "ResourceFi\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceFi.dll" "ResourceFi\Release\Resource.res"

"ResourceFi\Release\Resource.res" : ".\ResourceFi\Resource.rc" "ResourceFi\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceFi\Release\Resource.res" .\ResourceFi\Resource.rc


# ResourceFr

"ResourceFr\Release" :
    if not exist "ResourceFr/Release/$(NULL)" mkdir "ResourceFr/Release"

"..\..\bin\Translations\ToolkitPro.ResourceFr.dll" : "ResourceFr\Release" "ResourceFr\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceFr.dll" "ResourceFr\Release\Resource.res"

"ResourceFr\Release\Resource.res" : ".\ResourceFr\Resource.rc" "ResourceFr\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceFr\Release\Resource.res" .\ResourceFr\Resource.rc


# ResourceHe

"ResourceHe\Release" :
    if not exist "ResourceHe/Release/$(NULL)" mkdir "ResourceHe/Release"

"..\..\bin\Translations\ToolkitPro.ResourceHe.dll" : "ResourceHe\Release" "ResourceHe\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceHe.dll" "ResourceHe\Release\Resource.res"

"ResourceHe\Release\Resource.res" : ".\ResourceHe\Resource.rc" "ResourceHe\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceHe\Release\Resource.res" .\ResourceHe\Resource.rc


# ResourceHr

"ResourceHr\Release" :
    if not exist "ResourceHr/Release/$(NULL)" mkdir "ResourceHr/Release"

"..\..\bin\Translations\ToolkitPro.ResourceHr.dll" : "ResourceHr\Release" "ResourceHr\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceHr.dll" "ResourceHr\Release\Resource.res"

"ResourceHr\Release\Resource.res" : ".\ResourceHr\Resource.rc" "ResourceHr\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceHr\Release\Resource.res" .\ResourceHr\Resource.rc


# ResourceHu

"ResourceHu\Release" :
    if not exist "ResourceHu/Release/$(NULL)" mkdir "ResourceHu/Release"

"..\..\bin\Translations\ToolkitPro.ResourceHu.dll" : "ResourceHu\Release" "ResourceHu\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceHu.dll" "ResourceHu\Release\Resource.res"

"ResourceHu\Release\Resource.res" : ".\ResourceHu\Resource.rc" "ResourceHu\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceHu\Release\Resource.res" .\ResourceHu\Resource.rc


# ResourceIt

"ResourceIt\Release" :
    if not exist "ResourceIt/Release/$(NULL)" mkdir "ResourceIt/Release"

"..\..\bin\Translations\ToolkitPro.ResourceIt.dll" : "ResourceIt\Release" "ResourceIt\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceIt.dll" "ResourceIt\Release\Resource.res"

"ResourceIt\Release\Resource.res" : ".\ResourceIt\Resource.rc" "ResourceIt\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceIt\Release\Resource.res" .\ResourceIt\Resource.rc


# ResourceJa

"ResourceJa\Release" :
    if not exist "ResourceJa/Release/$(NULL)" mkdir "ResourceJa/Release"

"..\..\bin\Translations\ToolkitPro.ResourceJa.dll" : "ResourceJa\Release" "ResourceJa\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceJa.dll" "ResourceJa\Release\Resource.res"

"ResourceJa\Release\Resource.res" : ".\ResourceJa\Resource.rc" "ResourceJa\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceJa\Release\Resource.res" .\ResourceJa\Resource.rc


# ResourceKo

"ResourceKo\Release" :
    if not exist "ResourceKo/Release/$(NULL)" mkdir "ResourceKo/Release"

"..\..\bin\Translations\ToolkitPro.ResourceKo.dll" : "ResourceKo\Release" "ResourceKo\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceKo.dll" "ResourceKo\Release\Resource.res"

"ResourceKo\Release\Resource.res" : ".\ResourceKo\Resource.rc" "ResourceKo\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceKo\Release\Resource.res" .\ResourceKo\Resource.rc


# ResourceLt

"ResourceLt\Release" :
    if not exist "ResourceLt/Release/$(NULL)" mkdir "ResourceLt/Release"

"..\..\bin\Translations\ToolkitPro.ResourceLt.dll" : "ResourceLt\Release" "ResourceLt\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceLt.dll" "ResourceLt\Release\Resource.res"

"ResourceLt\Release\Resource.res" : ".\ResourceLt\Resource.rc" "ResourceLt\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceLt\Release\Resource.res" .\ResourceLt\Resource.rc


# ResourceLv

"ResourceLv\Release" :
    if not exist "ResourceLv/Release/$(NULL)" mkdir "ResourceLv/Release"

"..\..\bin\Translations\ToolkitPro.ResourceLv.dll" : "ResourceLv\Release" "ResourceLv\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceLv.dll" "ResourceLv\Release\Resource.res"

"ResourceLv\Release\Resource.res" : ".\ResourceLv\Resource.rc" "ResourceLv\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceLv\Release\Resource.res" .\ResourceLv\Resource.rc


# ResourceNl

"ResourceNl\Release" :
    if not exist "ResourceNl/Release/$(NULL)" mkdir "ResourceNl/Release"

"..\..\bin\Translations\ToolkitPro.ResourceNl.dll" : "ResourceNl\Release" "ResourceNl\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceNl.dll" "ResourceNl\Release\Resource.res"

"ResourceNl\Release\Resource.res" : ".\ResourceNl\Resource.rc" "ResourceNl\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceNl\Release\Resource.res" .\ResourceNl\Resource.rc


# ResourceNo

"ResourceNo\Release" :
    if not exist "ResourceNo/Release/$(NULL)" mkdir "ResourceNo/Release"

"..\..\bin\Translations\ToolkitPro.ResourceNo.dll" : "ResourceNo\Release" "ResourceNo\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceNo.dll" "ResourceNo\Release\Resource.res"

"ResourceNo\Release\Resource.res" : ".\ResourceNo\Resource.rc" "ResourceNo\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceNo\Release\Resource.res" .\ResourceNo\Resource.rc


# ResourcePl

"ResourcePl\Release" :
    if not exist "ResourcePl/Release/$(NULL)" mkdir "ResourcePl/Release"

"..\..\bin\Translations\ToolkitPro.ResourcePl.dll" : "ResourcePl\Release" "ResourcePl\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourcePl.dll" "ResourcePl\Release\Resource.res"

"ResourcePl\Release\Resource.res" : ".\ResourcePl\Resource.rc" "ResourcePl\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourcePl\Release\Resource.res" .\ResourcePl\Resource.rc


# ResourcePt

"ResourcePt\Release" :
    if not exist "ResourcePt/Release/$(NULL)" mkdir "ResourcePt/Release"

"..\..\bin\Translations\ToolkitPro.ResourcePt.dll" : "ResourcePt\Release" "ResourcePt\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourcePt.dll" "ResourcePt\Release\Resource.res"

"ResourcePt\Release\Resource.res" : ".\ResourcePt\Resource.rc" "ResourcePt\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourcePt\Release\Resource.res" .\ResourcePt\Resource.rc


# ResourcePtBr

"ResourcePtBr\Release" :
    if not exist "ResourcePtBr/Release/$(NULL)" mkdir "ResourcePtBr/Release"

"..\..\bin\Translations\ToolkitPro.ResourcePtBr.dll" : "ResourcePtBr\Release" "ResourcePtBr\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourcePtBr.dll" "ResourcePtBr\Release\Resource.res"

"ResourcePtBr\Release\Resource.res" : ".\ResourcePtBr\Resource.rc" "ResourcePtBr\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourcePtBr\Release\Resource.res" .\ResourcePtBr\Resource.rc


# ResourceRo

"ResourceRo\Release" :
    if not exist "ResourceRo/Release/$(NULL)" mkdir "ResourceRo/Release"

"..\..\bin\Translations\ToolkitPro.ResourceRo.dll" : "ResourceRo\Release" "ResourceRo\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceRo.dll" "ResourceRo\Release\Resource.res"

"ResourceRo\Release\Resource.res" : ".\ResourceRo\Resource.rc" "ResourceRo\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceRo\Release\Resource.res" .\ResourceRo\Resource.rc


# ResourceRu

"ResourceRu\Release" :
    if not exist "ResourceRu/Release/$(NULL)" mkdir "ResourceRu/Release"

"..\..\bin\Translations\ToolkitPro.ResourceRu.dll" : "ResourceRu\Release" "ResourceRu\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceRu.dll" "ResourceRu\Release\Resource.res"

"ResourceRu\Release\Resource.res" : ".\ResourceRu\Resource.rc" "ResourceRu\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceRu\Release\Resource.res" .\ResourceRu\Resource.rc


# ResourceSk

"ResourceSk\Release" :
    if not exist "ResourceSk/Release/$(NULL)" mkdir "ResourceSk/Release"

"..\..\bin\Translations\ToolkitPro.ResourceSk.dll" : "ResourceSk\Release" "ResourceSk\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceSk.dll" "ResourceSk\Release\Resource.res"

"ResourceSk\Release\Resource.res" : ".\ResourceSk\Resource.rc" "ResourceSk\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceSk\Release\Resource.res" .\ResourceSk\Resource.rc


# ResourceSl

"ResourceSl\Release" :
    if not exist "ResourceSl/Release/$(NULL)" mkdir "ResourceSl/Release"

"..\..\bin\Translations\ToolkitPro.ResourceSl.dll" : "ResourceSl\Release" "ResourceSl\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceSl.dll" "ResourceSl\Release\Resource.res"

"ResourceSl\Release\Resource.res" : ".\ResourceSl\Resource.rc" "ResourceSl\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceSl\Release\Resource.res" .\ResourceSl\Resource.rc


# ResourceSv

"ResourceSv\Release" :
    if not exist "ResourceSv/Release/$(NULL)" mkdir "ResourceSv/Release"

"..\..\bin\Translations\ToolkitPro.ResourceSv.dll" : "ResourceSv\Release" "ResourceSv\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceSv.dll" "ResourceSv\Release\Resource.res"

"ResourceSv\Release\Resource.res" : ".\ResourceSv\Resource.rc" "ResourceSv\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceSv\Release\Resource.res" .\ResourceSv\Resource.rc


# ResourceTh

"ResourceTh\Release" :
    if not exist "ResourceTh/Release/$(NULL)" mkdir "ResourceTh/Release"

"..\..\bin\Translations\ToolkitPro.ResourceTh.dll" : "ResourceTh\Release" "ResourceTh\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceTh.dll" "ResourceTh\Release\Resource.res"

"ResourceTh\Release\Resource.res" : ".\ResourceTh\Resource.rc" "ResourceTh\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceTh\Release\Resource.res" .\ResourceTh\Resource.rc


# ResourceTr

"ResourceTr\Release" :
    if not exist "ResourceTr/Release/$(NULL)" mkdir "ResourceTr/Release"

"..\..\bin\Translations\ToolkitPro.ResourceTr.dll" : "ResourceTr\Release" "ResourceTr\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceTr.dll" "ResourceTr\Release\Resource.res"

"ResourceTr\Release\Resource.res" : ".\ResourceTr\Resource.rc" "ResourceTr\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceTr\Release\Resource.res" .\ResourceTr\Resource.rc


# ResourceUk

"ResourceUk\Release" :
    if not exist "ResourceUk/Release/$(NULL)" mkdir "ResourceUk/Release"

"..\..\bin\Translations\ToolkitPro.ResourceUk.dll" : "ResourceUk\Release" "ResourceUk\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceUk.dll" "ResourceUk\Release\Resource.res"

"ResourceUk\Release\Resource.res" : ".\ResourceUk\Resource.rc" "ResourceUk\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceUk\Release\Resource.res" .\ResourceUk\Resource.rc


# ResourceZhCn

"ResourceZhCn\Release" :
    if not exist "ResourceZhCn/Release/$(NULL)" mkdir "ResourceZhCn/Release"

"..\..\bin\Translations\ToolkitPro.ResourceZhCn.dll" : "ResourceZhCn\Release" "ResourceZhCn\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceZhCn.dll" "ResourceZhCn\Release\Resource.res"

"ResourceZhCn\Release\Resource.res" : ".\ResourceZhCn\Resource.rc" "ResourceZhCn\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceZhCn\Release\Resource.res" .\ResourceZhCn\Resource.rc


# ResourceZhTw

"ResourceZhTw\Release" :
    if not exist "ResourceZhTw/Release/$(NULL)" mkdir "ResourceZhTw/Release"

"..\..\bin\Translations\ToolkitPro.ResourceZhTw.dll" : "ResourceZhTw\Release" "ResourceZhTw\Release\Resource.res"
    $(LINK32) $(LINK32_FLAGS) /out:"../../bin/Translations/ToolkitPro.ResourceZhTw.dll" "ResourceZhTw\Release\Resource.res"

"ResourceZhTw\Release\Resource.res" : ".\ResourceZhTw\Resource.rc" "ResourceZhTw\Release" "..\..\bin\Translations"
	$(RSC) $(RSC_PROJ) /fo"ResourceZhTw\Release\Resource.res" .\ResourceZhTw\Resource.rc


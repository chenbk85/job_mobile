// test_code.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <msxml2.h>

#import <msxml4.dll> raw_interfaces_only
//using namespace MSXML2;

// Macro that calls a COM method returning HRESULT value:
#define HRCALL(a, errmsg) \
	do { \
	hr = (a); \
	if (FAILED(hr)) { \
	dprintf( "%s:%d  HRCALL Failed: %s\n  0x%.8x = %s\n", \
	__FILE__, __LINE__, errmsg, hr, #a ); \
	goto clean; \
	} \
	} while (0)

// Helper function that puts output in stdout and debug window
// in Visual Studio:
void dprintf( char * format, ...)
{
	static char buf[1024];
	va_list args;
	va_start( args, format );
	vsprintf( buf, format, args );
	va_end( args);
	OutputDebugStringA( buf);
	printf("%s", buf);
}



// Helper function to create a DOM instance: 
IXMLDOMDocument * DomFromCOM()
{
	HRESULT hr;
	IXMLDOMDocument *pxmldoc = NULL;

	HRCALL( CoCreateInstance(__uuidof(DOMDocument40),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IXMLDOMDocument),
		(void**)&pxmldoc),
		"Create a new DOMDocument");

	HRCALL( pxmldoc->put_async(VARIANT_FALSE),
		"should never fail");
	HRCALL( pxmldoc->put_validateOnParse(VARIANT_FALSE),
		"should never fail");
	HRCALL( pxmldoc->put_resolveExternals(VARIANT_FALSE),
		"should never fail");

	return pxmldoc;
clean:
	if (pxmldoc)
	{
		pxmldoc->Release();
	}
	return NULL;
}


void xml_save(WCHAR* szFile , WCHAR* szXML)
{
	IXMLDOMDocument *pXMLDom=NULL;
	IXMLDOMParseError *pXMLErr=NULL;
	BSTR bstr = NULL;
	VARIANT_BOOL status;
	VARIANT var;
	HRESULT hr;

	CoInitialize(NULL);

	pXMLDom = DomFromCOM();
	if (!pXMLDom) goto clean;

	bstr = SysAllocString(szXML);
	HRCALL(pXMLDom->loadXML(bstr, &status), 
		"dom->loadXML(): ");
	SysFreeString(bstr);

	if (status!=VARIANT_TRUE) {
		HRCALL(pXMLDom->get_parseError(&pXMLErr),
			"dom->get_parseError: ");
		HRCALL(pXMLErr->get_reason(&bstr),
			"parseError->get_reason: ");
		dprintf("Failed to load DOM from xml string. %S\n",
			bstr);
		goto clean;
	}
	HRCALL(pXMLDom->get_xml(&bstr), "dom->get_xml: ");
	dprintf("XML DOM loaded from stocks.xml:\n%S\n",bstr);

	VariantInit(&var);
	V_BSTR(&var) = SysAllocString(szFile);
	V_VT(&var) = VT_BSTR;
	HRCALL(pXMLDom->save(var), "dom->save: ");
	dprintf("XML DOM saved to myData.xml\n");

clean:
	if (bstr) SysFreeString(bstr);
	if (&var) VariantClear(&var);
	if (pXMLErr) pXMLErr->Release();
	if (pXMLDom) pXMLDom->Release();

	CoUninitialize();
}

int asdf_tmain(int argc, _TCHAR* argv[])
{
	WCHAR* szXML = L"<r>\n<t>top</t>\n<b>bottom</b>\n</r>";
	WCHAR* szFile = L"c:\\myData.xml";
	xml_save(szFile, szXML);
	return 0;
}



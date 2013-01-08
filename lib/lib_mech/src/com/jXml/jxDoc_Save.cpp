// test_code.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "header/jTCHAR_util.h"

#ifdef jMSXML_USE
		//#import <msxml4.dll> raw_interfaces_only
		#import <msxml6.dll> raw_interfaces_only
		//using namespace MSXML2;
		#include <msxml2.h>

		#include"header/jTCHAR_util.h"
		using namespace nMech;

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
			return;
			static char buf[1024];
			va_list args;
			va_start( args, format );
			vsprintf( buf, format, args );
			va_end( args);
			OutputDebugStringA( buf);
			jWARN_T("%s", jT(buf));
		}



		// Helper function to create a DOM instance: 
		IXMLDOMDocument * DomFromCOM()
		{
			HRESULT hr;
			IXMLDOMDocument *pxmldoc = NULL;

			HRCALL( CoCreateInstance(__uuidof(DOMDocument60),
				NULL,
				CLSCTX_INPROC_SERVER/*| CLSCTX_LOCAL_SERVER*/,
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


		void xml_save(const WCHAR* szFile , const WCHAR* szXML)
		{
			::CoInitialize(NULL);
			//::CoInitializeEx(NULL, COINIT_MULTITHREADED);
			IXMLDOMDocument *pXMLDom=NULL;
			IXMLDOMParseError *pXMLErr=NULL;
			BSTR bstr = NULL;
			VARIANT_BOOL status;
			VARIANT var;
			HRESULT hr;

			pXMLDom = DomFromCOM();
			if (!pXMLDom) 
			{
				jWARN_T("DomFromCOM(); %s",jT(szFile));
				goto clean;
			}

			bstr = SysAllocString(szXML);
			HRCALL(pXMLDom->loadXML(bstr, &status), 
				"dom->loadXML(): ");
			SysFreeString(bstr);

			if (status!=VARIANT_TRUE) 
			{
				size_t iSize = jw_strlen(szXML);
				char* sz_char_buffer = new char[iSize+10];
				nMech::nUNI::wchar2char_Cb(sz_char_buffer, szXML, iSize+9);
				//astring aa = a.getA();
				//::replace(aa.begin(), aa.end(),'&',' ');
				FILE* fp = jw_fopen(szFile , L"wt");
				if(fp)
				{
					ja_fprintf(fp , sz_char_buffer);
					fclose(fp);
				}
				delete [] sz_char_buffer;

				HRCALL(pXMLDom->get_parseError(&pXMLErr),
					"dom->get_parseError: ");
				HRCALL(pXMLErr->get_reason(&bstr),
					"parseError->get_reason: ");

				wstring str = bstr;

				jWARN(_T("Failed to load DOM from xml string. %s\n"),jT(str.c_str()));
				goto clean;
			}
			HRCALL(pXMLDom->get_xml(&bstr), "dom->get_xml: ");
			dprintf("XML DOM loaded from stocks.xml:\n%S\n",bstr);

			VariantInit(&var);
			V_BSTR(&var) = SysAllocString(szFile);
			V_VT(&var) = VT_BSTR;
			HRCALL(pXMLDom->save(var), "dom->save: ");

		clean:
			if (bstr) SysFreeString(bstr);
			if (&var) VariantClear(&var);
			if (pXMLErr) pXMLErr->Release();
			if (pXMLDom) pXMLDom->Release();

			CoUninitialize();
		}
		#if 0
		int _tmain(int argc, _TCHAR* argv[])
		{
			WCHAR* szXML = L"<r>\n<t>top</t>\n<b>bottom</b>\n</r>";
			WCHAR* szFile = L"c:\\myData.xml";
			xml_save(szFile, szXML);
			return 0;
		}

		#endif

#else //jMSXML_USE

void xml_save(const WCHAR* szFile , const WCHAR* szXML)
{
	
}

#endif //jMSXML_USE




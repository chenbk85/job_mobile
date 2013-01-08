// test_Mail.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "base/jBase.h"
#include "util/jUtil.h"
#include "common/jCommon.h"
#include "Interface/jISMTPClient.h"
#include "interface/jIDebugCallStack.h"
#include "common/jInit.h"
#include "header/nUNI_StringA.h"
#include "header/nUNI_StringW.h"

using namespace nMech;
using namespace nMech::nUtil;
using namespace nMech::nUtil::nDebug;


void _jConsolePrinterFunc( tcstr szString,bool bAdd )
{
	if(bAdd)
		jt_printf(_T("%s"), szString);
	else
		jt_printf(_T("\n%s"), szString);
}

cstr g_szApp = _TEXT("jTest_Gui");

int _tmain(int argc, _TCHAR* argv[])
{
	nFileSystem::jFolder::CreateDirForce(_T("..\\"));


	using namespace nUNI;
#if 1
	jStringW sTestW( L"Test" );
	jStringA sTestA( "Test" );

	// convert
	jStringW sW = sTestA;
	jStringA sA = sTestW;
	printf("sA = %s", sA);
	wprintf(L"sW = %s", sW);
	jASSERT0(sW==sTestW);


	scb1024_t testBuf;
	testBuf.set(sTestW.GetBuffer(0));
	acstr szA = testBuf.getA();
	wcstr szW = testBuf.getW();
	jASSERT0(sA==szA);
	jASSERT0(sW==szW);

#endif

	jMech_Init(g_szApp);
	GetjILog()->SetPrinter(_jConsolePrinterFunc);

	//jCREATE_INTERFACE_AUTO(pDebugger, nMech::nUtil::nDebug::jIDebugCallStack);
	//pDebugger->Init();

	nXML::jE e =  nGLOBAL::g_pDocApp->Find(jS(mail_test));
	cstr vServer = e(jS(mail_server))->GetVar()->Get_cstr();
	cstr szPort = e(jS(port))->GetVar()->Get_cstr();
	int port = jt_atoi(szPort);
	cstr id= e(jS(id))->GetVar()->Get_cstr();
	cstr pwd= e(jS(pwd))->GetVar()->Get_cstr();
	cstr vFrom = e(jS(from))->GetVar()->Get_cstr();
	cstr vTo = e(jS(to))->GetVar()->Get_cstr();
	
	//acstr fromNick, acstr fromEMail, acstr subject, acstr body 
	cstr fromNick = e(jS(titleNic))->GetVar()->Get_cstr();
	cstr fromEmail = e(jS(titleEMail))->GetVar()->Get_cstr();
	cstr subject = e(jS(subject))->GetVar()->Get_cstr();
	cstr body = e(jS(body))->GetVar()->Get_cstr();

	BOOL			ret;
	jISMTPClient* pMail = jCREATE_INTERFACE(nMech::nUtil::nDebug::jISMTPClient);
	try
	{
#if 1
		ret = pMail->Connect( jA(vServer),jA(id),jA(pwd), port);
		ret = pMail->MailFrom( jA(vFrom) );
		ret = pMail->MailTo( jA(vTo) );
		ret = pMail->MailContents( jA(fromNick), jA(fromEmail), jA(subject), jA(body) );
		jIE* it= e(jS(files))->begin();
		jrFOR(it)
		{
			jLOG(_T("attach file : %s"),it->GetVar()->Get_cstr());
			ret = pMail->MailAttachFileA(jA(it->GetVar()->Get_cstr()));
		}
		ret = pMail->MailSubmit();
		pMail->Disconnect();
#else
		ret = pMail->Connect( "10.96.14.215" ,"mailtest","asdf1234!");
		ret = pMail->MailFrom( "mailtest@10.96.14.215" );
		ret = pMail->MailTo( "icandoit@rocworks.co.kr" );
		ret = pMail->MailContents( "Crasher", "DontSendMe@rocworks.co.kr", "제목", "메일내용" );
		ret = pMail->MailAttachFileA("c:\\a.txt");
		ret = pMail->MailSubmit();
		pMail->Disconnect();
#endif
	}
	catch (acstr szError)
	{
		jWARN(_T("%s %s"),jT(szError),_T("error acstr "));
	}
	catch (wcstr szErrorW)
	{
		jWARN(_T("%s %s"),jT(szErrorW),_T("error wcstr") );
	}
	SAFE_RELEASE(pMail);

#if 0
	pMail = jCREATE_INTERFACE(nMech::nUtil::nDebug::jISMTPClient);
	try
	{
		ret = pMail->Connect( "smtp.gmail.com" );
		ret = pMail->MailFrom( "crash@RoCWorks.co.kr" );
		ret = pMail->MailTo( "icandoit@rocworks.co.kr" );
		ret = pMail->MailContents( "Crasher", "DontSendMe@rocworks.co.kr", "제목", "메일내용" );
		ret = pMail->MailAttachFileA("c:\\a.txt");
		ret = pMail->MailSubmit();
	}
	catch (acstr szError)
	{
		jMB(szError,"error");
	}
	catch (wcstr szErrorW)
	{
		jMB(szErrorW,L"error");
	}
	pMail->Disconnect();
	SAFE_RELEASE(pMail);
#endif
//	int *p =0;
//	*p =12334;

	return 0;
}

